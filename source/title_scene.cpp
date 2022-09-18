#include "title_scene.hpp"
#include "game_scene.hpp"
#include "global_define.hpp"
#include <DxLib.h>

TitleScene::TitleScene(IOnSceneChangedListener* impl, const SceneParameter& param) : AbstractScene(impl, param) {}

void TitleScene::update() {
    if (CheckHitKey(KEY_INPUT_E)) {
        SceneParameter param;
        param.set_param(GameScene::param_tag_level, GlobalValues::Level::Easy);
        const bool stack_clear = false;
        _impl_scene_changed->on_scene_changed(AppScenes::Game, param, stack_clear);
        return;
    }
    if (CheckHitKey(KEY_INPUT_N)) {
        SceneParameter param;
        param.set_param(GameScene::param_tag_level, GlobalValues::Level::Normal);
        const bool stack_clear = false;
        _impl_scene_changed->on_scene_changed(AppScenes::Game, param, stack_clear);
        return;
    }
}

void TitleScene::draw() const {
    DrawString(100, 100, "title", GetColor(255, 255, 255));
}