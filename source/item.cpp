#include <DxLib.h>
#include "item.hpp"
#include "global_define.hpp"
#include "utils.hpp"

Item::Item(Vec2 pos, int type) :
    _counter(0),
    _pos(pos),
    _type(type)
{}

bool Item::update() {

    return is_inside_field();
}

void Item::draw() const {

}

bool Item::is_inside_field() const
{
    if (_counter < 120) {
        return true;
    }
    if (_pos.x < -30.0f || GlobalValues::OUT_WIDTH + 30.0f < _pos.x ||
        _pos.y < -30.0f || GlobalValues::OUT_HEIGHT + 30.0f < _pos.y) {
        return false;
    }
    return true;
}
