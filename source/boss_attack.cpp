#include "boss_attack.hpp"
#include "boss.hpp"
#include "macro.hpp"
#include "global_define.hpp"
#include "enemy_bullet_manager.hpp"

BossAttack::BossAttack() {
    using AttackPattern = BossAttack::AttackPattern;
    // 体力・制限時間・関数へのポインタをあわせてセットする
    _attack_pattern_list.push_back(AttackPattern{ 1000, 3600, &BossAttack::attack_pattern_dummy });
    //_attack_pattern.push_back(&BossAttack::attack_pattern_00);
    //_attack_pattern.push_back(&BossAttack::attack_pattern_01);
    //_attack_pattern.push_back(&BossAttack::attack_pattern_02);
    //_attack_pattern.push_back(&BossAttack::attack_pattern_dummy);
    //_attack_pattern.push_back(&BossAttack::attack_pattern_04);
    //_attack_pattern.push_back(&BossAttack::attack_pattern_05);
    //_attack_pattern.push_back(&BossAttack::attack_pattern_dummy);
    //_attack_pattern.push_back(&BossAttack::attack_pattern_07);
    //_attack_pattern.push_back(&BossAttack::attack_pattern_08);
    //_attack_pattern.push_back(&BossAttack::attack_pattern_09);
    //_attack_pattern.push_back(&BossAttack::attack_pattern_10);
    //_attack_pattern.push_back(&BossAttack::attack_pattern_11);
}

void BossAttack::attack(Boss* boss)
{
    const unsigned int pattern_id = boss->get_attack_pattern_id();
    if (pattern_id >= _attack_pattern_list.size()) {
        APP_SYSTEM_ERROR("ボス敵のattack_pattern_idが不正です");
    }
    // ここでカウント等を参照しながら弾を登録できる.
    (this->*_attack_pattern_list[pattern_id]._pattern)(boss);
}


void BossAttack::attack_pattern_dummy(Boss* boss) {}

