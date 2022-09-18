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
    SetWindowText("GameTitle");
    //�E�B���h�E���[�h�ɕύX
    ChangeWindowMode(TRUE);
    //�E�B���h�E�T�C�Y��ύX���������͂����ɔ{�����w�肷��
    //	SetWindowSizeExtendRate(1.0);
    //�F��bit���B�ʏ�32�ŗǂ����y������Ȃ�16�ɂ���
    const int COLOR_BIT = 32;
    //�Q�[����ʂ̉𑜓x��ݒ肷��
    SetGraphMode(GlobalValues::SCREEN_WIDTH, GlobalValues::SCREEN_HEIGHT, COLOR_BIT);
    // ���������s������I������
    if (DxLib_Init()) return false;
    //����ʏ�����ݒ肷��
    SetDrawScreen(DX_SCREEN_BACK);
    return true;
}

void GameSystem::finalize() const {
    DxLib_End();
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
