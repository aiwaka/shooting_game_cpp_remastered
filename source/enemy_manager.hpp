#pragma once

#include <memory>
#include <list>
#include "abstract_enemy.hpp"
#include "task.hpp"

class EnemyManager : public Task {
public:
    EnemyManager();
    virtual ~EnemyManager() = default;
    bool update() override;
    void draw() const override;

private:
    std::list<std::shared_ptr<AbstractEnemy>> _list;
};

