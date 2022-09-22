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

    void push_bullet(Player& player);
    //! @brief ���@�V���b�g�̃��X�g��Ԃ�
    std::list<std::shared_ptr<PlayerBullet>> get_all_player_bullet() const;

private:
    GameScene* _game_scene;
    int _counter;
    std::list<std::shared_ptr<PlayerBullet>> _bullet_list;
};
