#include <DxLib.h>
#include <string>
#include <cstdio>
#include <vector>
#include "title_scene.hpp"
#include "result_scene.hpp"
#include "global_define.hpp"
#include "keyboard.hpp"
#include "pad_input.hpp"
#include "fullscreen_picture.hpp"
#include "music_manager.hpp"

const char* ResultScene::param_tag_level = "param_tag_level";
const char* ResultScene::param_tag_score = "param_tag_score";

ResultScene::ResultScene(IOnSceneChangedListener* impl, const SceneParameter& param) : AbstractScene(impl, param) {
    _level = param.get_param(this->param_tag_level);
    _score = param.get_param(this->param_tag_score);
    MusicManager::get_instance()->play_music(3);
    _background = std::make_shared<FullScreenPicture>(1);
}

bool ResultScene::update() {
    _background->update();
    if (PadInput::get_instance()->get(Shot) == 1 || PadInput::get_instance()->get(Bomb) == 1) {
        SceneParameter param;
        _impl_scene_changed->on_scene_changed(AppScenes::Title, param, false);
        return true;
    }
    return true;
}

void ResultScene::draw() const {
    _background->draw();
    auto white = GetColor(255, 255, 255);

    DrawString(300, 200, "RESULT", white);
    const char* level_str = _level == 0 ? "EASY" : _level == 1 ? "NORMAL" : _level == 2 ? "HARD" : "INFERNO";
    char result_str[256];
    std::snprintf(result_str, std::size(result_str), "LEVEL : %s   SCORE : %d", level_str, _score);
    DrawString(200, 270, result_str, white);

}