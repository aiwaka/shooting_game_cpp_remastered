#include <DxLib.h>
#include "enemy_b.hpp"
#include "image_manager.hpp"
#include "global_define.hpp"

EnemyB::EnemyB(float x, float y) : AbstractEnemy(x, y) {
    _move_pattern_id = 2;
}

void EnemyB::draw() const {
    auto handle = ImageManager::get_instance()->get_enemy_b()[0];
    DrawRotaGraphF(_pos.x, _pos.y, 1.0, 0.0, handle, 1);
}

void EnemyB::set_size() {
    auto handle = ImageManager::get_instance()->get_enemy_b()[0];
    GetGraphSize(handle, &_texture_width, &_texture_height);
}