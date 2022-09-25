#include "global_define.hpp"
#include "image_manager.hpp"
#include "boss_child.hpp"
// TODO: EnemyBulletInfo‚ð“Ç‚Ýž‚Þ‚¾‚¯. ÝŒv‚ªˆ«‚¢‚Ì‚Å‚È‚ñ‚Æ‚©‚µ‚½‚¢
#include "enemy_bullet_manager.hpp"
#include "utils.hpp"

BossChild::BossChild(const EnemyBulletInfo& info) :
    _counter(0),
    _pos(Vec2{ info.x, info.y }),
    _angle(info.angle),
    _speed(info.speed),
    _omega(info.omega),
    _acceleration(info.acceleration),
    _state(info.bullet_type),
    _delete_flag(false)
{
    _handle = ImageManager::get_instance()->get_boss_child();
}

bool BossChild::update() {
    if (_delete_flag) return false;
    _angle += _omega;
    _speed += _acceleration;
    _pos += _speed * Vec2::from_angle(_angle);
    ++_counter;
    return true;
}
void BossChild::draw() const {
    float ex_rate = 0.4f;
    // ‘¬“x‚ÌŒü‚«‚ÉŠÖŒW‚È‚­Ž©“®‚Å‰ñ‚é
    utils::DrawRotaGraphF_Screen(_pos.x, _pos.y, ex_rate, static_cast<float>(_counter) / 2.0f, _handle, 1, 0);
}
bool BossChild::is_inside_field() const
{
    if (_pos.x < -50.0f || GlobalValues::OUT_WIDTH + 50.0f < _pos.x ||
        _pos.y < -50.0f || GlobalValues::OUT_HEIGHT + 50.0f < _pos.y) {
        return false;
    }
    return true;
}
