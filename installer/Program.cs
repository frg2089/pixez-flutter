using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Threading.Tasks;
using System.Windows;

string path = $"{Path.GetTempFileName()}.msix";
using (Stream stream = typeof(Program).Assembly.GetManifestResourceStream("msix"))
using (FileStream fileStream = File.Create(path))
    stream.CopyTo(fileStream);

try
{
    X509Certificate2 x509Certificate = new(X509Certificate.CreateFromSignedFile(path));
    X509Store store = new(StoreName.TrustedPeople, StoreLocation.LocalMachine);
    store.Open(OpenFlags.ReadWrite);
    if (store.Certificates.Find(X509FindType.FindBySubjectDistinguishedName, x509Certificate.Subject, true) is { Count: 0 })
    {
        MessageBoxResult messageBoxResult = MessageBox.Show(
            $"""
            您是否要添加以下证书到计算机受信任人存储区?

            {x509Certificate.Subject}
            """,
            "提示",
            MessageBoxButton.OKCancel,
            MessageBoxImage.Question);

        if (messageBoxResult is not MessageBoxResult.OK)
            return;

        store.Add(x509Certificate);
    }
    Process.Start(path);
    Task.WaitAll(Process.GetProcesses()
        .Where(i => i.ProcessName is "AppInstaller")
        .Select(i => Task.Run(i.WaitForExit))
        .ToArray());
}
finally
{
    File.Delete(path);
}