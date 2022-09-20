#pragma once

#include "enemy_manager.hpp"
#include "abstract_enemy.hpp"

class EnemyA final : public AbstractEnemy {
public:
    EnemyA(EnemyInfo& info);
    ~EnemyA() = default;
    void draw() const override;

protected:
    void set_size() override;
};
