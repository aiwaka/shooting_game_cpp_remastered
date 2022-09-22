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
    //! @brief “G‚Æ‚Ì“–‚½‚è”»’è‚ğs‚¢, “G‚Éƒ_ƒ[ƒW‚ğ—^‚¦‚é–½—ß‚Æ©‹@’e‚ğÁ–Å‚³‚¹‚é–½—ß‚ğ‘—‚é.
    void collision_against_enemies();

    GameScene* _game_scene;
    int _counter;
    std::list<std::shared_ptr<PlayerBullet>> _bullet_list;
};
