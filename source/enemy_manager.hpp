#pragma once

#include <memory>
#include <list>
#include <string>
#include <array>
#include "enemy_bullet.hpp"
#include "abstract_enemy.hpp"
#include "task.hpp"

// 循環参照回避用の宣言
class GameScene;
class EnemyBulletManager;

/**
 * @brief 敵の出現や移動・攻撃等の情報を格納する構造体. ファイルから読み込んで作成し, 実体の生成に使う
 */
struct EnemyInfo {
    // _speed, wait_timeは不要と思われるので後で消す
    int spawn_count, move_pattern, enemy_type, start_attack_count, attack_pattern, bullet_id, bullet_color, hp, wait_time;
    float x, y, _speed;
    std::array<int, 6> item;
};

class EnemyManager : public Task {
public:
    EnemyManager(GameScene* scene, std::shared_ptr<EnemyBulletManager> bullet_manager);
    virtual ~EnemyManager() = default;
    bool update() override;
    void draw() const override;

    Vec2 get_player_pos() const;

    void push_bullet(std::shared_ptr<EnemyBullet> bullet);
    //! @brief 敵全体へのポインタを取得できる
    std::list<std::shared_ptr<AbstractEnemy>> get_all_enemies_iterator() const;


    //! @brief 敵撃破エフェクトをセット
    void set_destroy_effect(Vec2 pos, int color);
    //! @brief アイテムを出現させる
    void spawn_items(std::array<int, 6> items, Vec2 pos);

private:
    //! @brief 敵管理クラスはゲームシーンへのポインタを持つ. これにより公開された情報に限って敵管理クラスが様々な情報にアクセスできる.
    GameScene* _game_scene;
    std::shared_ptr<EnemyBulletManager> _enemy_bullet_manager;
    int _counter;
    /**
     * @brief 敵の出現情報をcsvファイルから読み込んで格納する.
     * @brief csvの書式はデータファイル自体を参照のこと.
     */
    void load_enemy_story(std::string filename);
    std::list<std::shared_ptr<AbstractEnemy>> _list;
    /**
     * @brief 敵情報を一括で保存しておくためのリスト.
     * @brief これを毎フレーム読んで, 定刻に登録を行う.
     * @brief TODO: カウントがソートされている保証があれば速い実装に変更できる
     */
    std::list<EnemyInfo> _enemy_info_list;

};

