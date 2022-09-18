#pragma once

#include <stack>
#include <memory>
#include "abstract_scene.hpp"
#include "i_on_changed_listener.hpp"
#include "frame_rate_manager.hpp"

class Looper final : public IOnSceneChangedListener {
public:
    Looper();
    ~Looper() = default;
    bool loop();
    void on_scene_changed(const AppScenes scene, const SceneParameter& param, const bool clear_stack) override;

private:
    // �V�[���̃X�}�[�g�|�C���^���X�^�b�N���邱�ƂŃV�[���X�^�b�N��\������.
    // ���ۃV�[���̃X�^�b�N�Ƃ��邱�ƂŌp����̌^�ɂ�炸�ɓ������O�̏������s�����Ƃ��ł���.
    std::stack<std::shared_ptr<AbstractScene>> _scene_stack;
    // ���[�v���i��N���X��FPS�Ǘ����s��.
    FrameRateManager _frm;
};
