#pragma once

#include <memory>
#include "abstract_scene.hpp"
#include "player.hpp"
#include "board.hpp"
#include "abstract_bg.hpp"
#include "background.hpp"
#include "enemy_manager.hpp"
#include "enemy_bullet.hpp"
#include "enemy_bullet_manager.hpp"
#include "boss_manager.hpp"
#include "player_bullet.hpp"
#include "player_bullet_manager.hpp"
#include "abstract_effect.hpp"
#include "effect_manager.hpp"
#include "item_manager.hpp"

class GameScene : public AbstractScene {
public:
    // パラメータのラベルとして利用する
    const static char* param_tag_stage;
    const static char* param_tag_level;

    GameScene(IOnSceneChangedListener* impl, const SceneParameter& param);
    virtual ~GameScene() = default;

    void update() override;
    void draw() const override;

    //! @brief 自機の位置を問い合わせられるようにする
    Vec2 get_player_pos() const;
    //! @brief ボード表示用にプレイヤーの情報を取得する.
    //! @return [スコア, HP, ショットパワー, 残機, ボム]が整数で返る.
    std::array<int, 5> get_player_info_for_board() const;
    //! @brief 敵全体へのポインタを取得できる
    std::list<std::shared_ptr<AbstractEnemy>> get_all_enemies_iterator() const;
    //! @brief ボス全体へのポインタを取得できる
    std::list<std::shared_ptr<Boss>> get_all_boss_iterator() const;

    void modify_score(int delta);
    void modify_player_hp(int delta);
    void modify_player_power(int delta);
    void increment_player_life();
    void increment_player_bomb();

    //! @brief 敵管理クラスのカウンタを取得する
    int get_enemy_manager_counter() const;
    //! @brief ボス出現中か？
    bool boss_exist();

    //! @brief エフェクトを登録する
    void set_effect(std::shared_ptr<AbstractEffect> effect);
    //! @brief アイテムを出現させる
    void spawn_items(std::array<int, 6>& items, Vec2 pos);
private:
    int _stage;
    // シーンにカウンタを用意すると色々煩雑になりそう
    //int _counter;
    // スコアはゲームシーンとして管理する
    int _score;
    //int _level;
    // ここでシーン内で動かすものへのポインタを保持しておき, updateやdrawを適用することで更新を行っていく.
    std::shared_ptr<Player> _player;
    std::shared_ptr<Board> _board;
    std::shared_ptr<AbstractBackground> _background;
    std::shared_ptr<EnemyManager> _enemy_manager;
    std::shared_ptr<EnemyBulletManager> _enemy_bullet_manager;
    std::shared_ptr<PlayerBulletManager> _player_bullet_manager;
    std::shared_ptr<EffectManager> _effect_manager;
    std::shared_ptr<ItemManager> _item_manager;
    std::shared_ptr<BossManager> _boss_manager;
};

inline int GameScene::get_enemy_manager_counter() const { return _enemy_manager->get_counter(); }

inline void GameScene::modify_score(int delta) { _score += delta; }
inline void GameScene::modify_player_hp(int delta) { _player->modify_hp(delta); }

inline void GameScene::modify_player_power(int delta) { _player->modify_power(delta); }
inline void GameScene::increment_player_life() { _player->increment_life(); }
inline void GameScene::increment_player_bomb() { _player->increment_bomb(); }

inline bool GameScene::boss_exist() { return _boss_manager->boss_exist(); }
