#pragma once

#include <array>
#include "task.hpp"
#include "euclid_vec.hpp"
#include "enemy_mover.hpp"

class EnemyMover;

struct EnemyInfo;

class AbstractEnemy : public Task {
public:
    AbstractEnemy(const EnemyInfo& info);
    virtual ~AbstractEnemy() = default;
    void initialize();
    bool update() override;

    Vec2 get_pos() const;
    void set_pos(Vec2 pos);
    int get_counter() const;
    Vec2 get_speed() const;
    void set_speed(Vec2 speed);
    int get_move_pattern() const;
    int get_enemy_type_id() const;
    int get_start_fire_count() const;
    int get_fire_pattern_id() const;
    int get_hp() const;
    void modify_hp(int delta);
    int get_bullet_id() const;
    int get_bullet_color() const;
    std::array<int, 6> get_item_id() const;


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
    int _hp;
    int _bullet_id;
    int _bullet_color;
    //! @brief �ړ��Ŏg���A�ҋ@����
    int _wait_time;
    //! @brief �A�C�e��id��6�܂œ������.
    std::array<int, 6> _item_slot;

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
inline int AbstractEnemy::get_enemy_type_id() const { return _enemy_type_id; }
inline int AbstractEnemy::get_start_fire_count() const { return _start_fire_count; }
inline int AbstractEnemy::get_fire_pattern_id() const { return _fire_pattern_id; }
inline int AbstractEnemy::get_hp() const { return _hp; }
inline void AbstractEnemy::modify_hp(int delta) { _hp += delta; }
inline int AbstractEnemy::get_bullet_id() const { return _bullet_id; }
inline int AbstractEnemy::get_bullet_color() const { return _bullet_color; }
inline std::array<int, 6> AbstractEnemy::get_item_id() const { return _item_slot; }
