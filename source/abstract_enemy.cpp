#include <DxLib.h>
#include "global_define.hpp"
#include "abstract_enemy.hpp"
#include "image_manager.hpp"

AbstractEnemy::AbstractEnemy(float x, float y) :
    _pos(Vec2{ x, y }),
    _speed(Vec2{}),
    _counter(0),
    _texture_width(0),
    _texture_height(0),
    _move_pattern_id(0)
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
    //Å‰‚Ì2•b‚ÍÁ‚¦‚È‚¢‚æ‚¤‚É‚·‚é
    if (_counter < 120) {
        return true;
    }
    if (_pos.x < -_texture_width / 2 || GlobalValues::OUT_WIDTH + _texture_width / 2 < _pos.x ||
        _pos.y < -_texture_height / 2 || GlobalValues::OUT_HEIGHT + _texture_height / 2 < _pos.y) {
        return false;
    }
    return true;
}
