#include "title_scene.hpp"
#include "game_scene.hpp"
#include "global_define.hpp"
#include <DxLib.h>
#include "keyboard.hpp"
#include "pad_input.hpp"
#include "fullscreen_picture.hpp"

TitleScene::TitleScene(IOnSceneChangedListener* impl, const SceneParameter& param) : AbstractScene(impl, param) {
    _background = std::make_shared<FullScreenPicture>(0);
}

void TitleScene::update() {
    _background->update();
    if (PadInput::get_instance()->get(Shot) == 1) {
        SceneParameter param;

        param.set_param(GameScene::param_tag_stage, GetRand(2));
        param.set_param(GameScene::param_tag_level, GlobalValues::Level::Easy);
        const bool stack_clear = true;
        _impl_scene_changed->on_scene_changed(AppScenes::Game, param, stack_clear);
        return;
    }
    /*
    if (Keyboard::get_instance()->get_pressing_count(KEY_INPUT_N) == 1) {
         SceneParameter param;
         param.set_param(GameScene::param_tag_level, GlobalValues::Level::Normal);
         const bool stack_clear = false;
         _impl_scene_changed->on_scene_changed(AppScenes::Game, param, stack_clear);
         return;
    }
    */
}

void TitleScene::draw() const {
    _background->draw();
    DrawString(GlobalValues::CENTER_X, GlobalValues::CENTER_Y, "Press Z Start", GetColor(255, 255, 255));
}