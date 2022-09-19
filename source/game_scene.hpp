#pragma once

#include <memory>
#include "abstract_scene.hpp"
#include "player.hpp"

class GameScene : public AbstractScene {
public:
    const static char* param_tag_stage;
    const static char* param_tag_level;

    GameScene(IOnSceneChangedListener* impl, const SceneParameter& param);
    virtual ~GameScene() = default;

    void update() override;
    void draw() const override;

private:
    //int _level;
    std::shared_ptr<Player> _player;
};
