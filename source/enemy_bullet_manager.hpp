#pragma once

#include <memory>
#include <list>
#include "task.hpp"
#include "enemy_bullet.hpp"

struct EnemyBulletInfo {
    int bullet_type = 0, color = 0, endure_count = 0, damage = 0, rotating = 0, fx_detail = 0;
    float x = 0.0, y = 0.0, angle = 0.0, speed = 0.0, omega = 0.0, acceleration = 0.0, temp_speed = 0.0;
    bool bomb_regist = false;
};

class AbstractEnemy;
class GameScene;

class EnemyBulletManager : public Task {
public:
    EnemyBulletManager(GameScene* scene);
    virtual ~EnemyBulletManager() = default;
    bool update() override;
    void draw() const override;

    Vec2 get_player_pos() const;

    void push_bullet(std::shared_ptr<EnemyBullet> bullet);

private:
    //! @brief �G�̒e�Ǘ��N���X�̓Q�[���V�[���ւ̃|�C���^������. ����ɂ����J���ꂽ���Ɍ����ēG�Ǘ��N���X���l�X�ȏ��ɃA�N�Z�X�ł���.
    GameScene* _game_scene;
    int _counter;
    std::list<std::shared_ptr<EnemyBullet>> _bullet_list;

    //! @brief ���@�ƓG�e�̓����蔻����s��, ���@�Ƀ_���[�W��^���閽�߂�^���G�e������
    void collision_against_player();

};
