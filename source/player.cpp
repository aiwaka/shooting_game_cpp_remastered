#include <DxLib.h>

#include "global_define.hpp"
#include "player.hpp"
#include "pad_input.hpp"
#include "player_bullet_manager.hpp"
#include "game_scene.hpp"
#include "bomb_effect.hpp"
#include "image_manager.hpp"
#include "se_manager.hpp"
#include "utils.hpp"

namespace {
    constexpr float SPEED = 6.0f;
}

Player::Player(GameScene* scene, std::shared_ptr<PlayerBulletManager> manager, int max_hp) :
    _pos(Vec2{ static_cast<float>(GlobalValues::CENTER_X), static_cast<float>(GlobalValues::OUT_HEIGHT) * 0.8f }),
    _counter(0),
    _move_dir(Vec2{}),
    _power(15),
    _hp(max_hp),
    _max_hp(max_hp),
    _lives_num(2),
    _bombs_num(2),
    _state(0),
    _invincible_counter(0),
    _bombing(false)
{
    _game_scene = scene;
    _bullet_manager = manager;
}

bool Player::update() {
    // 残機0でhpが0になったことはゲームシーンが検知してシーン移動を行う
    // 無敵カウンタが有効なら減らす
    if (_invincible_counter > 0) --_invincible_counter;
    if (_bombing && _invincible_counter == 0) _bombing = false;
    if (_hp == 0) {
        // 死んだらカウンターを0にして状態を2にする
        SoundEffectManager::get_instance()->set_se(2);
        _counter = 0;
        _invincible_counter = 180;
        _hp = _max_hp;
        _state = 2;
        --_lives_num;
    }
    if (_state == 2) { move_in_dead(); }
    else { move(); }
    shot();
    ++_counter;
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
    // posは画面内座標になっているので複雑なことをしなくていい
    _pos = _pos.clamp(Vec2{ 0.0, 15.0 }, Vec2{ static_cast<float>(GlobalValues::IN_WIDTH), static_cast<float>(GlobalValues::IN_HEIGHT) });
}

void Player::shot() {
    if (_state == 2) return;

    auto pad_ins = PadInput::get_instance();
    auto se_mng_ins = SoundEffectManager::get_instance();
    // 先にボムを判定
    if (!_bombing && pad_ins->get(Bomb) == 1 && _bombs_num > 0) {
        --_bombs_num;
        _bombing = true;
        _invincible_counter = 170;
        auto bomb_eff = std::make_shared<BombEffect>(_pos);
        _game_scene->set_effect(bomb_eff);
        se_mng_ins->set_se(7);
        se_mng_ins->set_se(8);
        return;
    }

    constexpr float SHOT_POS_X[4] = { -10.0, 10.0, -30.0, 30.0 };
    constexpr float SHOT_POS_Y[4] = { -30.0, -30.0, -10.0, -10.0 };
    if (pad_ins->get(Shot) > 0 && pad_ins->get(Shot) % 5 == 0) {
        for (int i = 0; i < 4; ++i) {
            if (pad_ins->get(Slow) > 0) {
                _bullet_manager->push_bullet(_power, Vec2{ SHOT_POS_X[i] / 3.0f, SHOT_POS_Y[i] / 2.0f } + this->_pos);
            }
            else {
                _bullet_manager->push_bullet(_power, Vec2{ SHOT_POS_X[i], SHOT_POS_Y[i] } + this->_pos);
            }
        }
        se_mng_ins->set_se(1);
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
