#include "Weiss.h"

const char *WEISS_CHANNEL = "com.perol.dev/weiss";
const char *TAG = "weiss";

void Weiss::bindChannel(flutter::FlutterEngine *flutterEngine,const flutter::StandardMethodCodec *codec)
{
  const std::string weiss_channel(WEISS_CHANNEL);
  flutter::MethodChannel crypto_method_channel_(flutterEngine->messenger(), weiss_channel, codec);
  crypto_method_channel_.SetMethodCallHandler([](const auto &call, auto result) {
    std::cout << "com.perol.dev/weiss" << std::endl;
    if (call.method_name().compare("start") == 0)
    {
      std::cout << "start" << std::endl;
    }
    else if (call.method_name().compare("proxy") == 0)
    {
      std::cout << "proxy" << std::endl;
    }
    else if (call.method_name().compare("stop") == 0)
    {
      std::cout << "stop" << std::endl;
    }
    result->Success();
  });
}

/*
    fun ser() {
        val serverSocket = ServerSocket(port.toInt())
        while (true) {
            val client = serverSocket.accept()
            println("Client connected: ${client.inetAddress.hostAddress}")

            // Run client in it's own thread.
            thread {
                val inputStream = client.getInputStream()
                val readBytes = inputStream.readBytes()
                inputStream.close()
                val message = readBytes.toString()
                Log.d(TAG, "message:\n $message")
                val serverSocket = SSLSocketFactory.getDefault().createSocket()
                val outputStream = serverSocket.getOutputStream()
                outputStream.write(readBytes)
                outputStream.flush()
                outputStream.close()

            }
        }
    }

    fun start() {
        try {
            weiss.Weiss.start(port)
        } catch (e: Throwable) {
        }
    }

    fun stop() {
        try {
            weiss.Weiss.close()
        } catch (e: Throwable) {

        }
    }

    fun proxy() {
        if (WebViewFeature.isFeatureSupported(WebViewFeature.PROXY_OVERRIDE)) {
            val proxyUrl = "127.0.0.1:${port}"
            val proxyConfig: ProxyConfig = ProxyConfig.Builder()
                    .addProxyRule(proxyUrl)
                    .addDirect()
                    .build()
            ProxyController.getInstance().setProxyOverride(proxyConfig, { command -> command?.run() }, { android.util.Log.w("d", "WebView proxy") })
        } else {
        }
    }
*/