#include <DxLib.h>
#include "item.hpp"
#include "global_define.hpp"
#include "image_manager.hpp"
#include "utils.hpp"

Item::Item(Vec2 pos, int type) :
    _counter(0),
    _pos(pos),
    _type(type),
    _getting(false)
{
    _spawn_offset = Vec2{ utils::rand_in_range(30.0), utils::rand_in_range(10.0) - 20.0f };
}

bool Item::update() {
    // 取得された場合特殊な動きにする
    if (_getting) {
        // 取得したらカウンターがリセットされるので再利用する
        if (_counter < 20) _pos.y -= 2.0;
        return _counter++ <= 40;
    }
    // 取得されていない場合以下
    if (_counter < 20) {
        _pos += _spawn_offset / 20.0;
    }
    else {
        _pos.y += 2.0;
    }
    ++_counter;
    return is_inside_field();
}

void Item::draw() const {
    auto handles = ImageManager::get_instance()->get_item(_type);
    int body_handle = handles[0];
    int frame_handle = handles[1];

    float ex_rate = 1.0;
    switch (_type)
    {
    case 0:
    case 4:
        //case 5:
        ex_rate = 0.6;
        break;
    default:
        break;
    }
    float frame_angle = GlobalValues::PI * static_cast<float>(_counter % 120) / 60.0;

    if (_getting) {
        int opacity = _counter < 20 ? 255 : 255 - (_counter - 20) * 13;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, opacity);
        utils::DrawRotaGraphF_Screen(_pos.x, _pos.y, ex_rate, 0.0, body_handle, TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    }
    else {
        utils::DrawRotaGraphF_Screen(_pos.x, _pos.y, ex_rate, frame_angle, frame_handle, TRUE);
        utils::DrawRotaGraphF_Screen(_pos.x, _pos.y, ex_rate, -frame_angle, frame_handle, TRUE);
        utils::DrawRotaGraphF_Screen(_pos.x, _pos.y, ex_rate, 0.0, body_handle, TRUE);

    }
}

bool Item::is_inside_field() const
{
    if (_counter < 240) {
        return true;
    }
    if (_pos.x < -30.0f || GlobalValues::OUT_WIDTH + 30.0f < _pos.x ||
        _pos.y < -30.0f || GlobalValues::OUT_HEIGHT + 30.0f < _pos.y) {
        return false;
    }
    return true;
}
