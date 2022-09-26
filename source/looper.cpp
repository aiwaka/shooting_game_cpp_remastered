#include "looper.hpp"
#include "error.hpp"
#include "macro.hpp"
#include "keyboard.hpp"
#include "pad_input.hpp"
#include "image_manager.hpp"
#include "se_manager.hpp"

#include "title_scene.hpp"
#include "level_select_scene.hpp"
#include "game_scene.hpp"

Looper::Looper() {
    // �A�Z�b�g���[�h
    ImageManager::get_instance()->load();
    SceneParameter param;
    // �^�C�g���V�[�����쐬���Ēǉ���������
    // Looper�̓��X�i�[���ۃN���X���p�����Ă���, �V�[���̃��X�i�[�ɂ�this�|�C���^��n��.
    _scene_stack.push(std::make_shared<TitleScene>(this, param));
    // �Q�[������n�߂�Ƃ��̓Q�[���V�[�����쐬���Ēǉ�
    //_scene_stack.push(std::make_shared<GameScene>(this, param));
}

/**
 * @brief �X�^�b�N�̈�ԏ�ɂ���V�[���ɂ��ď������s��
 */
bool Looper::loop() {
    Keyboard::get_instance()->update();
    PadInput::get_instance()->update();
    // �e�V�[����update��false���Ԃ��Ă����ꍇ�Q�[�����I������.
    bool update_result = _scene_stack.top()->update();
    if (!update_result) return false;
    _scene_stack.top()->draw();
    SoundEffectManager::get_instance()->play_se();
    _frm.draw();
    // ����wait�ɂ���莞�ԊԊu��update��draw�����s����邱�ƂɂȂ�.
    _frm.wait();
    return true;
}


void Looper::pop_scene() {
    if (_scene_stack.empty()) APP_SYSTEM_ERROR("�V�[���X�^�b�N�͋�̂��߃|�b�v�ł��܂���.");
    _scene_stack.pop();
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
    case LevelSelect:
        _scene_stack.push(std::make_shared<LevelSelectScene>(this, param));
        break;
    case Game:
        _scene_stack.push(std::make_shared<GameScene>(this, param));
        break;
        //case Staffroll:
            //break;
    default:
        APP_SYSTEM_ERROR("�V�[���G���[");
        break;
    }
}