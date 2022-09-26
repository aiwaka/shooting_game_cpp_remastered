#include <DxLib.h>
#include "item_manager.hpp"
#include "global_define.hpp"
#include "game_scene.hpp"
#include "macro.hpp"
#include "se_manager.hpp"

ItemManager::ItemManager(GameScene* scene) :
    _list(std::list<std::shared_ptr<Item>>{})
{
    _game_scene = scene;
    _counter = 0;
}

void ItemManager::push_item(Vec2 pos, int type) {
    if (type < 0 || 6 < type) return;
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
    collision_against_player();
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

void ItemManager::collision_against_player() const {
    Vec2 player_pos = get_player_pos();
    for (auto& item : this->_list) {
        // 取得済みで演出中なら飛ばす
        if (item->already_gotten()) continue;
        Vec2 item_pos = item->get_pos();
        // 大きさが少し違うので分岐
        float item_size = 40.0;
        switch (item->get_type())
        {
        case 0:
        case 4:
            //case 5: item5はスコア大とするので大きいと扱う. item.cppのdrawも同様
            item_size = 25.0;
            break;
        default:
            break;
        }
        // あたっていれば
        if (utils::sphere_collision(player_pos, item_pos, 10.0, item_size)) {
            int before_hp = 0;
            int after_hp = 0;
            // タイプで分岐して効果を及ぼす
            switch (item->get_type())
            {
            case 0: // hp小
                // 回復前後でHPが変化していなかったらスコアをオマケする。大も同様
                before_hp = _game_scene->get_player_info_for_board()[1];
                _game_scene->modify_player_hp(5);
                after_hp = _game_scene->get_player_info_for_board()[1];
                if (before_hp == after_hp) {
                    _game_scene->modify_score(50);
                }
                break;
            case 1: // hp大
                before_hp = _game_scene->get_player_info_for_board()[1];
                _game_scene->modify_player_hp(15);
                after_hp = _game_scene->get_player_info_for_board()[1];
                if (before_hp == after_hp) {
                    _game_scene->modify_score(150);
                }
                break;
            case 2: // パワー
                _game_scene->modify_player_power(10);
                break;
            case 3: // 残機
                _game_scene->increment_player_life();
                break;
            case 4: // スコア
                _game_scene->modify_score(100);
                break;
            case 5: // スコア大（TODO: スコア上昇量として使えるようにしたい）
                _game_scene->modify_score(500);
                break;
            case 6: // ボム
                _game_scene->increment_player_bomb();
                break;
            default:
                break;
            }
            item->set_getting();
            SoundEffectManager::get_instance()->set_se(10);
        }
    }
}
