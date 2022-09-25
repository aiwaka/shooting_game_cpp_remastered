#pragma once

#include <memory>
#include <list>
#include <array>
#include "enemy_bullet.hpp"
#include "task.hpp"

// 循環参照回避用の宣言
class GameScene;
class Boss;
class EnemyBulletManager;

class BossManager : public Task {
public:
    BossManager(GameScene* scene, std::shared_ptr<EnemyBulletManager> bullet_manager);
    virtual ~BossManager() = default;
    bool update() override;
    void draw() const override;

    bool boss_exist() const;

    Vec2 get_player_pos() const;

    void push_bullet(std::shared_ptr<EnemyBullet> bullet);

    std::list<std::shared_ptr<Boss>> get_all_boss_iterator() const;

    // //! @brief 敵撃破エフェクトをセット
    //void set_destroy_effect(Vec2 pos, int color);
    // //! @brief アイテムを出現させる
    //void spawn_items(std::array<int, 6> items, Vec2 pos);

private:
    GameScene* _game_scene;
    std::shared_ptr<EnemyBulletManager> _enemy_bullet_manager;
    int _counter;

    int _hp_bar_handle;

    std::list<std::shared_ptr<Boss>> _list;
    //! @brief ボスを定刻に登録する.
    void register_boss();
};


inline std::list<std::shared_ptr<Boss>> BossManager::get_all_boss_iterator() const { return _list; }
