#include <DxLib.h>
#include "boss_manager.hpp"
#include "global_define.hpp"
#include "game_scene.hpp"
#include "boss.hpp"
#include "image_manager.hpp"
#include "macro.hpp"
//#include "destroy_enemy_effect.hpp"

BossManager::BossManager(GameScene* scene, std::shared_ptr<EnemyBulletManager> bullet_manager) {
    _game_scene = scene;
    _enemy_bullet_manager = bullet_manager;
    _hp_bar_handle = ImageManager::get_instance()->get_hp_bar();
    _counter = 0;
}

void BossManager::push_bullet(std::shared_ptr<EnemyBullet> bullet) {
    this->_enemy_bullet_manager->push_bullet(bullet);
}

bool BossManager::update() {
    register_boss();
    for (auto iter = _list.begin(); iter != _list.end();) {
        if ((*iter)->update()) {
            ++iter;
        }
        else {
            iter = _list.erase(iter);
        }
    }
    ++_counter;
    return true;
}

void BossManager::draw() const {

    for (const auto boss : _list) {
        if (boss->get_attack_pattern_id() != -1) {

            // 攻撃中はHPバーを表示. 画像は横1pxなので, 画面幅くらいの大きさに合うようにスケーリングして並べて表示する
            int boss_hp = boss->get_hp();
            int boss_max_hp = boss->get_max_hp();
            int bar_num = GlobalValues::IN_WIDTH * 9 / 10 * boss_hp / boss_max_hp;
            for (int i = 0; i < bar_num; ++i) {
                utils::DrawRotaGraphF_Screen(20 + i, 20, 1.0, 0.0, _hp_bar_handle, 0);
            }
        }

        boss->draw();
    }
}

bool BossManager::boss_exist() const {
    return !_list.size() == 0;
}

Vec2 BossManager::get_player_pos() const {
    return _game_scene->get_player_pos();
}

void BossManager::register_boss() {
    // 敵管理クラスのカウントでボスを登録する
    // 楽だから
    if (_game_scene->get_enemy_manager_counter() == 2000 && !this->boss_exist()) {
        auto attack_queue = std::queue<int>{};
        // 攻撃パターン番号をキューに詰める
        attack_queue.push(4);
        attack_queue.push(3);
        attack_queue.push(2);
        attack_queue.push(1);
        auto boss1 = std::make_shared<Boss>(attack_queue, false, this);
        _list.push_back(boss1);
    }
}

/*
void BossManager::set_destroy_effect(Vec2 pos, int color) {
    // スコア加算
    _game_scene->modify_score(150);
    auto effect = std::make_shared<DestroyEnemyEffect>(pos, color);
    _game_scene->set_effect(effect);
}
void BossManager::spawn_items(std::array<int, 6> items, Vec2 pos) {
    _game_scene->spawn_items(items, pos);
}
*/
