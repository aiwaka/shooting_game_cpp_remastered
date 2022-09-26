#include <DxLib.h>
#include <utility>
#include "global_define.hpp"
#include "boss.hpp"
#include "boss_manager.hpp"
#include "image_manager.hpp"
#include "se_manager.hpp"


Boss::Boss(std::queue<int> attack_patterns, bool is_big_boss, BossManager* manager) :
    _pos(Vec2{}),
    _counter(0),
    //_attack(BossAttack{}),
    _attack_pattern_id(-1),
    _attack_patterns{ attack_patterns },
    _hp(0),
    _max_hp(0),
    _is_big_boss(is_big_boss),
    _f_var_slot{ std::array<float, 5>{} },
    _i_var_slot{ std::array<int, 5>{} },
    _move_target(Vec2{}),
    _child_list(std::list<std::shared_ptr<BossChild>>(0)),
    _bullet_list(std::list<std::shared_ptr<EnemyBullet>>(0))
{
    _manager = manager;
    // 最初の攻撃にhpと時間をセットする
    auto hp_and_time = _attack.get_hp_and_time(_attack_patterns.front());
    _max_hp = _hp = hp_and_time[0];
    _time_limit = hp_and_time[1];
}

bool Boss::update() {
    // 敵弾の管理をする. 消えているものを取り除く
    for (auto iter = _bullet_list.begin(); iter != _bullet_list.end();) {
        if (!(*iter)->get_delete_flag()) {
            ++iter;
        }
        else {
            // イテレータを用いてループして, updateがfalseになったものが取り除かれるように
            iter = _bullet_list.erase(iter);
        }
    }
    // 攻撃中にhpが0以下になった場合
    if (_hp <= 0 && _attack_pattern_id != -1) {
        // 子機と敵弾をすべて消す
        _child_list.clear();
        for (auto& bullet : _bullet_list) {
            bullet->set_delete_flag();
        }
        _attack_pattern_id = -1;
        if (_attack_patterns.size() == 0) {
            // もう攻撃が残っていなければ演出等してから終了
            // 背景を戻してスコアを加算して効果音を鳴らす
            if (_is_big_boss) _manager->set_normal_bg();
            _manager->modify_score(50000);
            SoundEffectManager::get_instance()->set_se(4);
            return false;
        }
        _counter = 0;
        SoundEffectManager::get_instance()->set_se(6);
        //_manager->set_destroy_effect(this->_pos, 0);
        // TODO: ここでアイテム出現処理等
        //_manager->spawn_items(this->_item_slot, this->_pos);
        //return false;
    }
    move();
    // 子機の更新
    for (auto iter = _child_list.begin(); iter != _child_list.end();) {
        if ((*iter)->update()) {
            ++iter;
        }
        else {
            iter = _child_list.erase(iter);
        }
    }
    // 攻撃状態によって分岐
    if (_attack_pattern_id == -1) {
        if (_counter == 0) {
            if (_is_big_boss) _manager->set_big_boss_bg();
        }
        // 待機状態
        // 画面中央に戻す
        set_move(Vec2{ static_cast<float>(GlobalValues::CENTER_X),  80.0f });
        // 2秒経過したら次の攻撃へ
        if (_counter > 120) {
            _attack_pattern_id = _attack_patterns.front();
            _attack_patterns.pop();
            auto hp_and_time = _attack.get_hp_and_time(_attack_pattern_id);
            _max_hp = _hp = hp_and_time[0];
            _time_limit = hp_and_time[1];
            // このループの最後で1増えるので0から始めるために-1にする
            _counter = -1;
        }
    }
    else {
        _attack.attack(this);
    }
    ++_counter;
    return true;
}
void Boss::draw() const {
    for (const auto enemy : _child_list) {
        enemy->draw();
    }
    auto handle = ImageManager::get_instance()->get_boss();
    utils::DrawRotaGraphF_Screen(_pos.x, _pos.y, 1.0, 0.0, handle, 1);
}

void Boss::set_move(Vec2 target) {
    _move_target = target;
}

void Boss::move() {
    Vec2 diff_to_target = _move_target - _pos;
    float length = diff_to_target.length();
    // ターゲット位置に近づいたら動かさない
    if (length < 0.1f) return;
    // TODO: ease-out的な移動処理
    Vec2 move_vec = Vec2{};
    if (length > 30.0) {
        move_vec = 3.0 * diff_to_target.normalized();
    }
    else {
        move_vec = diff_to_target * 0.1;
    }
    _pos += move_vec;
}
Vec2 Boss::get_player_pos() const { return _manager->get_player_pos(); }
float  Boss::get_angle_to_player() const {
    Vec2 diff_vec = this->get_player_pos() - this->get_pos();
    float angle = GlobalValues::PI / 2.0;
    if (!diff_vec.is_zero()) {
        angle = diff_vec.angle();
    }
    return angle;
}

void Boss::set_f_slot(size_t idx, float val) {
    this->_f_var_slot[idx] = val;
}
void Boss::set_i_slot(size_t idx, int val) {
    this->_i_var_slot[idx] = val;
}
float Boss::get_f_slot(size_t idx) const {
    return this->_f_var_slot[idx];
}
int Boss::get_i_slot(size_t idx) const {
    return this->_i_var_slot[idx];
}
void Boss::push_bullet(EnemyBulletInfo& info) {
    auto bullet = std::make_shared<EnemyBullet>(info);
    _manager->push_bullet(bullet);
    _bullet_list.push_back(bullet);
}

void Boss::push_child(EnemyBulletInfo& info) {
    auto child = std::make_shared<BossChild>(info);
    _child_list.push_back(child);
}
std::list<std::shared_ptr<EnemyBullet>> Boss::get_bullet_iterator() const {
    return this->_bullet_list;
}
std::list<std::shared_ptr<BossChild>> Boss::get_child_iterator() const {
    return this->_child_list;
}
