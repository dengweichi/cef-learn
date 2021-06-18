
#include <windows.h>

#include "cef_command_line.h"
#include "./simple_app.h"


int APIENTRY WinMain(HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPTSTR lpCmdLine,
                      int nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  // 启动高dpi屏幕支持
  CefEnableHighDPISupport();

  CefMainArgs main_args(hInstance);


  int exit_code = CefExecuteProcess(main_args, nullptr, nullptr);
  if (exit_code >= 0) {
    return exit_code;
  }

  // 构建命令行参数
  CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
  command_line->InitFromString(::GetCommandLineW());

  // cef应用全局设置
  CefSettings settings;

  CefRefPtr<SimpleApp> app(new SimpleApp);

  // 初始化cef
  CefInitialize(main_args, settings, app.get(), nullptr);

  // 期待cef browser消息循环
  CefRunMessageLoop();

  // 关闭cef
  CefShutdown();

  return 0;
}
