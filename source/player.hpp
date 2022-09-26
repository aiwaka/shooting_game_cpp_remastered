#pragma once

#include <memory>
#include "task.hpp"
#include "euclid_vec.hpp"

class GameScene;
class PlayerBulletManager;

class Player : public Task {
public:
    Player(GameScene* scene, std::shared_ptr<PlayerBulletManager> manager, int max_hp);
    virtual ~Player() = default;
    bool update() override;
    void draw() const override;

    Vec2 get_pos() const;
    int get_power() const;
    int get_hp() const;
    int get_max_hp() const;
    void modify_hp(int delta);
    void modify_power(int delta);
    void increment_life();
    void increment_bomb();
    int get_player_state() const;
    //int get_invincible_counter() const;
    //void set_invincible_counter(int count);
    int get_lives_num() const;
    int get_bombs_num() const;

private:
    GameScene* _game_scene;
    void move();
    void shot();
    //! @brief stateが2, 死亡中の移動操作をする
    void move_in_dead();

    std::shared_ptr<PlayerBulletManager>_bullet_manager;

    Vec2 _pos;
    int _counter;
    //! @brief このフレームでの移動方向.
    Vec2 _move_dir;
    int _hp;
    int _max_hp;
    //! @brief 攻撃力
    int _power;
    //! @brief プレイヤー状態. 0は通常, 1は無敵, 2なら復帰中
    int _state;
    //! @brief 無敵カウント. 0より大きいならば無敵であり, 毎フレーム減少する.
    int _invincible_counter;
    int _lives_num; // 残機
    int _bombs_num;
    bool _bombing;
};

inline Vec2 Player::get_pos() const { return _pos; }
inline int Player::get_power() const { return _power; }
inline int Player::get_hp() const { return _hp; }
inline int Player::get_max_hp() const { return _max_hp; }
inline int Player::get_player_state() const { return _state; }
inline int Player::get_lives_num() const { return _lives_num; }
inline int Player::get_bombs_num() const { return _bombs_num; }

inline void Player::modify_power(int delta) { _power += delta; }
inline void Player::increment_life() { ++_lives_num; }
inline void Player::increment_bomb() { ++_bombs_num; }

//inline int Player::get_invincible_counter() const { return _invincible_counter; }
//inline void Player::set_invincible_counter(int count) { _invincible_counter = count; }
