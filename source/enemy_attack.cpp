#include "enemy_attack.hpp"
#include "macro.hpp"
#include "global_define.hpp"
#include "abstract_enemy.hpp"
#include "enemy_bullet_manager.hpp"

EnemyAttack::EnemyAttack() {
    _attack_pattern.push_back(&EnemyAttack::attack_pattern_00);
    _attack_pattern.push_back(&EnemyAttack::attack_pattern_00);
    _attack_pattern.push_back(&EnemyAttack::attack_pattern_00);
    _attack_pattern.push_back(&EnemyAttack::attack_pattern_00);
    _attack_pattern.push_back(&EnemyAttack::attack_pattern_00);
    _attack_pattern.push_back(&EnemyAttack::attack_pattern_00);
    _attack_pattern.push_back(&EnemyAttack::attack_pattern_00);
    _attack_pattern.push_back(&EnemyAttack::attack_pattern_00);
    _attack_pattern.push_back(&EnemyAttack::attack_pattern_00);
    _attack_pattern.push_back(&EnemyAttack::attack_pattern_00);
    _attack_pattern.push_back(&EnemyAttack::attack_pattern_00);
    _attack_pattern.push_back(&EnemyAttack::attack_pattern_00);
    _attack_pattern.push_back(&EnemyAttack::attack_pattern_00);
    _attack_pattern.push_back(&EnemyAttack::attack_pattern_00);
    _attack_pattern.push_back(&EnemyAttack::attack_pattern_00);
    _attack_pattern.push_back(&EnemyAttack::attack_pattern_00);
}

void EnemyAttack::attack(AbstractEnemy* enemy)
{
    const int start_count = enemy->get_start_attack_count();
    // カウントが攻撃開始に達していなければ終了
    if (enemy->get_counter() < start_count) return;

    const unsigned int pattern_id = enemy->get_attack_pattern_id();
    if (pattern_id >= _attack_pattern.size()) {
        APP_SYSTEM_ERROR("attack_pattern_idが不正です");
    }
    // ここでカウント等を参照しながら弾を登録できる.
    (this->*_attack_pattern[pattern_id])(enemy);
}


void EnemyAttack::attack_pattern_dummy(AbstractEnemy* enemy) {}

void EnemyAttack::attack_pattern_00(AbstractEnemy* enemy) {
    if (enemy->get_counter() == enemy->get_start_attack_count()) {
        EnemyBulletInfo info;
        info.bullet_type = 0;
        info.color = 0;
        info.endure_count = 0;
        info.damage = 1;
        info.rotating = 0;
        info.fx_detail = 0;
        Vec2 pos = enemy->get_pos();
        info.x = pos.x;
        info.y = pos.y;
        info.angle = GlobalValues::PI / 2.0;
        info.speed = 5.0;
        info.omega = 0.0;
        info.acceleration = 0.0;
        info.base_angle = 0.0;
        info.temp_speed = 5.0;
        info.bomb_regist = false;
        enemy->push_bullet(std::make_shared<EnemyBullet>(info, enemy));
    }
}
