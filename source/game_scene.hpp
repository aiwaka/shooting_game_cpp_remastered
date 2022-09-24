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
#include "player_bullet.hpp"
#include "player_bullet_manager.hpp"
#include "abstract_effect.hpp"
#include "effect_manager.hpp"
#include "item_manager.hpp"

class GameScene : public AbstractScene {
public:
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

    void modify_score(int delta);
    void modify_player_hp(int delta);

    //! @brief エフェクトを登録する
    void set_effect(std::shared_ptr<AbstractEffect> effect);
    //! @brief アイテムを出現させる
    void spawn_items(std::array<int, 6>& items, Vec2 pos);
private:
    // スコアはゲームシーンとして管理する
    int _score;
    //int _level;
    // ここでシーン内で動かすものへのポインタを保持しておき, updateやdrawを適用することで更新を行っていく.
    std::shared_ptr<Player> _player;
    std::shared_ptr<Board> _board;
    std::shared_ptr<AbstractBackground> _background;
    std::shared_ptr<EnemyManager> _enemy_manager;
    std::shared_ptr<PlayerBulletManager> _player_bullet_manager;
    std::shared_ptr<EffectManager> _effect_manager;
    std::shared_ptr<ItemManager> _item_manager;
};


inline void GameScene::modify_score(int delta) { _score += delta; }
inline void GameScene::modify_player_hp(int delta) { _player->modify_hp(delta); }
