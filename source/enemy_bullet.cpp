#include "enemy_bullet.hpp"
#include "enemy_bullet_manager.hpp"
#include "abstract_enemy.hpp"
#include "global_define.hpp"
#include "image_manager.hpp"
#include "utils.hpp"

EnemyBullet::EnemyBullet(const EnemyBulletInfo& info) :
    _counter(0),
    _pos(Vec2{ info.x, info.y }),
    _angle(info.angle),
    _speed(info.speed),
    _omega(info.omega),
    _acceleration(info.acceleration),
    _endure_count(info.endure_count),
    _type(info.bullet_type),
    _color(info.color),
    _damage(info.damage),
    _fx_detail(info.fx_detail),
    _bomb_regist(info.bomb_regist),
    _delete_flag(false)
{
    auto handle = ImageManager::get_instance()->get_enemy_bullet(info.bullet_type, info.color);
    _handle = handle;
    //_parent = parent;
}

bool EnemyBullet::update() {
    if (_delete_flag) return false;
    _angle += _omega;
    _speed += _acceleration;
    _pos += _speed * Vec2::from_angle(_angle);
    ++_counter;
    return is_inside_field();
}
void EnemyBullet::draw() const {
    float ex_rate = 0.4f;
    utils::DrawRotaGraphF_Screen(_pos.x, _pos.y, ex_rate, _angle, _handle, 1, 0);
}
bool EnemyBullet::is_inside_field() const
{
    // ‘Ï‹vƒJƒEƒ“ƒg‚ğã‰ñ‚Á‚Ä‚¢‚È‚¯‚ê‚ÎÁ‚³‚È‚¢
    if (_counter < _endure_count) {
        return true;
    }
    if (_pos.x < -50.0f || GlobalValues::OUT_WIDTH + 50.0f < _pos.x ||
        _pos.y < -50.0f || GlobalValues::OUT_HEIGHT + 50.0f < _pos.y) {
        return false;
    }
    return true;
}
int EnemyBullet::get_counter() const { return this->_counter; }
Vec2 EnemyBullet::get_pos() const { return this->_pos; }
int EnemyBullet::get_type() const { return this->_type; }
