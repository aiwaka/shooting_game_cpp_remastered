#pragma once

#include "task.hpp"
#include "euclid_vec.hpp"

class Enemy : public Task {
public:
    Enemy(float x, float y);
    virtual ~Enemy() = default;
    bool update() override;
    void draw() const override;

protected:
    Vec2 _pos;
    Vec2 _speed;
};
