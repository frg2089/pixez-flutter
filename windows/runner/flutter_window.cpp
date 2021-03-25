#include "flutter_window.h"

#include <optional>

#include "CodeGen.h"
#include "Weiss.h"
#include "flutter/generated_plugin_registrant.h"

const char *CHANNEL = "com.perol.dev/save";
const char *CRYPTO_CHANNEL = "com.perol.dev/crypto";
const char *ENCODE_CHANNEL = "samples.flutter.dev/battery";
const char *SUPPORTER_CHANNEL = "com.perol.dev/supporter";

FlutterWindow::FlutterWindow(RunLoop *run_loop,
                             const flutter::DartProject &project)
    : run_loop_(run_loop), project_(project) {}

FlutterWindow::~FlutterWindow() {}

bool FlutterWindow::OnCreate()
{
  if (!Win32Window::OnCreate())
  {
    return false;
  }

  RECT frame = GetClientArea();

  // The size here must match the window dimensions to avoid unnecessary surface
  // creation / destruction in the startup path.
  flutter_controller_ = std::make_unique<flutter::FlutterViewController>(
      frame.right - frame.left, frame.bottom - frame.top, project_);
  // Ensure that basic setup of the controller was successful.
  if (!flutter_controller_->engine() || !flutter_controller_->view())
  {
    return false;
  }
  RegisterPlugins(flutter_controller_->engine());
  run_loop_->RegisterFlutterInstance(flutter_controller_->engine());
  SetChildContent(flutter_controller_->view()->GetNativeWindow());

  configMethodChannel(flutter_controller_->engine());

  return true;
}

void FlutterWindow::OnDestroy()
{
  if (flutter_controller_)
  {
    run_loop_->UnregisterFlutterInstance(flutter_controller_->engine());
    flutter_controller_ = nullptr;
  }

  Win32Window::OnDestroy();
}

LRESULT
FlutterWindow::MessageHandler(HWND hwnd, UINT const message,
                              WPARAM const wparam,
                              LPARAM const lparam) noexcept
{
  // Give Flutter, including plugins, an opporutunity to handle window messages.
  if (flutter_controller_)
  {
    std::optional<LRESULT> result =
        flutter_controller_->HandleTopLevelWindowProc(hwnd, message, wparam,
                                                      lparam);
    if (result)
    {
      return *result;
    }
  }

  switch (message)
  {
  case WM_FONTCHANGE:
    flutter_controller_->engine()->ReloadSystemFonts();
    break;
  }

  return Win32Window::MessageHandler(hwnd, message, wparam, lparam);
}

void configMethodChannel(flutter::FlutterEngine *engine)
{
  const flutter::StandardMethodCodec &codec = flutter::StandardMethodCodec::GetInstance();

  const std::string crypto_channel(CRYPTO_CHANNEL);
  flutter::MethodChannel crypto_method_channel_(engine->messenger(), crypto_channel, &codec);
  crypto_method_channel_.SetMethodCallHandler([](const auto &call, auto result) {
    std::cout << "Inside method call" << std::endl;
    if (call.method_name().compare("code_verifier") == 0)
    {
      std::cout << "code_verifier" << std::endl;
      result->Success(CodeGen::getCodeVer());
    }
    else if (call.method_name().compare("code_challenge") == 0)
    {
      std::cout << "code_challenge" << std::endl;
      std::cout << call.arguments() << std::endl;
      result->Success();
    }
  });

  const std::string supporter_channel(SUPPORTER_CHANNEL);
  flutter::MethodChannel supporter_method_channel_(engine->messenger(), supporter_channel, &codec);
  supporter_method_channel_.SetMethodCallHandler([](const auto &call, auto result) {
    if (call.method_name().compare("process_text") == 0)
    {
      std::cout << "process_text" << std::endl;
      result->Success();
    }
    else if (call.method_name().compare("process") == 0)
    {
      std::cout << "process" << std::endl;
      result->Success();
    }
  });

  const std::string channel(CHANNEL);
  flutter::MethodChannel method_channel_(engine->messenger(), channel, &codec);
  method_channel_.SetMethodCallHandler([](const auto &call, auto result) {
    if (call.method_name().compare("save") == 0)
    {
      std::cout << "save" << std::endl;
      result->Success();
    }
    else if (call.method_name().compare("get_path") == 0)
    {
      std::cout << "get_path" << std::endl;
      result->Success();
    }
    else if (call.method_name().compare("exist") == 0)
    {
      std::cout << "exist" << std::endl;
      result->Success();
    }
    else if (call.method_name().compare("choice_folder") == 0)
    {
      std::cout << "choice_folder" << std::endl;
      result->Success();
    }
  });

  const std::string encode_channel(ENCODE_CHANNEL);
  flutter::MethodChannel encode_method_channel_(engine->messenger(), encode_channel, &codec);
  encode_method_channel_.SetMethodCallHandler([](const auto &call, auto result) {
    if (call.method_name().compare("getBatteryLevel") == 0)
    {
      std::cout << "getBatteryLevel" << std::endl;
      result->Success();
    }
  });

  Weiss::bindChannel(engine, &codec);
}