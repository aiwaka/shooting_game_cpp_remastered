#pragma once

#include <memory>
#include "task.hpp"
#include "euclid_vec.hpp"

class PlayerBulletManager;

class Player : public Task {
public:
    Player(std::shared_ptr<PlayerBulletManager> manager);
    virtual ~Player() = default;
    bool update() override;
    void draw() const override;

    Vec2 get_pos() const;
    int get_power() const;
    int get_hp() const;
    int get_max_hp() const;
    void modify_hp(int delta);
    int get_player_state() const;
    int get_lives_num() const;
    int get_bombs_num() const;

private:
    void move();
    void shot();

    std::shared_ptr<PlayerBulletManager>_bullet_manager;

    Vec2 _pos;
    int _counter;
    //! @brief ���̃t���[���ł̈ړ�����.
    Vec2 _move_dir;
    int _hp;
    int _max_hp;
    //! @brief �U����
    int _power;
    //! @brief �v���C���[���. 0�͒ʏ�, 1�͖��G, 2�Ȃ畜�A��
    int _state;
    int _lives_num; // �c�@
    int _bombs_num;
};

inline Vec2 Player::get_pos() const { return _pos; }
inline int Player::get_power() const { return _power; }
inline int Player::get_hp() const { return _hp; }
inline int Player::get_max_hp() const { return _max_hp; }
inline int Player::get_player_state() const { return _state; }
inline int Player::get_lives_num() const { return _lives_num; }
inline int Player::get_bombs_num() const { return _bombs_num; }
