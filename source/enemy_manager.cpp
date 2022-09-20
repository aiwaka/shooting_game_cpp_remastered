#include "enemy_manager.hpp"
#include "global_define.hpp"

EnemyManager::EnemyManager() {
    _list.emplace_back(std::make_shared<Enemy>(GlobalValues::CENTER_X, 100.0));
}

bool EnemyManager::update() {
    for (auto enemy : _list) {
        enemy->update();
    }
    return true;
}

void EnemyManager::draw() const {
    for (const auto enemy : _list) {
        enemy->draw();
    }
}
