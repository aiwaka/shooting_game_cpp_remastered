#include <DxLib.h>

#include "global_define.hpp"
#include "player.hpp"
#include "pad_input.hpp"
#include "image_manager.hpp"

constexpr float SPEED = 9.0f;

Player::Player() : _pos(Vec2{ static_cast<float>(GlobalValues::CENTER_X), static_cast<float>(GlobalValues::OUT_HEIGHT) * 0.8f }) {}

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
    //éŒÇﬂà⁄ìÆ
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
    // ÉQÅ[ÉÄç¿ïWÇÃè„â∫îΩì]Ç…ãCÇÇ¬ÇØÇÈ
    const float IN_TOP_LEFT_X = GlobalValues::IN_TOP_LEFT_X;
    const float IN_TOP_LEFT_Y = GlobalValues::IN_TOP_LEFT_Y;
    const float IN_BOTTOM_RIGHT_X = GlobalValues::IN_TOP_LEFT_X + GlobalValues::IN_WIDTH;
    const float IN_BOTTOM_RIGHT_Y = GlobalValues::IN_TOP_LEFT_Y + GlobalValues::IN_HEIGHT;
    _pos = _pos.clamp(Vec2{ IN_TOP_LEFT_X, IN_TOP_LEFT_Y }, Vec2{ IN_BOTTOM_RIGHT_X, IN_BOTTOM_RIGHT_Y });
}