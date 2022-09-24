#include <DxLib.h>
#include "item_manager.hpp"
#include "global_define.hpp"
#include "game_scene.hpp"
#include "macro.hpp"

ItemManager::ItemManager(GameScene* scene) :
    _list(std::list<std::shared_ptr<Item>>{})
{
    _game_scene = scene;
    _counter = 0;
}

void ItemManager::push_item(Vec2 pos, int type) {
    auto item = std::make_shared<Item>(pos, type);
    this->_list.push_back(item);
}

bool ItemManager::update() {
    for (auto iter = _list.begin(); iter != _list.end();) {
        if ((*iter)->update()) {
            ++iter;
        }
        else {
            iter = _list.erase(iter);
        }
    }
    ++_counter;
    return true;
}

void ItemManager::draw() const {
    for (const auto item : _list) {
        item->draw();
    }
}

Vec2 ItemManager::get_player_pos() const {
    return _game_scene->get_player_pos();
}
