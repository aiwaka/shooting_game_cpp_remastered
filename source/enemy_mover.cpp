#include "enemy_mover.hpp"
#include "macro.hpp"
#include "global_define.hpp"
#include "abstract_enemy.hpp"

EnemyMover::EnemyMover() {
    _move_pattern.push_back(&EnemyMover::move_pattern_00);
    _move_pattern.push_back(&EnemyMover::move_pattern_dummy);
    _move_pattern.push_back(&EnemyMover::move_pattern_dummy);
    _move_pattern.push_back(&EnemyMover::move_pattern_dummy);
    _move_pattern.push_back(&EnemyMover::move_pattern_dummy);
    _move_pattern.push_back(&EnemyMover::move_pattern_05);
    _move_pattern.push_back(&EnemyMover::move_pattern_06);
    _move_pattern.push_back(&EnemyMover::move_pattern_dummy);
    _move_pattern.push_back(&EnemyMover::move_pattern_dummy);
    _move_pattern.push_back(&EnemyMover::move_pattern_09);
    _move_pattern.push_back(&EnemyMover::move_pattern_dummy);
    _move_pattern.push_back(&EnemyMover::move_pattern_11);
    _move_pattern.push_back(&EnemyMover::move_pattern_12);
    _move_pattern.push_back(&EnemyMover::move_pattern_13);
}

void EnemyMover::move(AbstractEnemy* enemy)
{
    const unsigned int pattern_id = enemy->get_move_pattern();
    if (pattern_id >= _move_pattern.size()) {
        APP_SYSTEM_ERROR("move_pattern_idが不正です");
    }
    // ここで位置や速度を書き換える. enemyのポインタ渡しによってAbstractEnemyのpublicメソッドを自由に使える.
    (this->*_move_pattern[pattern_id])(enemy);
    // 変更された速度による位置変化を反映する.
    enemy->set_pos(enemy->get_pos() + enemy->get_speed());
}


void EnemyMover::move_pattern_dummy(AbstractEnemy* enemy) {}

void EnemyMover::move_pattern_00(AbstractEnemy* enemy) {
    const int count = enemy->get_counter();
    const int wait = 180;
    if (count == 0) {
        enemy->set_speed(Vec2{ 0.0f, 3.0f });
    }
    // 40カウントまでに停止
    if (30 < count && count <= 40) {
        enemy->set_speed(enemy->get_speed() - Vec2{ 0.0f, 0.3f });
    }
    // 180カウント待機してから20カウントかけて加速して上昇
    if (40 + wait < count && count <= 40 + wait + 20) {
        enemy->set_speed(enemy->get_speed() - Vec2{ 0.0f, 0.15f });
    }
}

void EnemyMover::move_pattern_05(AbstractEnemy* enemy) {
    int count = enemy->get_counter();
    if (count == 0) {
        enemy->set_speed(Vec2{ -1.0f, 2.0f });
    }
}
void EnemyMover::move_pattern_06(AbstractEnemy* enemy) {
    int count = enemy->get_counter();
    if (count == 0) {
        enemy->set_speed(Vec2{ 1.0f, 2.0f });
    }
}
void EnemyMover::move_pattern_09(AbstractEnemy* enemy) {
    int count = enemy->get_counter();
    if (count == 360) {
        enemy->set_speed(Vec2{ 0.0f, -3.0f });
    }
}
// 自機の位置を取得できるようにしたときに実装
void EnemyMover::move_pattern_11(AbstractEnemy* enemy) {
    int count = enemy->get_counter();
    if (count < 60) {
        // 敵から自機へのベクトル
        Vec2 diff_vec = enemy->get_player_pos() - enemy->get_pos();
        Vec2 next_speed = Vec2{ 0.0, 2.0f };
        if (diff_vec.length_square() > 0.0001f) {
            next_speed = 2.0f * diff_vec.normalized();
        }
        enemy->set_speed(next_speed);
    }
}
void EnemyMover::move_pattern_12(AbstractEnemy* enemy) {
    const int count = enemy->get_counter();
    const int wait = 20;
    if (count == 0) {
        enemy->set_speed(Vec2{ 3.0f, 0.0f });
    }
    // 50カウントで停止
    if (count == 50) {
        enemy->set_speed(Vec2{});
    }
    // 70カウントで再び移動開始
    if (count == 50 + wait) {
        enemy->set_speed(Vec2{ 3.0f, 0.0f });
    }
}
void EnemyMover::move_pattern_13(AbstractEnemy* enemy) {
    const int count = enemy->get_counter();
    const int wait = 20;
    if (count == 0) {
        enemy->set_speed(Vec2{ -3.0f, 0.0f });
    }
    // 50カウントで停止
    if (count == 50) {
        enemy->set_speed(Vec2{});
    }
    // 70カウントで再び移動開始
    if (count == 50 + wait) {
        enemy->set_speed(Vec2{ -3.0f, 0.0f });
    }
}
