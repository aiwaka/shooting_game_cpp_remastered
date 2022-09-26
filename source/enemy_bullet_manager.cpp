#include "enemy_bullet_manager.hpp"
#include "game_scene.hpp"
#include "abstract_enemy.hpp"
#include "global_define.hpp"

EnemyBulletManager::EnemyBulletManager(GameScene* scene) {
    _game_scene = scene;
    _counter = 0;
    _bullet_list = std::list<std::shared_ptr<EnemyBullet>>(0);
}

bool EnemyBulletManager::update() {
    for (auto iter = _bullet_list.begin(); iter != _bullet_list.end();) {
        if ((*iter)->update()) {
            ++iter;
        }
        else {
            // �C�e���[�^��p���ă��[�v����, update��false�ɂȂ������̂���菜�����悤��
            // �G�e�ւ̃|�C���^�͓G��{�X�������Ă���̂�, ������ł���菜����悤�Ƀt���O�𗧂ĂĂ����K�v����
            (*iter)->set_delete_flag();
            iter = _bullet_list.erase(iter);
        }
    }
    // ���@�Ƃ̓����蔻��
    this->collision_against_player();
    ++_counter;
    return true;
}

void EnemyBulletManager::draw() const {
    //DrawFormatString(0, 60, GetColor(255, 255, 255), "    �G�e�̐� : %u", _bullet_list.size());
    for (const auto bullet : _bullet_list) {
        bullet->draw();
    }
}

Vec2 EnemyBulletManager::get_player_pos() const {
    return _game_scene->get_player_pos();
}
void EnemyBulletManager::push_bullet(std::shared_ptr<EnemyBullet> bullet) {
    _bullet_list.push_back(bullet);
}


void EnemyBulletManager::collision_against_player() {
    Vec2 player_pos = _game_scene->get_player_pos();
    for (auto& bullet : this->_bullet_list) {
        Vec2 bullet_pos = bullet->get_pos();
        // �������Ă����
        if (utils::sphere_collision(player_pos, bullet_pos, 2.0, 5.0)) {
            _game_scene->modify_player_hp(-bullet->get_damage());
            bullet->set_delete_flag();
        }
    }
}
