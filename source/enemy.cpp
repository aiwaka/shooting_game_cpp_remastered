#include <DxLib.h>
#include "enemy.hpp"
#include "image_manager.hpp"
#include "global_define.hpp"

Enemy::Enemy(float x, float y) : _pos(Vec2{ x, y }), _speed(Vec2{ 0.0f, 2.0f }) {}


bool Enemy::update() {
    _pos += _speed;
    return true;
}

void Enemy::draw() const {
    auto handle = ImageManager::get_instance()->get_enemy_a()[0];
    DrawRotaGraphF(_pos.x, _pos.y, 1.0, 0.0, handle, 1);
}