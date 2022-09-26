#include <DxLib.h>
#include "game_system.hpp"

// _In_�Ƃ��̓w�b�_���߂Ƃ����炵��. ���ꂪ�Ȃ��ƌx�����o��
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    GameSystem system = GameSystem{};
    if (system.initialize()) {
        system.main();
    }
    system.finalize();
}