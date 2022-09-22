#include "player_bullet_manager.hpp"
#include "player.hpp"
#include "player_bullet.hpp"
#include "game_scene.hpp"

PlayerBulletManager::PlayerBulletManager(GameScene* scene) : _counter(0) {
    _game_scene = scene;
    _bullet_list = std::list<std::shared_ptr<PlayerBullet>>(0);
}

bool PlayerBulletManager::update() {
    for (auto iter = _bullet_list.begin(); iter != _bullet_list.end();) {
        if (!((*iter)->update())) {
            iter = _bullet_list.erase(iter);
        }
        else {
            ++iter;
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

std::list<std::shared_ptr<PlayerBullet>> PlayerBulletManager::get_all_player_bullet() const {
    return this->_bullet_list;
}
void PlayerBulletManager::push_bullet(int power, Vec2 pos) {
    auto bullet = std::make_shared<PlayerBullet>(power, pos);
    _bullet_list.push_back(bullet);
}