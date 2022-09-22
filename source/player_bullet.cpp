#include "player_bullet.hpp"
#include "player.hpp"
#include "global_define.hpp"
#include "utils.hpp"
#include "image_manager.hpp"

PlayerBullet::PlayerBullet(int power, Vec2 pos) :
    _counter(0),
    _power(power),
    _pos(pos),
    _angle(-GlobalValues::PI / 2.0),
    _speed(20.0),
    _collided(false)
{
    auto handle = ImageManager::get_instance()->get_player_shot(0);
    _handle = handle;
}

bool PlayerBullet::update() {
    // “G‚Æ‚Ô‚Â‚©‚Á‚½‚çÁ–Å‚³‚¹‚é
    if (_collided) return false;
    _pos += _speed * Vec2::from_angle(_angle);
    ++_counter;
    return is_inside_field();
}
void PlayerBullet::draw() const {
    utils::DrawRotaGraphF_Screen(_pos.x, _pos.y, 1.0, _angle, _handle, 1, 0);
}
Vec2 PlayerBullet::get_pos() const { return this->_pos; }
int PlayerBullet::get_power() const { return this->_power; }
bool PlayerBullet::is_inside_field() const
{
    if (_pos.x < -50.0f || GlobalValues::OUT_WIDTH + 50.0f < _pos.x ||
        _pos.y < -50.0f || GlobalValues::OUT_HEIGHT + 50.0f < _pos.y) {
        return false;
    }
    return true;
}

void PlayerBullet::set_collide_flag() {
    _collided = true;
}
