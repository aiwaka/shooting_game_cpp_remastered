#pragma once

#include "i_on_changed_listener.hpp"
#include "scene_parameter.hpp"

class IOnSceneChangedListener;

/**
 * @brief �V�[���ɕK�v�Ȃ��̂��܂Ƃ߂����ۃN���X
 */
class AbstractScene {
protected:
    IOnSceneChangedListener* _impl_scene_changed;
public:
    /**
     * @brief ���ۃN���X�̃R���X�g���N�^.
     * @param impl �V�[���ύX�̃��X�i�[
     * @param parameter �O�̃V�[������n���ꂽ�p�����[�^
     */
    AbstractScene(IOnSceneChangedListener* impl, const SceneParameter& param);
    virtual ~AbstractScene() = default;
    virtual void update() = 0;
    virtual void draw() const = 0;
};
