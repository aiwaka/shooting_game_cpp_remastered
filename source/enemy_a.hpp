#pragma once

#include "abstract_enemy.hpp"

class EnemyA final : public AbstractEnemy {
public:
    EnemyA(float x, float y);
    ~EnemyA() = default;
    void draw() const override;

protected:
    void set_size() override;
};
