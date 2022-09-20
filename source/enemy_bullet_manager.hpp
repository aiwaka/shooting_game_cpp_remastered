#pragma once

#include <memory>
#include <list>
#include "task.hpp"
#include "enemy_bullet.hpp"

struct EnemyBulletInfo {
    int bullet_type, color, endure_count, damage, rotating, fx_detail;
    float x, y, angle, speed, omega, acceleration, base_angle, temp_speed;
    bool bomb_regist;
};

//class AbstractEnemy;
//class GameScene;
//
//class EnemyBulletManager : public Task {
//public:
//    EnemyBulletManager(GameScene* scene);
//    virtual ~EnemyBulletManager() = default;
//    bool update() override;
//    void draw() const override;
//
//    Vec2 get_player_pos() const;
//
//    void push_bullet(std::shared_ptr<EnemyBullet> bullet);
//
//private:
//    //! @brief 敵の弾管理クラスはゲームシーンへのポインタを持つ. これにより公開された情報に限って敵管理クラスが様々な情報にアクセスできる.
//    GameScene* _game_scene;
//    int _counter;
//    std::list<std::shared_ptr<EnemyBullet>> _bullet_list;
//
//};
