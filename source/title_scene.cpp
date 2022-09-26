#include <DxLib.h>
#include "title_scene.hpp"
#include "game_scene.hpp"
#include "global_define.hpp"
#include "keyboard.hpp"
#include "pad_input.hpp"
#include "fullscreen_picture.hpp"
#include "music_manager.hpp"

TitleScene::TitleScene(IOnSceneChangedListener* impl, const SceneParameter& param) : AbstractScene(impl, param) {
    using Option = std::pair<std::string, int>;
    MusicManager::get_instance()->play_music(0);
    _background = std::make_shared<FullScreenPicture>(0);
    _cursor_pos = 0;
    _option_list = std::vector<Option>(0);
    // 選択肢内容と表示するy座標をセットにして持っておく
    _option_list.push_back(Option{ "START", 260 });
    _option_list.push_back(Option{ "EXIT", 300 });
}

bool TitleScene::update() {
    _background->update();
    int list_size = static_cast<int>(_option_list.size());
    if (PadInput::get_instance()->get(Up) == 1) {
        _cursor_pos = (_cursor_pos + list_size - 1) % list_size;
    }
    if (PadInput::get_instance()->get(Down) == 1) {
        _cursor_pos = (_cursor_pos + 1) % list_size;
    }
    if (PadInput::get_instance()->get(Shot) == 1) {
        if (_cursor_pos == 1) return false;
        SceneParameter param;
        _impl_scene_changed->on_scene_changed(AppScenes::LevelSelect, param, false);
        return true;
    }
    if (PadInput::get_instance()->get(Bomb) == 1) {
        _cursor_pos = 1;
    }
    return true;
}

void TitleScene::draw() const {
    _background->draw();
    auto white = GetColor(255, 255, 255);

    for (auto& [str, pos_y] : _option_list) {
        DrawString(300, pos_y, str.c_str(), white);
    }
    int cursor_y = _option_list[_cursor_pos].second;
    DrawString(250, cursor_y, "■", white);
}