#pragma once

#include "scene.hpp"
#include "abstract_scene.hpp"
#include "scene_parameter.hpp"

/**
 * �V�[���̕ύX�����m���ē�����s�����߂̃��X�i�[�C���^�[�t�F�C�X���`
 * �������z�֐��݂̂����N���X�Ƃ��Ē�`����.
 */
class IOnSceneChangedListener {
public:
    IOnSceneChangedListener() = default;
    virtual ~IOnSceneChangedListener() = default;
    virtual void on_scene_changed(const AppScenes scene, const SceneParameter& param, const bool stack_clear) = 0;
};
