#include "bomb_effect.hpp"
#include "global_define.hpp"
#include "image_manager.hpp"
#include "utils.hpp"

BombEffect::BombEffect(Vec2 pos) :
    AbstractEffect(),
    _pos(pos),
    _angle(0.0),
    _ex_rate(0.01f)
{
    _handle = ImageManager::get_instance()->get_bomb();
    _black_handle = ImageManager::get_instance()->get_black();
}

bool BombEffect::update() {
    _ex_rate += 0.02f;
    _angle += 0.5f; // radian
    if (get_counter() == 150) finish();
    return true;
}

void BombEffect::draw() const {
    int counter = get_counter();
    int dark_opacity = counter < 20 ? counter * 5 : counter < 120 ? 100 : 100 - (counter - 120) * 4;
    int opacity = counter < 120 ? 255 : 255 - (counter - 120) * 9;
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, dark_opacity);
    DrawGraph(0, 0, _black_handle, 1);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, opacity);
    utils::DrawRotaGraphF_Screen(_pos.x, _pos.y, _ex_rate, _angle, _handle, 1);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}