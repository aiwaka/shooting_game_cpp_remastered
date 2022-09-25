#include "boss_attack.hpp"
#include "boss.hpp"
#include "macro.hpp"
#include "global_define.hpp"
#include "enemy_bullet_manager.hpp"

BossAttack::BossAttack() {
    using AttackPattern = BossAttack::AttackPattern;
    // 体力・制限時間・関数へのポインタをあわせてセットする
    _attack_pattern_list.push_back(AttackPattern{ 1000, 3600, &BossAttack::pattern_dummy });
    _attack_pattern_list.push_back(AttackPattern{ 1000, 3600, &BossAttack::pattern_001 });
    _attack_pattern_list.push_back(AttackPattern{ 1000, 3600, &BossAttack::pattern_002 });
    _attack_pattern_list.push_back(AttackPattern{ 1000, 3600, &BossAttack::pattern_003 });
    _attack_pattern_list.push_back(AttackPattern{ 1000, 3600, &BossAttack::pattern_004 });
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


std::array<int, 2> BossAttack::get_hp_and_time(int id) {
    return std::array<int, 2>{_attack_pattern_list[id]._hp, _attack_pattern_list[id]._time_limit};
}

void BossAttack::pattern_dummy(Boss* boss) {
    printf("dummy attack pattern called\n");
}
// 子機を展開してそこから円形発射を延々と行う
/*
void BossAttack::pattern_005(Boss* boss) {
#define TM005 400
#define CHILD_TIME005 240
    int i, j, k, l, t = boss_shot.cnt % TM004, t2 = boss_shot.cnt;
    static double tm;
    double angle;
    if (t == 0) {
        angle = bossatan2();
        for (i = 0; i < 5; i++) {
            if ((k = child_search()) != -1) {
                child[k].flag = 1;
                child[k].cnt = 0;
                child[k].angle = angle + PI2 / 5 * i;
                child[k].spd = 1.8;
                child[k].range = 0.5;
                child[k].x = boss.x;
                child[k].y = boss.y;
            }
        }
    }
    if (t <= 200 && t % 25 == 0) {
        for (i = 0; i < CHILD_MAX; i++) {
            if (child[i].flag == 1) {
                angle = atan2(boss.y - child[i].y, boss.x - child[i].x);
                for (j = 0; j < 8; j++) {
                    if ((l = search_boss_shot()) != -1) {
                        boss_shot.bullet[l].flag = 1;
                        boss_shot.bullet[l].cnt = 0;
                        boss_shot.bullet[l].angle = angle + PI2 / 8 * j;
                        boss_shot.bullet[l].spd = 4;
                        boss_shot.bullet[l].knd = 4;
                        boss_shot.bullet[l].col = 3;
                        boss_shot.bullet[l].eff = 1;
                        boss_shot.bullet[l].x = child[i].x;
                        boss_shot.bullet[l].y = child[i].y;
                        boss_shot.bullet[l].power = 3;
                        boss_shot.bullet[l].till = 200;
                    }
                }
                se.SetSEFlag(10);
            }
        }
    }
    for (i = 0; i < CHILD_MAX; i++) {
        if (child[i].cnt > CHILD_TIME005) {
            child[i].cnt = 0;
            child[i].flag = 0;
        }
    }
}
*/

// でかい2色の円をいっぱい発射
void BossAttack::pattern_001(Boss* boss) {
    int count = boss->get_counter();
    Vec2 boss_pos = boss->get_pos();
    if (count == 0) {
        // 最初に子機を準備
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 8; ++j) {
                EnemyBulletInfo info;
                info.bullet_type = i * 8 + j; // 子機番号として使う
                info.x = boss_pos.x;
                info.y = boss_pos.y;
                info.angle = -GlobalValues::PI / 2.0; // 角度は発射方向として使う
                info.speed = 0.0; // 自動で移動しない
                info.omega = 0.0;
                info.acceleration = 0.0;
                boss->push_child(info);
            }
        }
    }
    auto child_list = boss->get_child_iterator();
    for (auto& child : child_list) {
        // 子機番号を復元
        int i = child->get_state() / 8;
        int j = child->get_state() % 8;
        float angle1 = GlobalValues::PI / 2.0 + GlobalValues::PI / 400.0 * static_cast<float>(count);
        float angle2 = GlobalValues::PI / 2.0 - GlobalValues::PI / 400.0 * static_cast<float>(count);
        Vec2 rel_vec = Vec2::from_angle((i == 0 ? angle1 : angle2) + GlobalValues::PI * static_cast<float>(j) / 4.0) * 90.0;
        Vec2 next_child_pos = boss_pos + rel_vec;
        child->set_pos(next_child_pos);
        child->set_angle(static_cast<float>(count));

        if (count % 9 == 0) {
            for (int k = 0; k < 2; ++k) {
                float bullet_angle = GlobalValues::PI * 2.0 / 3.0 * static_cast<float>(count / 8);
                EnemyBulletInfo info;
                info.bullet_type = 1;
                info.color = k + 1; // 1 or 2
                info.endure_count = 60;
                info.damage = 5;
                info.x = next_child_pos.x;
                info.y = next_child_pos.y;
                info.angle = child->get_angle() + static_cast<float>(k * 2 - 1) * bullet_angle;
                info.speed = 3.0;
                info.omega = 0.0;
                info.acceleration = 0.0;
                boss->push_bullet(info);
            }
        }
    }
}

