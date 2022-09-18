#include "looper.hpp"
#include "error.hpp"
#include "title_scene.hpp"
#include "game_scene.hpp"
#include "macro.hpp"

Looper::Looper() {
    SceneParameter param;
    // �^�C�g���V�[�����쐬���Ēǉ���������
    // Looper�̓��X�i�[���ۃN���X���p�����Ă���, �V�[���̃��X�i�[�ɂ�this�|�C���^��n��.
    _scene_stack.push(std::make_shared<TitleScene>(this, param));
}

/**
 * @brief �X�^�b�N�̈�ԏ�ɂ���V�[���ɂ��ď������s��
 */
bool Looper::loop() {
    _scene_stack.top()->update();
    _scene_stack.top()->draw();
    _frm.draw();
    // ����wait�ɂ���莞�ԊԊu��update��draw�����s����邱�ƂɂȂ�.
    _frm.wait();
    return true;
}

/**
 * @brief �V�[���ύX�i�e�V�[������R�[���o�b�N�Ƃ��ČĂяo�����j
 * @param scene �ύX��̃V�[��
 * @param parameter �O�̃V�[����������p���p�����[�^
 * @param stackClear ���݂̃V�[���̃X�^�b�N���N���A���邩
 */
void Looper::on_scene_changed(const AppScenes scene, const SceneParameter& param, const bool stack_clear) {
    if (stack_clear) {
        while (!_scene_stack.empty()) {
            _scene_stack.pop();
        }
    }
    switch (scene)
    {
    case Title:
        _scene_stack.push(std::make_shared<TitleScene>(this, param));
        break;
    case Game:
        _scene_stack.push(std::make_shared<GameScene>(this, param));
        break;
    default:
        APP_SYSTEM_ERROR("�V�[���G���[");
        break;
    }
}