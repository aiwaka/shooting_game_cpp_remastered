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
    //! @brief �G�Ǘ��N���X�̓Q�[���V�[���ւ̃|�C���^������. ����ɂ����J���ꂽ���Ɍ����ēG�Ǘ��N���X���l�X�ȏ��ɃA�N�Z�X�ł���.
    GameScene* _game_scene;
    int _counter;
    std::list<std::shared_ptr<AbstractEffect>> _list;
};