//一つの子機から2色楔弾
void BossAttack::pattern_002(Boss* boss) {
    int count = boss->get_counter();
    Vec2 boss_pos = boss->get_pos();
    if (count == 0) {
        EnemyBulletInfo info;
        info.angle = utils::rand_in_range(GlobalValues::PI);
        Vec2 rel_pos = Vec2::from_angle(info.angle) * 75.0f;
        info.x = boss_pos.x + rel_pos.x;
        info.y = boss_pos.y + rel_pos.y;
        info.speed = 0.0; // 自動で移動しない
        boss->push_child(info);
    }
    auto child_list = boss->get_child_iterator();
    for (auto& child : child_list) {
        // 子機の位置と角度を更新
        float next_child_angle = child->get_angle() + GlobalValues::PI / 60.0;
        child->set_angle(next_child_angle);
        Vec2 next_child_pos = boss_pos + Vec2::from_angle(next_child_angle) * 75.0f;
        child->set_pos(next_child_pos);

        if (count % 5 == 0) {
            // 子機から2列7wayで発射
            for (int j = 0; j < 2; ++j) {
                for (int i = 0; i < 7; ++i) {
                    EnemyBulletInfo info;
                    info.bullet_type = 5;
                    info.color = 4 * j + 1; // 1 or 5
                    info.endure_count = 30;
                    info.damage = 4;
                    info.x = next_child_pos.x;
                    info.y = next_child_pos.y;
                    info.angle = static_cast<float>(count) * 0.3 + GlobalValues::PI * 2.0 * static_cast<float>(i) / 7.0f;
                    info.speed = j == 0 ? 2.8 : 3.6;
                    boss->push_bullet(info);
                    // se
                }
            }
        }
    }
}

// 曲がる交差弾
void BossAttack::pattern_003(Boss* boss) {
    int count = boss->get_counter();
    int local_count = count % 240; // 3秒周期を持つのでこのカウントを用意する
    Vec2 boss_pos = boss->get_pos();
    static float base_angle;
    if (count == 0) {
        base_angle = utils::rand_in_range(GlobalValues::PI);
    }
    if (local_count % 9 == 0 && local_count < 150) {
        float angle = base_angle + local_count * 0.1;
        for (int j = 0; j < 2; ++j) {
            for (int i = 0; i < 10; ++i) {
                EnemyBulletInfo info;
                info.bullet_type = 0;
                info.color = 4;
                info.endure_count = 50;
                info.damage = 4;
                info.x = boss_pos.x;
                info.y = boss_pos.y;
                info.angle = angle + GlobalValues::PI * static_cast<float>(i) / 5.0;
                info.speed = 4.4;
                info.omega = j == 0 ? GlobalValues::PI / 180.0 : -GlobalValues::PI / 180.0;
                boss->push_bullet(info);
                // se
            }
        }
    }
    auto bullet_list = boss->get_bullet_iterator();
    for (auto& bullet : bullet_list) {
        if (bullet->get_counter() >= 90) {
            bullet->set_omega(0.0);
        }
    }
}

