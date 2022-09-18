#include "title_scene.hpp"
#include "game_scene.hpp"
#include "global_define.hpp"
#include <DxLib.h>
#include "keyboard.hpp"
#include "pad_input.hpp"

TitleScene::TitleScene(IOnSceneChangedListener* impl, const SceneParameter& param) : AbstractScene(impl, param) {}

void TitleScene::update() {
    if (PadInput::get_instance()->get(Shot) == 1) {
        SceneParameter param;
        param.set_param(GameScene::param_tag_level, GlobalValues::Level::Easy);
        const bool stack_clear = false;
        _impl_scene_changed->on_scene_changed(AppScenes::Game, param, stack_clear);
        return;
    }
    if (Keyboard::get_instance()->get_pressing_count(KEY_INPUT_N) == 1) {
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