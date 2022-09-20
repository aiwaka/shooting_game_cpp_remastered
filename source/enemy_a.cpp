#include <DxLib.h>
#include "enemy_a.hpp"
#include "image_manager.hpp"
#include "global_define.hpp"

EnemyA::EnemyA(float x, float y) : AbstractEnemy(x, y) {
    _move_pattern_id = 0;
}

void EnemyA::draw() const {
    auto handle = ImageManager::get_instance()->get_enemy_a()[0];
    DrawRotaGraphF(_pos.x, _pos.y, 1.0, 0.0, handle, 1);
}

void EnemyA::set_size() {
    auto handle = ImageManager::get_instance()->get_enemy_a()[0];
    GetGraphSize(handle, &_texture_width, &_texture_height);
}