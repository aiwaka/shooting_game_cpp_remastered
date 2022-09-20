#include <DxLib.h>
#include "global_define.hpp"
#include "abstract_enemy.hpp"
#include "enemy_manager.hpp"
#include "image_manager.hpp"


AbstractEnemy::AbstractEnemy(const EnemyInfo& info) :
    _pos(Vec2{ info.x, info.y }),
    _speed(Vec2{}),
    _counter(0),
    _texture_width(0),
    _texture_height(0),
    _move_pattern_id(info.move_pattern),
    _enemy_type_id(info.enemy_type),
    _start_fire_count(info.start_fire_count),
    _fire_pattern_id(info.fire_pattern),
    _hp(info.hp),
    _bullet_id(info.bullet_id),
    _bullet_color(info.bullet_color),
    _wait_time(info.wait_time),
    _item_slot{ info.item }
{}

void AbstractEnemy::initialize() {
    set_size();
}

bool AbstractEnemy::update() {
    _mover.move(this);
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
