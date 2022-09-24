#pragma once

#include "abstract_effect.hpp"
#include "effect_manager.hpp"
#include "euclid_vec.hpp"


class BombEffect final : public AbstractEffect {
public:
    BombEffect(Vec2 pos);
    ~BombEffect() = default;
    bool update() override;
    void draw() const override;

private:
    int _handle;
    int _black_handle;
    float _ex_rate;
    float _angle;
    Vec2 _pos;
};
