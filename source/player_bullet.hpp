#pragma once

#include "task.hpp"
#include "euclid_vec.hpp"

class Player;

class PlayerBullet : public Task {
public:
    PlayerBullet(int power, Vec2 pos);
    virtual ~PlayerBullet() = default;
    bool update() override;
    void draw() const override;

    Vec2 get_pos() const;
    int get_power() const;

    void set_collide_flag();

private:
    bool is_inside_field() const;

    int _handle;

    int _power;
    int _counter;
    Vec2 _pos;
    float _angle;
    float _speed;

    //! @brief “G‚Æ‚Ô‚Â‚©‚Á‚½‚©‚Ç‚¤‚©‚Ìƒtƒ‰ƒO.
    bool _collided;
};
