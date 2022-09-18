#pragma once

#include "scene.hpp"
#include "abstract_scene.hpp"
#include "scene_parameter.hpp"

/**
 * シーンの変更を検知して動作を行うためのリスナーインターフェイスを定義
 * 純粋仮想関数のみをもつクラスとして定義する.
 */
class IOnSceneChangedListener {
public:
    IOnSceneChangedListener() = default;
    virtual ~IOnSceneChangedListener() = default;
    virtual void on_scene_changed(const AppScenes scene, const SceneParameter& param, const bool stack_clear) = 0;
};
