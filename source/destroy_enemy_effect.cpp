#include "destroy_enemy_effect.hpp"
#include "global_define.hpp"
#include "image_manager.hpp"
#include "utils.hpp"

DestroyEnemyEffect::DestroyEnemyEffect(Vec2 pos, int color) :
    AbstractEffect(),
    _pos(pos),
    _angle(utils::rand_in_range(GlobalValues::PI)),
    _ex_rate(0.1f)
{
    _handle = ImageManager::get_instance()->get_destroy_enemy_effect(color);
}

bool DestroyEnemyEffect::update() {
    _ex_rate += 0.05f;
    _angle += 0.3f; // radian
    printf("%d\n", get_counter());
    if (get_counter() == 30) finish();
    return true;
}

void DestroyEnemyEffect::draw() const {
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - get_counter() * 6);
    utils::DrawRotaGraphF_Screen(_pos.x, _pos.y, _ex_rate, _angle, _handle, 1);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}