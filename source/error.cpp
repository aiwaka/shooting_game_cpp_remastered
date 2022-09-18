#include <string>
#include <DxLib.h>
#include "global_define.hpp"
#include "error.hpp"

void Error::finish(std::string error_message, LPCTSTR lpsz_func_name, int line_num)
{
    char func_name[1024];
    sprintf_s(func_name, "%s", lpsz_func_name);
    printfDx("システムエラー\n%s\n%s(%d)", error_message.c_str(), func_name, line_num);
    while (!ProcessMessage()) {
        ClearDrawScreen();
        ScreenFlip();
    }
    DxLib_End();
    exit(99);
}