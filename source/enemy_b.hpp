#pragma once

#include "abstract_enemy.hpp"

class EnemyB final : public AbstractEnemy {
public:
    EnemyB(float x, float y);
    ~EnemyB() = default;
    void draw() const override;

protected:
    void set_size() override;
};
