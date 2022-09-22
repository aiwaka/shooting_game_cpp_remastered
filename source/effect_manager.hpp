#pragma once

#include <memory>
#include <list>
#include "task.hpp"
#include "euclid_vec.hpp"

class AbstractEffect;
class GameScene;

class EffectManager : public Task {
public:
    EffectManager(GameScene* scene);
    virtual ~EffectManager() = default;
    bool update() override;
    void draw() const override;

    void push_effect(std::shared_ptr<AbstractEffect> effect);
private:
    //! @brief 敵管理クラスはゲームシーンへのポインタを持つ. これにより公開された情報に限って敵管理クラスが様々な情報にアクセスできる.
    GameScene* _game_scene;
    int _counter;
    std::list<std::shared_ptr<AbstractEffect>> _list;
};

