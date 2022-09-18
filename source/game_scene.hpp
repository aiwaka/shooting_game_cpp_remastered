#pragma once

#include "abstract_scene.hpp"

class GameScene : public AbstractScene {
public:
    const static char* param_tag_stage;
    const static char* param_tag_level;

    GameScene(IOnSceneChangedListener* impl, const SceneParameter& param);
    virtual ~GameScene() = default;

    void update() override;
    void draw() const override;

private:
    int _level;
};
