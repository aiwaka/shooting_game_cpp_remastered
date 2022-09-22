#pragma once

#include "abstract_effect.hpp"
#include "effect_manager.hpp"
#include "euclid_vec.hpp"


class DestroyEnemyEffect final : public AbstractEffect {
public:
    DestroyEnemyEffect(Vec2 pos, int color);
    ~DestroyEnemyEffect() = default;
    bool update() override;
    void draw() const override;

private:
    int _handle;
    float _ex_rate;
    float _angle;
    Vec2 _pos;
};
