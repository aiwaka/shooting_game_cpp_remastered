#pragma once

#include <memory>
#include <list>
#include <string>
#include <array>
#include "abstract_enemy.hpp"
#include "task.hpp"

// �z�Q�Ɖ��p�̐錾
class GameScene;

/**
 * @brief �G�̏o����ړ��E�U�����̏����i�[����\����. �t�@�C������ǂݍ���ō쐬��, ���̂̐����Ɏg��
 */
struct EnemyInfo {
    // _speed, wait_time�͕s�v�Ǝv����̂Ō�ŏ���
    int spawn_count, move_pattern, enemy_type, start_fire_count, fire_pattern, bullet_id, bullet_color, hp, wait_time;
    float x, y, _speed;
    std::array<int, 6> item;
};

class EnemyManager : public Task {
public:
    EnemyManager(GameScene* scene);
    virtual ~EnemyManager() = default;
    bool update() override;
    void draw() const override;

    Vec2 get_player_pos() const;

private:
    //! @brief �G�Ǘ��N���X�̓Q�[���V�[���ւ̃|�C���^������. ����ɂ����J���ꂽ���Ɍ����ēG�Ǘ��N���X���l�X�ȏ��ɃA�N�Z�X�ł���.
    GameScene* _game_scene;
    int _counter;
    /**
     * @brief �G�̏o������csv�t�@�C������ǂݍ���Ŋi�[����.
     * @brief csv�̏����̓f�[�^�t�@�C�����̂��Q�Ƃ̂���.
     */
    void load_enemy_story(std::string filename);
    std::list<std::shared_ptr<AbstractEnemy>> _list;
    std::list<EnemyInfo> _enemy_info_list;

};

