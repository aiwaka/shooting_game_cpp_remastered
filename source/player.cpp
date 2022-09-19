#include "player.hpp"
#include "pad_input.hpp"
#include "image_manager.hpp"
#include <DxLib.h>

constexpr float SPEED = 9.0f;

Player::Player() : _pos(Vec2{ 100.0f, 100.0f }) {
    _image = LoadGraph("./dat/img/atari.png");
}
bool Player::update() {
    move();
    return true;
}

void Player::draw() const {
    auto img_manager = ImageManager::get_instance();
    DrawRotaGraphF(_pos.x, _pos.y, 10.0, 0.0, img_manager->get_player(), 1);
}
void Player::move()
{
    float moveX = 0, moveY = 0;
    auto pad_ins = PadInput::get_instance();
    if (pad_ins->get(Left) > 0) {
        moveX -= SPEED;
    }
    if (pad_ins->get(Right) > 0) {
        moveX += SPEED;
    }
    if (pad_ins->get(Down) > 0) {
        moveY += SPEED;
    }
    if (pad_ins->get(Up) > 0) {
        moveY -= SPEED;
    }
    //ŽÎ‚ßˆÚ“®
    if (moveX && moveY) {
        moveX /= sqrtf(2.0);
        moveY /= sqrtf(2.0);
    }
    if (pad_ins->get(Slow) > 0) {
        moveX /= 3.0f;
        moveY /= 3.0f;
    }
    _pos.x += moveX;
    _pos.y += moveY;
}