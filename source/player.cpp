#include <DxLib.h>

#include "global_define.hpp"
#include "player.hpp"
#include "pad_input.hpp"
#include "player_bullet_manager.hpp"
#include "image_manager.hpp"
#include "utils.hpp"

constexpr float SPEED = 6.0f;

Player::Player(std::shared_ptr<PlayerBulletManager> manager) :
    _pos(Vec2{ static_cast<float>(GlobalValues::CENTER_X), static_cast<float>(GlobalValues::OUT_HEIGHT) * 0.8f }),
    _counter(0),
    _move_dir(Vec2{})
{
    _bullet_manager = manager;
}

bool Player::update() {
    ++_counter;
    move();
    shot();
    return true;
}

void Player::draw() const {
    auto img_manager = ImageManager::get_instance();
    // 
    size_t idx = 0;
    if (_move_dir.x > 0.0) idx = 2;
    if (_move_dir.x < 0.0) idx = 4;
    idx += (_counter / 15) % 2 == 0 ? 0 : 1;
    utils::DrawRotaGraphF_Screen(_pos.x, _pos.y, 1.0, 0.0, img_manager->get_player_a()[idx], 1);
}
void Player::move()
{
    float move_x = 0, move_y = 0;
    auto pad_ins = PadInput::get_instance();
    if (pad_ins->get(Left) > 0) {
        move_x -= SPEED;
    }
    if (pad_ins->get(Right) > 0) {
        move_x += SPEED;
    }
    if (pad_ins->get(Down) > 0) {
        move_y += SPEED;
    }
    if (pad_ins->get(Up) > 0) {
        move_y -= SPEED;
    }
    //ŽÎ‚ßˆÚ“®
    if (move_x && move_y) {
        move_x /= sqrtf(2.0);
        move_y /= sqrtf(2.0);
    }
    if (pad_ins->get(Slow) > 0) {
        move_x /= 3.0f;
        move_y /= 3.0f;
    }
    _move_dir = Vec2{ move_x, move_y };
    _pos += _move_dir;
    // ƒQ[ƒ€À•W‚Ìã‰º”½“]‚É‹C‚ð‚Â‚¯‚é
    const float IN_TOP_LEFT_X = GlobalValues::IN_TOP_LEFT_X;
    const float IN_TOP_LEFT_Y = GlobalValues::IN_TOP_LEFT_Y;
    const float IN_BOTTOM_RIGHT_X = GlobalValues::IN_TOP_LEFT_X + GlobalValues::IN_WIDTH;
    const float IN_BOTTOM_RIGHT_Y = GlobalValues::IN_TOP_LEFT_Y + GlobalValues::IN_HEIGHT;
    _pos = _pos.clamp(Vec2{ IN_TOP_LEFT_X, IN_TOP_LEFT_Y }, Vec2{ IN_BOTTOM_RIGHT_X, IN_BOTTOM_RIGHT_Y });
}

void Player::shot() {
    constexpr float SHOT_POS_X[4] = { -10.0, 10.0, -30.0, 30.0 };
    constexpr float SHOT_POS_Y[4] = { -30.0, -30.0, -10.0, -10.0 };
    constexpr int POWER = 15;
    auto pad_ins = PadInput::get_instance();
    if (pad_ins->get(Shot) > 0 && pad_ins->get(Shot) % 5 == 0) {
        for (int i = 0; i < 4; ++i) {
            if (pad_ins->get(Slow) > 0) {
                _bullet_manager->push_bullet(POWER, Vec2{ SHOT_POS_X[i] / 3.0f, SHOT_POS_Y[i] / 2.0f } + this->_pos);
            }
            else {
                _bullet_manager->push_bullet(POWER, Vec2{ SHOT_POS_X[i], SHOT_POS_Y[i] } + this->_pos);

            }
        }
    }
}
