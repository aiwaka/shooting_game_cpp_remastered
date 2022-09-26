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
    // �ŏ��̍U����hp�Ǝ��Ԃ��Z�b�g����
    auto hp_and_time = _attack.get_hp_and_time(_attack_patterns.front());
    _max_hp = _hp = hp_and_time[0];
    _time_limit = hp_and_time[1];
}

bool Boss::update() {
    // �G�e�̊Ǘ�������. �����Ă�����̂���菜��
    for (auto iter = _bullet_list.begin(); iter != _bullet_list.end();) {
        if (!(*iter)->get_delete_flag()) {
            ++iter;
        }
        else {
            // �C�e���[�^��p���ă��[�v����, update��false�ɂȂ������̂���菜�����悤��
            iter = _bullet_list.erase(iter);
        }
    }
    // �U������hp��0�ȉ��ɂȂ����ꍇ
    if (_hp <= 0 && _attack_pattern_id != -1) {
        // �q�@�ƓG�e�����ׂď���
        _child_list.clear();
        for (auto& bullet : _bullet_list) {
            bullet->set_delete_flag();
        }
        _attack_pattern_id = -1;
        if (_attack_patterns.size() == 0) {
            // �����U�����c���Ă��Ȃ���Ή��o�����Ă���I��
            // �w�i��߂��ăX�R�A�����Z���Č��ʉ���炷
            if (_is_big_boss) _manager->set_normal_bg();
            _manager->modify_score(50000);
            SoundEffectManager::get_instance()->set_se(4);
            return false;
        }
        _counter = 0;
        SoundEffectManager::get_instance()->set_se(6);
        //_manager->set_destroy_effect(this->_pos, 0);
        // TODO: �����ŃA�C�e���o��������
        //_manager->spawn_items(this->_item_slot, this->_pos);
        //return false;
    }
    move();
    // �q�@�̍X�V
    for (auto iter = _child_list.begin(); iter != _child_list.end();) {
        if ((*iter)->update()) {
            ++iter;
        }
        else {
            iter = _child_list.erase(iter);
        }
    }
    // �U����Ԃɂ���ĕ���
    if (_attack_pattern_id == -1) {
        if (_counter == 0) {
            if (_is_big_boss) _manager->set_big_boss_bg();
        }
        // �ҋ@���
        // ��ʒ����ɖ߂�
        set_move(Vec2{ static_cast<float>(GlobalValues::CENTER_X),  80.0f });
        // 2�b�o�߂����玟�̍U����
        if (_counter > 120) {
            _attack_pattern_id = _attack_patterns.front();
            _attack_patterns.pop();
            auto hp_and_time = _attack.get_hp_and_time(_attack_pattern_id);
            _max_hp = _hp = hp_and_time[0];
            _time_limit = hp_and_time[1];
            // ���̃��[�v�̍Ō��1������̂�0����n�߂邽�߂�-1�ɂ���
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
    // �^�[�Q�b�g�ʒu�ɋ߂Â����瓮�����Ȃ�
    if (length < 0.1f) return;
    // TODO: ease-out�I�Ȉړ�����
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