// 子機から出て回転する弾 花っぽい
void BossAttack::pattern_004(Boss* boss) {
    int count = boss->get_counter();
    int local_count = count % 200; // 200フレーム周期
    int period_num = count / 200; // 何週期目？
    Vec2 boss_pos = boss->get_pos();

    if (local_count == 0) {
        float child_base_angle = utils::rand_in_range(GlobalValues::PI); // 前は自機狙いだったがランダムでも大差ないのでは
        //chilang = bossatan2();
        // 各周期の最初に子機を3つ発射
        for (int i = 0; i < 3; ++i) {
            EnemyBulletInfo info;
            info.angle = child_base_angle + GlobalValues::PI * 2.0 * static_cast<float>(i) / 3.0f;
            info.x = boss_pos.x;
            info.y = boss_pos.y;
            info.speed = 3.0;
            info.omega = GlobalValues::PI / 180.0;
            boss->push_child(info);
        }
        if (period_num % 3 == 1) {
            // 3周期に1回移動
            Vec2 target = Vec2::from_angle(utils::rand_in_range(GlobalValues::PI)) * 60.0 + boss_pos;
            // 適当な位置に収める. 敵の位置は左上が基準で描画しているので複雑に考えないでいい
            Vec2 min_vec = Vec2{ 50.0, 40.0 };
            Vec2 max_vec = Vec2{ static_cast<float>(GlobalValues::IN_WIDTH) - 50.0f, 80.0f };
            target = target.clamp(min_vec, max_vec);
            boss->set_move(target);
        }
    }
    auto child_list = boss->get_child_iterator();
    for (auto& child : child_list) {
        if (child->get_counter() > 81) {
            // 81カウントで子機は消滅させる
            child->delete_child();
            continue;
        }
        if (local_count % 5 == 0) {
            float angle = child->get_angle();
            Vec2 child_pos = child->get_pos();
            for (int i = 0; i < 7; i++) {
                EnemyBulletInfo info;
                info.bullet_type = 1;
                info.color = 2;
                info.endure_count = 150;
                info.damage = 5;
                info.x = child_pos.x;
                info.y = child_pos.y;
                info.angle = angle + GlobalValues::PI * 2.0 * static_cast<float>(i) / 7.0;
                info.speed = 3.0;
                info.omega = GlobalValues::PI / 30.0;
                boss->push_bullet(info);
            }
            // se
        }
    }

    auto bullet_list = boss->get_bullet_iterator();
    for (auto& bullet : bullet_list) {
        if (bullet->get_counter() >= 100) {
            bullet->set_omega(0.0);
        }
    }
}
/*
void boss_shot_bullet007() {
#define TM007 300
    int i, j, k, t = boss_shot.cnt % TM007;
    static double angle, aangle, base_angle;
    if (t == 0) {
        angle = rang(PI);
        base_angle = angle;
        aangle = 0;
    }
    if (t % 2 == 0 && t < 240) {
        for (j = 0; j < 2; j++) {
            for (i = 0; i < 4; i++) {
                if ((k = search_boss_shot()) != -1) {
                    boss_shot.bullet[k].flag = 1;
                    boss_shot.bullet[k].cnt = 0;
                    boss_shot.bullet[k].col = 2;
                    boss_shot.bullet[k].knd = 0;
                    boss_shot.bullet[k].x = boss.x;
                    boss_shot.bullet[k].y = boss.y;
                    boss_shot.bullet[k].angle = base_angle + (j ? angle : -angle) + PI2 / 4 * i;
                    boss_shot.bullet[k].spd = 3;
                    boss_shot.bullet[k].power = 3;
                    boss_shot.bullet[k].eff = 1;
                }
            }
        }
        se.SetSEFlag(10);
        aangle += PI2 / 2160;
    }
    angle += aangle;
}

void boss_shot_bullet008() {
    int i, k, t = boss_shot.cnt;
    static double angle, aangle;
    if (t == 0) {
        angle = -PI2;
        aangle = 0;
    }
    if (t % 2 == 0) {
        for (i = 0; i < 5; i++) {
            if ((k = search_boss_shot()) != -1) {
                boss_shot.bullet[k].flag = 1;
                boss_shot.bullet[k].col = 5;
                boss_shot.bullet[k].x = boss.x;
                boss_shot.bullet[k].y = boss.y;
                boss_shot.bullet[k].knd = 1;
                boss_shot.bullet[k].angle = angle + PI2 / 5 * i;
                boss_shot.bullet[k].cnt = 0;
                boss_shot.bullet[k].spd = 4;
            }
        }
        se.SetSEFlag(10);
        aangle += PI2 / 2160;
    }
    angle -= aangle;
    if (angle < -PI2) {
        angle += PI2;
    }
    for (i = 0; i < BOSS_BULLET_MAX; i++) {
        if (boss_shot.bullet[i].flag == 1 && boss_shot.bullet[i].cnt < 120) {
            boss_shot.bullet[i].spd -= 0.07;
        }
        if (boss_shot.bullet[i].flag == 1 && boss_shot.bullet[i].cnt == 120) {
            boss_shot.bullet[i].knd = 2;
            boss_shot.bullet[i].col = 1;
        }
    }
}




//sine wave
void boss_shot_bullet010() {
#define TM010 240
    int i, j, k, t = boss_shot.cnt % TM010, t2 = boss_shot.cnt;
    static double y, angle;
    if (t == 0) {
        y = boss.y;
        angle = rang(PI);
    }
    if (t % 2 == 0 && t < 80) {
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 8; j++) {
                if ((k = search_boss_shot()) != -1) {
                    boss_shot.bullet[k].flag = 1;
                    boss_shot.bullet[k].cnt = 0;
                    boss_shot.bullet[k].knd = 0;
                    boss_shot.bullet[k].col = i == 0 ? 1 : 2;
                    boss_shot.bullet[k].x = FMX / 80.0 * t;
                    boss_shot.bullet[k].y = sin(PI2 / 80 * t) * 80 + y;
                    boss_shot.bullet[k].spd = i == 0 ? 3.4 : 0;
                    boss_shot.bullet[k].angle = angle + PI2 / (80) * t + PI2 / 8 * j + (i == 0 ? 0 : PI2 / 8 / 2);
                    boss_shot.bullet[k].state = i == 0 ? 0 : 1;
                    boss_shot.bullet[k].power = 3;
                    boss_shot.bullet[k].eff = i == 0 ? 0 : 1;
                    se.SetSEFlag(10);
                }
            }
        }
    }
    for (i = 0; i < BOSS_BULLET_MAX; i++) {
        if (boss_shot.bullet[i].flag > 0) {
            if (boss_shot.bullet[i].state == 1 && boss_shot.bullet[i].cnt > 60) {
                boss_shot.bullet[i].state = 0;
                boss_shot.bullet[i].spd = 3.4;
                boss_shot.bullet[i].eff = 0;
            }
        }
    }
}

//花火っぽい
void boss_shot_bullet011() {
#define TM011 240
    int h, i, j, k, t = boss_shot.cnt % TM011, t2 = boss_shot.cnt;
    static double y, angle, baseangle;
    if (t == 0) {
        angle = rang(PI);
        int num = 0;
        baseangle = -bossatan2();
        baseangle *= -1;
        for (i = 0; i < 3; i++) {
            int column = 0;
            for (h = 0; h < 3; h++) {
                for (j = 0; j < 20; j++) {
                    if ((k = search_boss_shot()) != -1) {
                        boss_shot.bullet[k].flag = 1;
                        boss_shot.bullet[k].knd = 4;
                        boss_shot.bullet[k].cnt = 0;
                        boss_shot.bullet[k].col = i + 1;
                        boss_shot.bullet[k].x = boss.x;
                        boss_shot.bullet[k].y = boss.y;
                        boss_shot.bullet[k].vx = cos(baseangle + PI - PI2 / 3 / 2 + PI2 / 3 / 2 * i) * 3.1;
                        boss_shot.bullet[k].vy = sin(baseangle + PI - PI2 / 3 / 2 + PI2 / 3 / 2 * i) * 3.1;
                        boss_shot.bullet[k].state = num;
                        boss_shot.bullet[k].rem_spd[0] = column;
                        boss_shot.bullet[k].till = 150;
                        //boss_shot.bullet[k].bomb_resist=1;
                        boss_shot.bullet[k].power = 2;
                        se.SetSEFlag(10);
                        num++;
                    }
                }
                column++;
            }
        }
    }
    for (i = 0; i < BOSS_BULLET_MAX; i++) {
        if (boss_shot.bullet[i].flag > 0) {
            boss_shot.bullet[i].x += boss_shot.bullet[i].vx;
            boss_shot.bullet[i].y += boss_shot.bullet[i].vy;
            boss_shot.bullet[i].angle = atan2(boss_shot.bullet[i].vy, boss_shot.bullet[i].vx);
            if (boss_shot.bullet[i].state > -1 && boss_shot.bullet[i].cnt > 40) {
                int column = (int)boss_shot.bullet[i].rem_spd[0];
                double thisangle = angle + PI2 / 20 * (boss_shot.bullet[i].state % 20) + PI2 / 20 / 3 * column;
                double spd = 1.5 + column * 0.5;
                boss_shot.bullet[i].vx = cos(thisangle) * spd;
                boss_shot.bullet[i].vy = sin(thisangle) * spd;
                boss_shot.bullet[i].knd = 0;
                boss_shot.bullet[i].state = -1;
            }
            if (boss_shot.bullet[i].state == -1 && boss_shot.bullet[i].cnt < 130) {
                boss_shot.bullet[i].vy += 0.06;
            }
        }
    }
}




//ダブル波粒
void boss_shot_bullet014() {
#define POS014 60
    int i, j, k, t = boss_shot.cnt;
    static double y, angle, aangle;
    if (t == 0) {
        angle = rang(PI);
        for (i = 0; i < 36; i++) {
            if ((k = search_boss_shot()) != -1) {
                boss_shot.bullet[k].flag = 1;
                boss_shot.bullet[k].col = 1;
                boss_shot.bullet[k].x = boss.x;
                boss_shot.bullet[k].y = boss.y;
                boss_shot.bullet[k].knd = 0;
                boss_shot.bullet[k].angle = angle + PI2 / 36 * i;
                boss_shot.bullet[k].cnt = 0;
                boss_shot.bullet[k].spd = 4.6;
                boss_shot.bullet[k].eff = 1;
                boss_shot.bullet[k].power = 30;
            }
        }
        se.SetSEFlag(10);
    }
    if (t % 4 == 0) {
        for (j = 0; j < 2; j++) {
            for (i = 0; i < 6; i++) {
                if ((k = search_boss_shot()) != -1) {
                    boss_shot.bullet[k].flag = 1;
                    boss_shot.bullet[k].col = 3;
                    boss_shot.bullet[k].x = boss.x + (j == 0 ? POS014 : -POS014);
                    boss_shot.bullet[k].y = boss.y + 30;
                    boss_shot.bullet[k].knd = 0;
                    boss_shot.bullet[k].angle = (j == 0 ? PI + angle : PI - angle) + PI2 / 6 * i;
                    boss_shot.bullet[k].cnt = 0;
                    boss_shot.bullet[k].spd = 3.8;
                    boss_shot.bullet[k].eff_detail = 1;
                    boss_shot.bullet[k].power = 2;
                }
            }
        }
        se.SetSEFlag(10);
        aangle += PI2 / 2160;
    }
    angle -= aangle;
    if (angle < -PI2) {
        angle += PI2;
    }
}

//2か所からランダムへにょり
void boss_shot_bullet015() {
#define TM015 240
#define POS015 70
    int h, i, j, k, t = boss_shot.cnt % TM015, t2 = boss_shot.cnt;
    static double y, angle, baseangle, aangle;
    if (t == 0) {
        angle = rang(PI);
    }
    if (t % 7 == 0 && t < 160) {
        for (h = 0; h < 2; h++) {
            for (j = 0; j < 3; j++) {
                for (i = 0; i < 3; i++) {
                    if ((k = search_boss_shot()) != -1) {
                        boss_shot.bullet[k].flag = 1;
                        boss_shot.bullet[k].col = (h == 0 ? 1 : 2);
                        boss_shot.bullet[k].x = boss.x + (h == 0 ? POS015 : -POS015);
                        boss_shot.bullet[k].y = boss.y;
                        boss_shot.bullet[k].knd = 1;
                        boss_shot.bullet[k].angle = angle + PI2 / 3 * j - PI2 / 10 / 2 + PI2 / 10 / 2 * i;
                        boss_shot.bullet[k].cnt = 0;
                        boss_shot.bullet[k].spd = 2.9;
                        boss_shot.bullet[k].base_angle[0] = PI2 / 360;
                        boss_shot.bullet[k].power = 7;
                    }
                }
            }
        }
        se.SetSEFlag(10);
    }
    angle += PI2 / 150 * 1.5;
    for (i = 0; i < BOSS_BULLET_MAX; i++) {
        if (boss_shot.bullet[i].flag > 0) {
            if (boss_shot.bullet[i].cnt < 100) {
                boss_shot.bullet[i].angle += (i % 2 == 0 ? boss_shot.bullet[i].base_angle[0] : -boss_shot.bullet[i].base_angle[0]);
            }
        }
    }
}*/

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
