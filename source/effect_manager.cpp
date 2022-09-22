#include <DxLib.h>
#include "effect_manager.hpp"
#include "global_define.hpp"
#include "game_scene.hpp"
#include "abstract_effect.hpp"
#include "destroy_enemy_effect.hpp"
#include "macro.hpp"

EffectManager::EffectManager(GameScene* scene) {
    _game_scene = scene;
    _counter = 0;
}

void EffectManager::push_effect(std::shared_ptr<AbstractEffect> effect) {
    this->_list.push_back(effect);
}

bool EffectManager::update() {
    for (auto iter = _list.begin(); iter != _list.end();) {
        // updateが正常に終了し, かつエフェクトが終了していないときは次へ
        if ((*iter)->update() && !(*iter)->is_finished()) {
            (*iter)->increment_counter();
            ++iter;
        }
        else {
            iter = _list.erase(iter);
        }
    }
    ++_counter;
    return true;
}

void EffectManager::draw() const {
    for (const auto Effect : _list) {
        Effect->draw();
    }
}