#pragma once

#include "abstract_scene.hpp"

class TitleScene : public AbstractScene {
public:
    TitleScene(IOnSceneChangedListener* impl, const SceneParameter& param);
    virtual ~TitleScene() = default;

    void update() override;
    void draw() override;
};
