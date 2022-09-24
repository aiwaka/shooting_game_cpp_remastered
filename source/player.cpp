#include <DxLib.h>

#include "global_define.hpp"
#include "player.hpp"
#include "pad_input.hpp"
#include "player_bullet_manager.hpp"
#include "image_manager.hpp"
#include "utils.hpp"

namespace {
    constexpr float SPEED = 6.0f;
    constexpr int PLAYER_MAX_HP = 99;
}

Player::Player(std::shared_ptr<PlayerBulletManager> manager) :
    _pos(Vec2{ static_cast<float>(GlobalValues::CENTER_X), static_cast<float>(GlobalValues::OUT_HEIGHT) * 0.8f }),
    _counter(0),
    _move_dir(Vec2{}),
    _power(15),
    _hp(PLAYER_MAX_HP),
    _max_hp(PLAYER_MAX_HP),
    _lives_num(2),
    _bombs_num(2),
    _state(0),
    _invincible_counter(0)
{
    _bullet_manager = manager;
}

bool Player::update() {
    ++_counter;
    // 無敵カウンタが有効なら減らす
    if (_invincible_counter > 0) --_invincible_counter;
    if (_hp == 0) {
        // 死んだらカウンターを0にして状態を2にする
        _counter = 0;
        _invincible_counter = 180;
        _hp = _max_hp;
        _state = 2;
    }
    if (_state == 2) { move_in_dead(); }
    else { move(); }
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
    // 無敵中は点滅させる
    bool draw_player = true;
    draw_player = (_invincible_counter / 2) % 2 == 0;
    if (draw_player) {
        utils::DrawRotaGraphF_Screen(_pos.x, _pos.y, 1.0, 0.0, img_manager->get_player_a()[idx], 1);
    }
}
void Player::move()
{
    if (_state == 2) return;
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
    //斜め移動
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
    // ゲーム座標の上下反転に気をつける
    const float IN_TOP_LEFT_X = GlobalValues::IN_TOP_LEFT_X;
    const float IN_TOP_LEFT_Y = GlobalValues::IN_TOP_LEFT_Y;
    const float IN_BOTTOM_RIGHT_X = GlobalValues::IN_TOP_LEFT_X + GlobalValues::IN_WIDTH;
    const float IN_BOTTOM_RIGHT_Y = GlobalValues::IN_TOP_LEFT_Y + GlobalValues::IN_HEIGHT;
    _pos = _pos.clamp(Vec2{ IN_TOP_LEFT_X, IN_TOP_LEFT_Y }, Vec2{ IN_BOTTOM_RIGHT_X, IN_BOTTOM_RIGHT_Y });
}

void Player::shot() {
    if (_state == 2) return;
    constexpr float SHOT_POS_X[4] = { -10.0, 10.0, -30.0, 30.0 };
    constexpr float SHOT_POS_Y[4] = { -30.0, -30.0, -10.0, -10.0 };
    auto pad_ins = PadInput::get_instance();
    if (pad_ins->get(Shot) > 0 && pad_ins->get(Shot) % 5 == 0) {
        for (int i = 0; i < 4; ++i) {
            if (pad_ins->get(Slow) > 0) {
                _bullet_manager->push_bullet(_power, Vec2{ SHOT_POS_X[i] / 3.0f, SHOT_POS_Y[i] / 2.0f } + this->_pos);
            }
            else {
                _bullet_manager->push_bullet(_power, Vec2{ SHOT_POS_X[i], SHOT_POS_Y[i] } + this->_pos);

            }
        }
    }
}

void Player::move_in_dead() {
    if (_counter == 0) {
        _pos = Vec2{ static_cast<float>(GlobalValues::CENTER_X), static_cast<float>(GlobalValues::OUT_HEIGHT) * 0.8f + 60 };
    }
    _pos -= Vec2{ 0.0, 1.0 };
    if (_counter >= 60) {
        auto pad_ins = PadInput::get_instance();
        if (pad_ins->get(Up) + pad_ins->get(Down) + pad_ins->get(Left) + pad_ins->get(Right) > 0) {
            _state = 0;
        }
    }
    if (_counter == 180) {
        _state = 0;
    }
}


void Player::modify_hp(int delta) {
    if (_invincible_counter > 0) return;
    _hp = utils::clamp(_hp + delta, 0, _max_hp);
}
