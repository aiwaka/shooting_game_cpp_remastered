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
        // �擾�ς݂ŉ��o���Ȃ��΂�
        if (item->already_gotten()) continue;
        Vec2 item_pos = item->get_pos();
        // �傫���������Ⴄ�̂ŕ���
        float item_size = 40.0;
        switch (item->get_type())
        {
        case 0:
        case 4:
            //case 5: item5�̓X�R�A��Ƃ���̂ő傫���ƈ���. item.cpp��draw�����l
            item_size = 25.0;
            break;
        default:
            break;
        }
        // �������Ă����
        if (utils::sphere_collision(player_pos, item_pos, 10.0, item_size)) {
            int before_hp = 0;
            int after_hp = 0;
            // �^�C�v�ŕ��򂵂Č��ʂ��y�ڂ�
            switch (item->get_type())
            {
            case 0: // hp��
                // �񕜑O���HP���ω����Ă��Ȃ�������X�R�A���I�}�P����B������l
                before_hp = _game_scene->get_player_info_for_board()[1];
                _game_scene->modify_player_hp(5);
                after_hp = _game_scene->get_player_info_for_board()[1];
                if (before_hp == after_hp) {
                    _game_scene->modify_score(50);
                }
                break;
            case 1: // hp��
                before_hp = _game_scene->get_player_info_for_board()[1];
                _game_scene->modify_player_hp(15);
                after_hp = _game_scene->get_player_info_for_board()[1];
                if (before_hp == after_hp) {
                    _game_scene->modify_score(150);
                }
                break;
            case 2: // �p���[
                _game_scene->modify_player_power(10);
                break;
            case 3: // �c�@
                _game_scene->increment_player_life();
                break;
            case 4: // �X�R�A
                _game_scene->modify_score(100);
                break;
            case 5: // �X�R�A��iTODO: �X�R�A�㏸�ʂƂ��Ďg����悤�ɂ������j
                _game_scene->modify_score(500);
                break;
            case 6: // �{��
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
