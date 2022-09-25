#pragma once

#include "task.hpp"
#include "euclid_vec.hpp"

class EnemyBulletManager;
struct EnemyBulletInfo;
class AbstractEnemy;

//! @brief �{�X���g���q�@�̃N���X
class BossChild : public Task {
public:
    BossChild(const EnemyBulletInfo& info);
    virtual ~BossChild() = default;
    bool update() override;
    void draw() const override;

    int get_counter() const;
    int get_state() const;
    Vec2 get_pos() const;
    void set_pos(Vec2 pos);
    float get_speed() const;
    void set_speed(float speed);
    float get_angle() const;
    void set_angle(float angle);

    // �q�@���������ǂ����͐e�Ɉς˂������ߌ��J����
    bool is_inside_field() const;
    //! @brief ������ĂԂƏI���t���O���������̃t���[���ŏ��������
    void delete_child();

private:
    int _counter;
    Vec2 _pos;
    float _angle;
    float _speed;
    float _omega;
    float _acceleration;

    // �e�^�C�v�̑���ɓK���Ɏg����ϐ�������
    int _state;
    int _handle;

    //! @brief ���ꂪtrue�ɂȂ����ꍇ�X�V���������ɏ������Ƃɂ���
    bool _delete_flag;
};

inline void BossChild::delete_child() { _delete_flag = true; }
inline int BossChild::get_counter() const { return this->_counter; }
inline Vec2 BossChild::get_pos() const { return this->_pos; }
inline  void BossChild::set_pos(Vec2 pos) { _pos = pos; }
inline float BossChild::get_speed() const { return _speed; }
inline void BossChild::set_speed(float speed) { _speed = speed; }
inline float BossChild::get_angle() const { return _angle; }
inline void BossChild::set_angle(float angle) { _angle = angle; }
inline int BossChild::get_state() const { return this->_state; }

