#include "enemy_bullet_manager.hpp"
#include "game_scene.hpp"
#include "abstract_enemy.hpp"
#include "global_define.hpp"

//EnemyBulletManager::EnemyBulletManager(GameScene* scene) {
//    _game_scene = scene;
//    _counter = 0;
//    _bullet_list = std::list<std::shared_ptr<EnemyBullet>>(0);
//}
//
//bool EnemyBulletManager::update() {
//    ++_counter;
//    for (auto iter = _bullet_list.begin(); iter != _bullet_list.end();) {
//        if (!((*iter)->update())) {
//            // イテレータを用いてループして, updateがfalseになったものが取り除かれるように
//            //iter = _list.erase(iter);
//        }
//        else {
//            ++iter;
//        }
//    }
//    return true;
//}
//
//void EnemyBulletManager::draw() const {
//    DrawFormatString(0, 60, GetColor(255, 255, 255), "敵弾の数 : %d", _bullet_list.size());
//    for (const auto bullet : _bullet_list) {
//        bullet->draw();
//    }
//}
//
//Vec2 EnemyBulletManager::get_player_pos() const {
//    return _game_scene->get_player_pos();
//}
//void EnemyBulletManager::push_bullet(std::shared_ptr<EnemyBullet> bullet) {
//    _bullet_list.push_back(bullet);
//}
