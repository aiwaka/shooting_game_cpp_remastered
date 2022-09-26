#include <DxLib.h>
#include "game_system.hpp"
#include "global_define.hpp"
#include "looper.hpp"

/**
 * DxLibやゲーム自体の初期化
 */
bool GameSystem::initialize() const {
    //ウィンドウがノンアクティブでも実行
    SetAlwaysRunFlag(TRUE);
    //ウィンドウサイズを自由に変更できるようにする
    SetWindowSizeChangeEnableFlag(TRUE);
    //ログ出力しない
    SetOutApplicationLogValidFlag(FALSE);
    //フルスクリーン時に縦横比を維持する
    SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);
    //ウィンドウタイトルを付ける
    SetWindowText("FailOver 2 Remastered");
    //ウィンドウモードに変更
    ChangeWindowMode(TRUE);
    // フォントサイズ変更
    SetFontSize(16);
    //ウィンドウサイズを変更したい時はここに倍率を指定する
    //	SetWindowSizeExtendRate(1.0);
    //色のbit数。通常32で良いが軽くするなら16にする
    const int COLOR_BIT = 32;
    //ゲーム画面の解像度を設定する
    SetGraphMode(GlobalValues::SCREEN_WIDTH, GlobalValues::SCREEN_HEIGHT, COLOR_BIT);
    // 初期化失敗したら終了する
    if (DxLib_Init()) return false;
    /*
    デバッグ用　コンソール出力
    */
    //FILE* dummy;
    //AllocConsole();
    //freopen_s(&dummy, "CONOUT$", "w", stdout);
    // デバッグコンソールがアクティブウィンドウになるので
    // ゲーム本体のウィンドウをアクティブにする
    //SetForegroundWindow(GetMainWindowHandle());
    /*デバッグ用コンソールウィンドウ設定 ここまで*/

    //裏画面処理を設定する
    SetDrawScreen(DX_SCREEN_BACK);
    return true;
}

void GameSystem::finalize() const {
    DxLib_End();
    /*デバッグ*/
    //FreeConsole();
}

void GameSystem::main() const {
    Looper looper;
    // ここがメインループ
    while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
        if (!looper.loop()) {
            break;
        }
    }
}
