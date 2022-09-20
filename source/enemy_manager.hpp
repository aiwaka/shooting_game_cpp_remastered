#pragma once

#include <memory>
#include <list>
#include <string>
#include "abstract_enemy.hpp"
#include "task.hpp"

/**
 * @brief �G�̏o����ړ��E�U�����̏����i�[����\����. �t�@�C������ǂݍ���ō쐬��, ���̂̐����Ɏg��
 */
struct EnemyInfo {
    // _speed�͕s�v�Ǝv����̂Ō�ŏ���
    int spawn_count, move_pattern, enemy_type, start_fire_count, fire_pattern, bullet_id, bullet_color, hp, wait_time;
    float x, y, _speed;
    int item[6];
};

class EnemyManager : public Task {
public:
    EnemyManager();
    virtual ~EnemyManager() = default;
    bool update() override;
    void draw() const override;

private:
    /**
     * @brief �G�̏o������csv�t�@�C������ǂݍ���Ŋi�[����.
     * @brief csv�̏����̓f�[�^�t�@�C�����̂��Q�Ƃ̂���.
     */
    void load_enemy_story(std::string filename);
    std::list<std::shared_ptr<AbstractEnemy>> _list;
    std::list<EnemyInfo> _enemy_info_list;

};

