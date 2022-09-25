#include "player_bullet_manager.hpp"
#include "player.hpp"
#include "player_bullet.hpp"
#include "boss.hpp"
#include "game_scene.hpp"

PlayerBulletManager::PlayerBulletManager(GameScene* scene) : _counter(0) {
    _game_scene = scene;
    _bullet_list = std::list<std::shared_ptr<PlayerBullet>>(0);
}

bool PlayerBulletManager::update() {
    // �S�e���X�V, update��false�ŕԂ��Ă������̂͏�������
    for (auto iter = _bullet_list.begin(); iter != _bullet_list.end();) {
        if ((*iter)->update()) {
            ++iter;
        }
        else {
            iter = _bullet_list.erase(iter);
        }
    }
    // �����œ����蔻��������Ȃ�
    // �������̂������Ă��瓖���蔻����s��Ȃ���, �������Ă���̂Ɍ����Ȃ��Ƃ������Ƃ��N����͂�
    collision_against_enemies();
    collision_against_boss();
    ++_counter;
    return true;
}

void PlayerBulletManager::draw() const {
    //DrawFormatString(0, 90, GetColor(255, 255, 255), "���@�e�̐� : %d", _bullet_list.size());
    for (const auto bullet : _bullet_list) {
        bullet->draw();
    }
}

void PlayerBulletManager::push_bullet(int power, Vec2 pos) {
    auto bullet = std::make_shared<PlayerBullet>(power, pos);
    _bullet_list.push_back(bullet);
}

void PlayerBulletManager::collision_against_enemies() {
    auto all_enemies = this->_game_scene->get_all_enemies_iterator();
    for (auto& enemy : all_enemies) {
        Vec2 enemy_pos = enemy->get_pos();
        for (auto& bullet : this->_bullet_list) {
            Vec2 bullet_pos = bullet->get_pos();
            // �������Ă����
            if (utils::sphere_collision(enemy_pos, bullet_pos, 25.0, 10.0)) {
                _game_scene->modify_score(10);
                enemy->modify_hp(-bullet->get_power());
                bullet->set_collide_flag();
            }
        }
    }
}
void PlayerBulletManager::collision_against_boss() {
    if (!_game_scene->boss_exist()) return;
    auto all_boss = this->_game_scene->get_all_boss_iterator();
    for (auto& boss : all_boss) {
        if (boss->get_attack_pattern_id() == -1) {
            // �U���p�^�[����-1�Ȃ��C���Ȃ̂œ����蔻����s��Ȃ�
            continue;
        }
        Vec2 boss_pos = boss->get_pos();
        for (auto& bullet : this->_bullet_list) {
            Vec2 bullet_pos = bullet->get_pos();
            // �������Ă����
            if (utils::sphere_collision(boss_pos, bullet_pos, 60.0, 10.0)) {
                _game_scene->modify_score(10);
                boss->modify_hp(-bullet->get_power());
                bullet->set_collide_flag();
            }
        }
    }
}
