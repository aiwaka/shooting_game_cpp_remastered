#include <DxLib.h>
#include "game_system.hpp"
#include "global_define.hpp"
#include "looper.hpp"

/**
 * DxLib��Q�[�����̂̏�����
 */
bool GameSystem::initialize() const {
    //�E�B���h�E���m���A�N�e�B�u�ł����s
    SetAlwaysRunFlag(TRUE);
    //�E�B���h�E�T�C�Y�����R�ɕύX�ł���悤�ɂ���
    SetWindowSizeChangeEnableFlag(TRUE);
    //���O�o�͂��Ȃ�
    SetOutApplicationLogValidFlag(FALSE);
    //�t���X�N���[�����ɏc������ێ�����
    SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);
    //�E�B���h�E�^�C�g����t����
    SetWindowText("FailOver 2 Remastered");
    //�E�B���h�E���[�h�ɕύX
    ChangeWindowMode(TRUE);
    // �t�H���g�T�C�Y�ύX
    SetFontSize(16);
    //�E�B���h�E�T�C�Y��ύX���������͂����ɔ{�����w�肷��
    //	SetWindowSizeExtendRate(1.0);
    //�F��bit���B�ʏ�32�ŗǂ����y������Ȃ�16�ɂ���
    const int COLOR_BIT = 32;
    //�Q�[����ʂ̉𑜓x��ݒ肷��
    SetGraphMode(GlobalValues::SCREEN_WIDTH, GlobalValues::SCREEN_HEIGHT, COLOR_BIT);
    // ���������s������I������
    if (DxLib_Init()) return false;
    /*
    �f�o�b�O�p�@�R���\�[���o��
    */
    //FILE* dummy;
    //AllocConsole();
    //freopen_s(&dummy, "CONOUT$", "w", stdout);
    // �f�o�b�O�R���\�[�����A�N�e�B�u�E�B���h�E�ɂȂ�̂�
    // �Q�[���{�̂̃E�B���h�E���A�N�e�B�u�ɂ���
    //SetForegroundWindow(GetMainWindowHandle());
    /*�f�o�b�O�p�R���\�[���E�B���h�E�ݒ� �����܂�*/

    //����ʏ�����ݒ肷��
    SetDrawScreen(DX_SCREEN_BACK);
    return true;
}

void GameSystem::finalize() const {
    DxLib_End();
    /*�f�o�b�O*/
    //FreeConsole();
}

void GameSystem::main() const {
    Looper looper;
    // ���������C�����[�v
    while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
        if (!looper.loop()) {
            break;
        }
    }
}
