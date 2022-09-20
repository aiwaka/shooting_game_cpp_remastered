#pragma once

#include <memory>
#include <list>
#include "task.hpp"
#include "enemy.hpp"

class EnemyManager : public Task {
public:
    EnemyManager();
    virtual ~EnemyManager() = default;
    bool update() override;
    void draw() const override;

private:
    std::list<std::shared_ptr<Enemy>> _list;
};

