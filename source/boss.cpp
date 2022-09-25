#include <DxLib.h>
#include <utility>
#include "global_define.hpp"
#include "boss.hpp"
#include "boss_manager.hpp"
#include "image_manager.hpp"


Boss::Boss(std::queue<int> attack_patterns, bool is_big_boss, BossManager* manager) :
    _pos(Vec2{}),
    _counter(0),
    _attack_pattern_id(-1),
    _attack_patterns{ attack_patterns },
    _hp(0),
    _is_big_boss(is_big_boss),
    _f_var_slot{ std::array<float, 5>{} },
    _i_var_slot{ std::array<int, 5>{} },
    _move_target(Vec2{})
{
    _manager = manager;
    _bullet_list = std::list<std::shared_ptr<EnemyBullet>>(0);

}

bool Boss::update() {
    if (_hp <= 0) {
        //_manager->set_destroy_effect(this->_pos, 0);
        // TODO: ここでアイテム出現処理等
        //_manager->spawn_items(this->_item_slot, this->_pos);
        //return false;
    }
    move();
    if (_attack_pattern_id == -1) {
        // 待機状態
        // 画面中央に戻す
        set_move(Vec2{ static_cast<float>(GlobalValues::CENTER_X), static_cast<float>(GlobalValues::CENTER_Y) - 70.0f });
        if (_counter > 120) {
            _attack_pattern_id = _attack_patterns.front();
            _attack_patterns.pop();
        }
    }
    else {
        _attack.attack(this);
    }
    ++_counter;
    return true;
}
void Boss::draw() const {
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
std::list<std::shared_ptr<EnemyBullet>> Boss::get_bullet_iterator() const {
    return this->_bullet_list;
}
