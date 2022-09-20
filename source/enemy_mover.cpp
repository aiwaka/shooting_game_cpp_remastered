#include "enemy_mover.hpp"
#include "macro.hpp"
#include "global_define.hpp"
#include "abstract_enemy.hpp"

EnemyMover::EnemyMover() {
    _move_pattern.push_back(&EnemyMover::move_pattern_00);
    _move_pattern.push_back(&EnemyMover::move_pattern_01);
    _move_pattern.push_back(&EnemyMover::move_pattern_02);
}

void EnemyMover::move(AbstractEnemy* enemy)
{
    const unsigned int pattern_id = enemy->get_move_pattern();
    if (pattern_id >= _move_pattern.size()) {
        APP_SYSTEM_ERROR("move_pattern_id‚ª•s³‚Å‚·");
    }
    (this->*_move_pattern[pattern_id])(enemy);
    enemy->set_pos(enemy->get_pos() + enemy->get_speed());
}


void EnemyMover::move_pattern_00(AbstractEnemy* enemy) {
    const int count = enemy->get_counter();
    const int wait = 180;
    if (count == 0) {
        enemy->set_speed(Vec2{ 0.0f, 3.0f });
    }
    if (60 < count && count <= 90) {
        enemy->set_speed(enemy->get_speed() - Vec2{ 0.0f, 0.1f });
    }
    if (90 + wait < count && count <= 90 + wait + 30) {
        enemy->set_speed(enemy->get_speed() + Vec2{ 0.0f, 0.1f });
    }
}

void EnemyMover::move_pattern_01(AbstractEnemy* enemy) {
    int count = enemy->get_counter();
    if (count == 0) {
        enemy->set_speed(Vec2{ -4.0f, 4.0f });
    }
}
void EnemyMover::move_pattern_02(AbstractEnemy* enemy) {
    int count = enemy->get_counter();
    if (count == 0) {
        enemy->set_speed(Vec2{ 4.0f, 4.0f });
    }
}