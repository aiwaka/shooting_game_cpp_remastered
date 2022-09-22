#include "player_bullet_manager.hpp"
#include "player.hpp"
#include "player_bullet.hpp"
#include "game_scene.hpp"

PlayerBulletManager::PlayerBulletManager(GameScene* scene) : _counter(0) {
    _game_scene = scene;
    _bullet_list = std::list<std::shared_ptr<PlayerBullet>>(0);
}

bool PlayerBulletManager::update() {
    // ‚±‚±‚Å“–‚½‚è”»’è‚ð‚¨‚±‚È‚¤
    collision_against_enemies();
    // ‘S’e‚ðXV, update‚ªfalse‚Å•Ô‚Á‚Ä‚«‚½‚à‚Ì‚ÍÁ‹Ž‚·‚é
    for (auto iter = _bullet_list.begin(); iter != _bullet_list.end();) {
        if ((*iter)->update()) {
            ++iter;
        }
        else {
            iter = _bullet_list.erase(iter);
        }
    }
    ++_counter;
    return true;
}

void PlayerBulletManager::draw() const {
    //DrawFormatString(0, 90, GetColor(255, 255, 255), "Ž©‹@’e‚Ì” : %d", _bullet_list.size());
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
            // ‚ ‚½‚Á‚Ä‚¢‚ê‚Î
            if (enemy_pos.distance(bullet_pos) < 20.0) {
                enemy->modify_hp(-bullet->get_power());
                bullet->set_collide_flag();
            }
        }
    }
}
