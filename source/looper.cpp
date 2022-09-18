#include "looper.hpp"
#include "title_scene.hpp"
#include "error.hpp"

Looper::Looper() {
    SceneParameter param;
    // �^�C�g���V�[�����쐬���Ēǉ���������
    // Looper�̓��X�i�[���ۃN���X���p�����Ă���, �V�[���̃��X�i�[�ɂ�this�|�C���^��n��.
    _scene_stack.push(std::make_shared<TitleScene>(this, param));
}
Looper::~Looper() {}

/**
 * @brief �X�^�b�N�̈�ԏ�ɂ���V�[���ɂ��ď������s��
 */
bool Looper::loop() const {
    _scene_stack.top()->update();
    _scene_stack.top()->draw();
    return true;
}

/**
 * @brief �V�[���ύX�i�e�V�[������R�[���o�b�N�����j
 * @param scene �ύX����V�[����enum
 * @param parameter �O�̃V�[����������p���p�����[�^
 * @param stackClear ���݂̃V�[���̃X�^�b�N���N���A���邩
 */
void Looper::on_scene_changed(const GameScene scene, const SceneParameter& param, const bool stack_clear) {}