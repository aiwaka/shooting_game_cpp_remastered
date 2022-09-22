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
    //! @brief 敵全体へのポインタを取得できる
    std::list<std::shared_ptr<AbstractEnemy>> get_all_enemies_iterator() const;

    //! @brief エフェクトを登録する
    void set_effect(std::shared_ptr<AbstractEffect> effect);
private:
    //int _level;
    // ここでシーン内で動かすものへのポインタを保持しておき, updateやdrawを適用することで更新を行っていく.
    std::shared_ptr<Player> _player;
    std::shared_ptr<Board> _board;
    std::shared_ptr<AbstractBackground> _background;
    std::shared_ptr<EnemyManager> _enemy_manager;
    std::shared_ptr<PlayerBulletManager> _player_bullet_manager;
    std::shared_ptr<EffectManager> _effect_manager;
};