/*
void BossAttack::attack_pattern_00(AbstractEnemy* enemy) {
    if (enemy->get_counter() == enemy->get_start_attack_count()) {
        EnemyBulletInfo info;
        info.bullet_type = 0;
        info.color = 0;
        info.endure_count = 0;
        info.damage = 4;
        info.rotating = 0;
        info.fx_detail = 0;
        Vec2 pos = enemy->get_pos();
        info.x = pos.x;
        info.y = pos.y;
        info.angle = GlobalValues::PI / 2.0;
        info.speed = 5.0;
        info.omega = 0.0;
        info.acceleration = 0.0;
        info.temp_speed = 5.0;
        info.bomb_regist = false;
        enemy->push_bullet(info);
    }
}

void BossAttack::attack_pattern_01(AbstractEnemy* enemy) {
    const int local_count = enemy->get_counter() - enemy->get_start_attack_count();
    if (0 <= local_count && local_count < 100 && local_count % 10 == 0) {
        float angle = enemy->get_angle_to_player();

        EnemyBulletInfo info;
        info.bullet_type = 1;
        info.color = 2;
        info.endure_count = 0;
        info.damage = 4;
        info.rotating = 0;
        info.fx_detail = 0;
        Vec2 pos = enemy->get_pos();
        info.x = pos.x;
        info.y = pos.y;
        info.angle = angle;
        info.speed = 4.0;
        info.omega = 0.0;
        info.acceleration = 0.0;
        info.temp_speed = 4.0;
        info.bomb_regist = false;
        enemy->push_bullet(info);
    }
}
void BossAttack::attack_pattern_02(AbstractEnemy* enemy) {
    const int local_count = enemy->get_counter() - enemy->get_start_attack_count();
    if (local_count == 0) {
        float angle = enemy->get_angle_to_player();
        enemy->set_f_slot(0, angle);
    }
    if (0 <= local_count && local_count < 100 && local_count % 10 == 0) {
        EnemyBulletInfo info;
        info.bullet_type = 1;
        info.color = 2;
        info.endure_count = 0;
        info.damage = 4;
        info.rotating = 0;
        info.fx_detail = 0;
        Vec2 pos = enemy->get_pos();
        info.x = pos.x;
        info.y = pos.y;
        info.angle = enemy->get_f_slot(0);
        info.speed = 4.0;
        info.omega = 0.0;
        info.acceleration = 0.0;
        info.temp_speed = 4.0;
        info.bomb_regist = false;
        enemy->push_bullet(info);
    }
}
void BossAttack::attack_pattern_04(AbstractEnemy* enemy) {
    const int local_count = enemy->get_counter() - enemy->get_start_attack_count();
    if (0 <= local_count && local_count < 120 && local_count % 25 == 0) {
        float angle = enemy->get_angle_to_player();
        for (int i = 0; i < 20; ++i) {
            EnemyBulletInfo info;
            info.bullet_type = 5;
            info.color = 3;
            info.endure_count = 0;
            info.damage = 4;
            info.rotating = 0;
            info.fx_detail = 0;
            Vec2 pos = enemy->get_pos();
            info.x = pos.x;
            info.y = pos.y;
            info.angle = angle + GlobalValues::PI * static_cast<float>(i) / 10.0;
            info.speed = 4.0;
            info.omega = 0.0;
            info.acceleration = 0.0;
            info.temp_speed = 4.0;
            info.bomb_regist = false;
            enemy->push_bullet(info);
        }
    }
}
void BossAttack::attack_pattern_05(AbstractEnemy* enemy) {
    const int local_count = enemy->get_counter() - enemy->get_start_attack_count();
    if (0 <= local_count && local_count < 120 && local_count % 3 == 0) {
        float angle = enemy->get_angle_to_player();
        EnemyBulletInfo info;
        info.bullet_type = 4;
        info.color = 1;
        info.endure_count = 0;
        info.damage = 3;
        info.rotating = 0;
        info.fx_detail = 0;
        Vec2 pos = enemy->get_pos();
        info.x = pos.x;
        info.y = pos.y;
        info.angle = angle + utils::rand_in_range(GlobalValues::PI / 4.0);
        info.speed = 4.0 + utils::rand_in_range(1.5);
        info.omega = 0.0;
        info.acceleration = 0.0;
        info.temp_speed = 4.0;
        info.bomb_regist = false;
        enemy->push_bullet(info);
    }
}
void BossAttack::attack_pattern_07(AbstractEnemy* enemy) {
    const int local_count = enemy->get_counter() - enemy->get_start_attack_count();
    if (0 <= local_count && local_count < 160 && local_count % 20 == 0) {
        float angle = enemy->get_angle_to_player();
        for (int i = 0; i < 4; ++i) {
            EnemyBulletInfo info;
            info.bullet_type = 1;
            info.color = 3;
            info.endure_count = 0;
            info.damage = 3;
            info.rotating = 0;
            info.fx_detail = 0;
            Vec2 pos = enemy->get_pos();
            info.x = pos.x;
            info.y = pos.y;
            info.angle = angle + GlobalValues::PI * (static_cast<float>(i) / 18.0 - 1.0 / 12.0);
            info.speed = 4.0;
            info.omega = 0.0;
            info.acceleration = 0.0;
            info.temp_speed = 4.0;
            info.bomb_regist = false;
            enemy->push_bullet(info);
        }
    }
}
void BossAttack::attack_pattern_08(AbstractEnemy* enemy) {
    const int local_count = enemy->get_counter() - enemy->get_start_attack_count();
    if (0 <= local_count && local_count < 160 && local_count % 20 == 0) {
        float angle = enemy->get_angle_to_player();
        for (int i = 0; i < 5; ++i) {
            EnemyBulletInfo info;
            info.bullet_type = 1;
            info.color = 0;
            info.endure_count = 0;
            info.damage = 3;
            info.rotating = 0;
            info.fx_detail = 0;
            Vec2 pos = enemy->get_pos();
            info.x = pos.x;
            info.y = pos.y;
            info.angle = angle + GlobalValues::PI * (static_cast<float>(i) / 24.0 - 1.0 / 12.0);
            info.speed = 4.0;
            info.omega = 0.0;
            info.acceleration = 0.0;
            info.temp_speed = 4.0;
            info.bomb_regist = false;
            enemy->push_bullet(info);
        }
    }
}

void BossAttack::attack_pattern_09(AbstractEnemy* enemy) {
    const int local_count = enemy->get_counter() - enemy->get_start_attack_count();
    if (0 <= local_count && local_count <= 240 && local_count % 80 == 0) {
        float angle = enemy->get_angle_to_player();
        EnemyBulletInfo info;
        info.bullet_type = 4;
        info.color = 3;
        info.endure_count = 0;
        info.damage = 8;
        info.rotating = 0;
        info.fx_detail = 0;
        Vec2 pos = enemy->get_pos();
        info.x = pos.x;
        info.y = pos.y;
        info.angle = angle;
        info.speed = 5.5;
        info.omega = 0.0;
        info.acceleration = 0.0;
        info.temp_speed = 5.5;
        info.bomb_regist = false;
        enemy->push_bullet(info);
    }
    auto bullet_list = enemy->get_bullet_iterator();
    for (auto& bullet : bullet_list) {
        // 弾で特定の種類のものが特定のカウント周期のとき
        if (bullet->get_counter() % 12 == 0 && bullet->get_type() == 4) {
            float angle = utils::rand_in_range(GlobalValues::PI);
            for (int i = 0; i < 4; ++i) {
                EnemyBulletInfo info;
                info.bullet_type = 1;
                info.color = 3;
                info.endure_count = 0;
                info.damage = 3;
                info.rotating = 0;
                info.fx_detail = 0;
                Vec2 pos = bullet->get_pos();
                info.x = pos.x;
                info.y = pos.y;
                info.angle = angle + GlobalValues::PI * static_cast<float>(i) / 2.0;
                info.speed = 4.0;
                info.omega = 0.0;
                info.acceleration = 0.0;
                info.temp_speed = 4.0;
                info.bomb_regist = false;
                enemy->push_bullet(info);
            }
        }
    }
}
void BossAttack::attack_pattern_10(AbstractEnemy* enemy) {
    const int local_count = enemy->get_counter() - enemy->get_start_attack_count();
    if (0 <= local_count && local_count < 240 && local_count % 80 == 0) {
        float angle = utils::rand_in_range(GlobalValues::PI);
        for (int i = 0; i < 12; ++i) {
            for (int j = 0; j < 2; ++j) {
                EnemyBulletInfo info;
                info.bullet_type = 5;
                info.color = 2;
                info.endure_count = 50;
                info.damage = 4;
                info.rotating = 0;
                info.fx_detail = 0;
                Vec2 pos = enemy->get_pos();
                info.x = pos.x;
                info.y = pos.y;
                info.angle = angle + GlobalValues::PI * static_cast<float>(i) / 6.0;
                info.speed = j == 0 ? 3.0 : 5.0;
                info.omega = j == 0 ? 0.0 : GlobalValues::PI / 240.0;
                info.acceleration = 0.0;
                info.temp_speed = 4.0;
                info.bomb_regist = false;
                enemy->push_bullet(info);
            }
        }
    }
}
void BossAttack::attack_pattern_11(AbstractEnemy* enemy) {
    const int local_count = enemy->get_counter() - enemy->get_start_attack_count();
    if (0 <= local_count && local_count < 60 && local_count % 4 == 0) {
        float angle = enemy->get_angle_to_player();
        for (int i = 0; i < 5; ++i) {
            EnemyBulletInfo info;
            info.bullet_type = 1;
            info.color = 3;
            info.endure_count = 0;
            info.damage = 4;
            info.rotating = 0;
            info.fx_detail = 0;
            Vec2 pos = enemy->get_pos();
            info.x = pos.x;
            info.y = pos.y;
            info.angle = angle + GlobalValues::PI * (static_cast<float>(i) / 32.0 - 1.0 / 16.0);
            info.speed = static_cast<float>(local_count + 30) * 0.09;
            info.omega = 0.0;
            info.acceleration = 0.0;
            info.temp_speed = 4.0;
            info.bomb_regist = false;
            enemy->push_bullet(info);
        }
    }
}
*/
