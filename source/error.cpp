#include <string>
#include <DxLib.h>
#include "global_define.hpp"
#include "error.hpp"

using namespace std;

void Error::finish(char* errorMessage, LPCTSTR lpszFuncName, int lineN)
{
    char funcName[1024];
    //sprintf(funcName, "%s", lpszFuncName);
    printfDx("�G���[\n%s\n%s(%d)"
        , errorMessage
        , funcName
        , lineN
    );
    while (!ProcessMessage()) {
        ClearDrawScreen();
        ScreenFlip();
    }
    DxLib_End();
    exit(99);
}