#include "game_scene.hpp"
#include <DxLib.h>

const char* GameScene::param_tag_stage = "param_tag_stage";
const char* GameScene::param_tag_level = "param_tag_level";

GameScene::GameScene(IOnSceneChangedListener* impl, const SceneParameter& param) : AbstractScene(impl, param) {
    _level = param.get_param(this->param_tag_level);
}

void GameScene::update() {}

void GameScene::draw() const {
    DrawFormatString(100, 100, GetColor(255, 255, 255), "level %d", _level);
}


