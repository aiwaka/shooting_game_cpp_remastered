#include <DxLib.h>
#include "game_system.hpp"

// _In_‚Æ‚©‚Íƒwƒbƒ_’ß‚Æ‚¢‚¤‚ç‚µ‚¢. ‚±‚ê‚ª‚È‚¢‚ÆŒx‚ªo‚é
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    GameSystem system = GameSystem{};
    if (system.initialize()) {
        system.main();
    }
    system.finalize();
}