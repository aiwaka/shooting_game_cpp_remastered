#pragma once

#include "task.hpp"
#include "euclid_vec.hpp"

class EnemyBulletManager;
struct EnemyBulletInfo;
class AbstractEnemy;

class EnemyBullet : public Task {
public:
    EnemyBullet(const EnemyBulletInfo& info, AbstractEnemy* parent);
    virtual ~EnemyBullet() = default;
    bool update() override;
    void draw() const override;

    int get_counter() const;

private:
    bool is_inside_field() const;

    //! @brief �����������Ă���e�ւ̃|�C���^
    AbstractEnemy* _parent;

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

};
