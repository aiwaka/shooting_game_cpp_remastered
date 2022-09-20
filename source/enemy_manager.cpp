#include <DxLib.h>
#include "enemy_manager.hpp"
#include "global_define.hpp"
#include "enemy_a.hpp"
#include "enemy_b.hpp"

EnemyManager::EnemyManager() {
    _list.emplace_back(std::make_shared<EnemyA>(GlobalValues::CENTER_X, 100.0));
    _list.emplace_back(std::make_shared<EnemyB>(GlobalValues::CENTER_X - 100.0, 100.0));

    for (auto enemy : _list) {
        enemy->initialize();
    }
}

bool EnemyManager::update() {
    for (auto iter = _list.begin(); iter != _list.end();) {
        if (!((*iter)->update())) {
            // イテレータを用いてループして, updateがfalseになったものが取り除かれるように
            iter = _list.erase(iter);
        }
        else {
            ++iter;
        }
    }
    return true;
}

void EnemyManager::draw() const {
    DrawFormatString(0, 20, GetColor(255, 255, 255), "敵の数 : %d", _list.size());
    for (const auto enemy : _list) {
        enemy->draw();
    }
}
