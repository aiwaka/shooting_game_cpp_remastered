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
    // �p�����[�^�̃��x���Ƃ��ė��p����
    const static char* param_tag_stage;
    const static char* param_tag_level;

    GameScene(IOnSceneChangedListener* impl, const SceneParameter& param);
    virtual ~GameScene() = default;

    void update() override;
    void draw() const override;

    //! @brief ���@�̈ʒu��₢���킹����悤�ɂ���
    Vec2 get_player_pos() const;
    //! @brief �{�[�h�\���p�Ƀv���C���[�̏����擾����.
    //! @return [�X�R�A, HP, �V���b�g�p���[, �c�@, �{��]�������ŕԂ�.
    std::array<int, 5> get_player_info_for_board() const;
    //! @brief �G�S�̂ւ̃|�C���^���擾�ł���
    std::list<std::shared_ptr<AbstractEnemy>> get_all_enemies_iterator() const;
    //! @brief �{�X�S�̂ւ̃|�C���^���擾�ł���
    std::list<std::shared_ptr<Boss>> get_all_boss_iterator() const;

    void modify_score(int delta);
    void modify_player_hp(int delta);
    void modify_player_power(int delta);
    void increment_player_life();
    void increment_player_bomb();

    //! @brief �G�Ǘ��N���X�̃J�E���^���擾����
    int get_enemy_manager_counter() const;
    //! @brief �{�X�o�������H
    bool boss_exist();

    //! @brief �G�t�F�N�g��o�^����
    void set_effect(std::shared_ptr<AbstractEffect> effect);
    //! @brief �A�C�e�����o��������
    void spawn_items(std::array<int, 6>& items, Vec2 pos);
private:
    int _stage;
    // �V�[���ɃJ�E���^��p�ӂ���ƐF�X�ώG�ɂȂ肻��
    //int _counter;
    // �X�R�A�̓Q�[���V�[���Ƃ��ĊǗ�����
    int _score;
    //int _level;
    // �����ŃV�[�����œ��������̂ւ̃|�C���^��ێ����Ă���, update��draw��K�p���邱�ƂōX�V���s���Ă���.
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
