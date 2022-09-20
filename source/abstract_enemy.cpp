#include <DxLib.h>
#include "global_define.hpp"
#include "abstract_enemy.hpp"
#include "enemy_manager.hpp"
#include "image_manager.hpp"


AbstractEnemy::AbstractEnemy(const EnemyInfo& info, EnemyManager* manager) :
    _pos(Vec2{ info.x, info.y }),
    _speed(Vec2{}),
    _counter(0),
    _texture_width(0),
    _texture_height(0),
    _move_pattern_id(info.move_pattern),
    _enemy_type_id(info.enemy_type),
    _start_attack_count(info.start_attack_count),
    _attack_pattern_id(info.attack_pattern),
    _hp(info.hp),
    _bullet_id(info.bullet_id),
    _bullet_color(info.bullet_color),
    _wait_time(info.wait_time),
    _item_slot{ info.item }
{
    _manager = manager;
    _bullet_list = std::list<std::shared_ptr<EnemyBullet>>(0);
}

void AbstractEnemy::initialize() {
    set_size();
}

bool AbstractEnemy::update() {
    _mover.move(this);
    _attack.attack(this);
    for (auto& bullet : _bullet_list) {
        bullet->update();
    }
    ++_counter;
    return is_inside_field();
}
bool AbstractEnemy::is_inside_field() const
{
    //ç≈èâÇÃ2ïbÇÕè¡Ç¶Ç»Ç¢ÇÊÇ§Ç…Ç∑ÇÈ
    if (_counter < 120) {
        return true;
    }
    if (_pos.x < -_texture_width / 2 || GlobalValues::OUT_WIDTH + _texture_width / 2 < _pos.x ||
        _pos.y < -_texture_height / 2 || GlobalValues::OUT_HEIGHT + _texture_height / 2 < _pos.y) {
        return false;
    }
    return true;
}

Vec2 AbstractEnemy::get_player_pos() const { return _manager->get_player_pos(); }

void AbstractEnemy::push_bullet(std::shared_ptr<EnemyBullet> bullet) {
    _bullet_list.push_back(bullet);
}
