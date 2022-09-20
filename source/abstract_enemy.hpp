#pragma once

#include "task.hpp"
#include "euclid_vec.hpp"
#include "enemy_mover.hpp"

class EnemyMover;

class AbstractEnemy : public Task {
public:
    AbstractEnemy(float x, float y);
    virtual ~AbstractEnemy() = default;
    void initialize();
    bool update() override;

    Vec2 get_pos() const;
    void set_pos(Vec2 pos);
    int get_counter() const;
    Vec2 get_speed() const;
    void set_speed(Vec2 speed);
    int get_move_pattern() const;

protected:
    virtual void set_size() = 0;
    /**
     * @brief ���݈ʒu����ʓ����ǂ���
     */
    bool is_inside_field() const;

    EnemyMover _mover;

    int _counter;
    int _move_pattern_id;
    int _enemy_type_id;
    Vec2 _pos;
    Vec2 _speed;
    //! @brief �e���������n�߂�J�E���g
    int _start_fire_count;
    int _fire_pattern_id;
    int hp;
    int _bullet_id;
    int _bullet_color;
    //! @brief �ړ��Ŏg���A�ҋ@����
    int _wait_time;
    //! @brief �A�C�e��id��6�܂œ������.
    int _item_slot[6];

    //! @brief �e�N�X�`���̑傫��
    int _texture_width;
    int _texture_height;

};

inline Vec2 AbstractEnemy::get_pos() const { return _pos; }
inline void AbstractEnemy::set_pos(Vec2 pos) { _pos = pos; }
inline int AbstractEnemy::get_counter() const { return _counter; }
inline Vec2 AbstractEnemy::get_speed() const { return _speed; }
inline void AbstractEnemy::set_speed(Vec2 speed) { _speed = speed; }
inline int AbstractEnemy::get_move_pattern() const { return _move_pattern_id; }
