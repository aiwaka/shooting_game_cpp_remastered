#pragma once

#include "task.hpp"
#include "euclid_vec.hpp"

class EnemyBulletManager;
struct EnemyBulletInfo;
class AbstractEnemy;

class EnemyBullet : public Task {
public:
    // parent�͎g���Ă��Ȃ��̂ŏ����Ă��܂��΂悳����
    //EnemyBullet(const EnemyBulletInfo& info, AbstractEnemy* parent);
    EnemyBullet(const EnemyBulletInfo& info);
    virtual ~EnemyBullet() = default;
    bool update() override;
    void draw() const override;

    int get_counter() const;
    int get_type() const;
    Vec2 get_pos() const;
    int get_damage() const;
    int get_color() const;

    void set_pos(Vec2 pos);
    void set_speed(float speed);
    void set_acc(float acc);
    void set_omega(float omega);
    void set_fx(int num);


    bool get_delete_flag() const;
    void set_delete_flag();

private:
    bool is_inside_field() const;

    // //! @brief �����������Ă���e�ւ̃|�C���^
    //AbstractEnemy* _parent;

    int _counter;
    Vec2 _pos;
    float _angle;
    float _speed;
    float _omega;
    float _acceleration;

    int _type;
    int _color;
    int _handle;
    //! @brief ��ʊO�ɂ��Ă���������Ȃ��J�E���g
    int _endure_count;
    int _damage;
    int _fx_detail;
    bool _bomb_regist;

    //! @brief ���ꂪtrue�ɂȂ����ꍇ�X�V���������ɏ������Ƃɂ���
    bool _delete_flag;
};

inline bool EnemyBullet::get_delete_flag() const { return _delete_flag; }
inline void EnemyBullet::set_delete_flag() { _delete_flag = true; }
inline int EnemyBullet::get_damage() const { return _damage; }
inline void EnemyBullet::set_pos(Vec2 pos) { _pos = pos; }
inline void EnemyBullet::set_speed(float speed) { _speed = speed; }
inline void EnemyBullet::set_acc(float acc) { _acceleration = acc; }
inline void EnemyBullet::set_omega(float omega) { _omega = omega; }
inline void EnemyBullet::set_fx(int num) { _fx_detail = num; }
inline int EnemyBullet::get_color() const { return _color; }
