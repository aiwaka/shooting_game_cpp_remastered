#include "level_select_scene.hpp"
#include "game_scene.hpp"
#include "global_define.hpp"
#include <DxLib.h>
#include "keyboard.hpp"
#include "pad_input.hpp"
#include "fullscreen_picture.hpp"

LevelSelectScene::LevelSelectScene(IOnSceneChangedListener* impl, const SceneParameter& param) : AbstractScene(impl, param) {
    using Option = std::pair<std::string, int>;
    _background = std::make_shared<FullScreenPicture>(0);
    _cursor_pos = 0;
    _option_list = std::vector<Option>(0);
    // 選択肢内容と表示するy座標をセットにして持っておく
    _option_list.push_back(Option{ "EASY", 200 });
    _option_list.push_back(Option{ "NORMAL", 240 });
    _option_list.push_back(Option{ "HARD", 280 });
    _option_list.push_back(Option{ "INFERNO", 320 });
    _option_list.push_back(Option{ "タイトルに戻る", 360 });
}

bool LevelSelectScene::update() {
    _background->update();
    int list_size = static_cast<int>(_option_list.size());
    if (PadInput::get_instance()->get(Up) == 1) {
        _cursor_pos = (_cursor_pos + list_size - 1) % list_size;
    }
    if (PadInput::get_instance()->get(Down) == 1) {
        _cursor_pos = (_cursor_pos + 1) % list_size;
    }
    if (PadInput::get_instance()->get(Shot) == 1) {
        if (_cursor_pos == 4) {
            // タイトルに戻る
            _impl_scene_changed->pop_scene();
            return true;
        }
        else {
            SceneParameter param;

            param.set_param(GameScene::param_tag_stage, GetRand(2));
            param.set_param(GameScene::param_tag_level, _cursor_pos);
            _impl_scene_changed->on_scene_changed(AppScenes::Game, param, true);
            return true;
        }

    }
    if (PadInput::get_instance()->get(Bomb) == 1) {
        _cursor_pos = 4;
    }
    return true;
}

void LevelSelectScene::draw() const {
    _background->draw();

    auto white = GetColor(255, 255, 255);
    DrawString(0, 0, "出撃準備画面です。最大HPを選択してください。", white);
    for (auto& [str, pos_y] : _option_list) {
        DrawString(280, pos_y, str.c_str(), white);
    }
    int cursor_y = _option_list[_cursor_pos].second;
    DrawString(250, cursor_y, "■", white);
}