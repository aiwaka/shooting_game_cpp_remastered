#include <DxLib.h>
#include "game_system.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    GameSystem system = GameSystem{};
    if (system.initialize()) {
        system.main();
    }
    system.finalize();
}