#pragma once

#include <memory>
#include <list>
#include "task.hpp"
#include "euclid_vec.hpp"

class GameScene;
class Player;
class PlayerBullet;

class PlayerBulletManager : public Task {
public:
    PlayerBulletManager(GameScene* scene);
    virtual ~PlayerBulletManager() = default;
    bool update() override;
    void draw() const override;

    void push_bullet(int power, Vec2 pos);

private:
    //! @brief �G�Ƃ̓����蔻����s��, �G�Ƀ_���[�W��^���閽�߂Ǝ��@�e�����ł����閽�߂𑗂�.
    void collision_against_enemies();

    GameScene* _game_scene;
    int _counter;
    std::list<std::shared_ptr<PlayerBullet>> _bullet_list;
};
