#include "boss_attack.hpp"
#include "boss.hpp"
#include "macro.hpp"
#include "global_define.hpp"
#include "enemy_bullet_manager.hpp"

BossAttack::BossAttack() {
    using AttackPattern = BossAttack::AttackPattern;
    // 体力・制限時間・関数へのポインタをあわせてセットする
    _attack_pattern_list.push_back(AttackPattern{ 1000, 3600, &BossAttack::pattern_006 });
    _attack_pattern_list.push_back(AttackPattern{ 1000, 3600, &BossAttack::pattern_dummy });
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
void BossAttack::pattern_006(Boss* boss) {
    int count = boss->get_counter();
    Vec2 boss_pos = boss->get_pos();
    if (count == 0) {
        // 最初に子機を準備
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 8; ++j) {
                EnemyBulletInfo info;
                info.bullet_type = i * 8 + j; // 子機番号として使う
                Vec2 pos = boss->get_pos();
                info.x = pos.x;
                info.y = pos.y;
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


//回転弾　花っぽい
void boss_shot_bullet009() {
#define TM009 200
    int i, j, k, t = boss_shot.cnt % TM009, t2 = boss_shot.cnt;
    static int cnum;
    static double angle, chilang;
    if (t2 == 0) {
        cnum = 0;
    }

    if (t == 0) {
        chilang = bossatan2();
        for (i = 0; i < 3; i++) {
            if ((k = child_search()) != -1) {
                child[k].flag = 1;
                child[k].cnt = 0;
                child[k].angle = chilang + PI2 / 3 * i;
                child[k].range = 0.5;
                child[k].spd = 3;
                child[k].x = boss.x;
                child[k].y = boss.y;
            }
        }
        if (cnum % 3 == 0) {
            move_boss_pos(40, 30, FMX - 40, 120, 60, 60);
        }
    }
    if (t % 5 == 0) {
        for (j = 0; j < CHILD_MAX; j++) {
            if (child[j].flag > 0) {
                angle = child[j].angle;
                for (i = 0; i < 7; i++) {
                    if ((k = search_boss_shot()) != -1) {
                        boss_shot.bullet[k].flag = 1;
                        boss_shot.bullet[k].cnt = 0;
                        boss_shot.bullet[k].col = 2;
                        boss_shot.bullet[k].knd = 1;
                        boss_shot.bullet[k].x = child[j].x;
                        boss_shot.bullet[k].y = child[j].y;
                        boss_shot.bullet[k].spd = 3;
                        boss_shot.bullet[k].angle = angle + PI2 / 7 * i;
                        boss_shot.bullet[k].base_angle[0] = PI / 60;
                        boss_shot.bullet[k].power = 5;
                        boss_shot.bullet[k].till = 150;
                    }
                }
                se.SetSEFlag(10);
                if (child[j].cnt > 80) {
                    child[j].flag = 0;
                }
            }
        }
    }
    for (i = 0; i < BOSS_BULLET_MAX; i++) {
        if (boss_shot.bullet[i].flag > 0) {
            if (boss_shot.bullet[i].cnt < 100) {
                boss_shot.bullet[i].angle += boss_shot.bullet[i].base_angle[0];
            }
        }
    }
    for (i = 0; i < CHILD_MAX; i++) {
        if (child[i].flag > 0) {
            child[i].angle += PI2 / 360;
        }
    }
    if (t == TM009 - 1) {
        cnum++;
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

//一つの魔法陣から2色楔弾
void boss_shot_bullet012() {
    int i, j, k, t = boss_shot.cnt;
#define CHILD_NUM 0
    static double y, angle, baseangle, childang;
    if (t == 0) {
        childang = rang(PI);
        angle = rang(PI);
    }
    child[CHILD_NUM].flag = 1;
    child[CHILD_NUM].cnt = 0;
    child[CHILD_NUM].range = 0.5;
    child[CHILD_NUM].angle = childang;
    child[CHILD_NUM].spd = 0;
    child[CHILD_NUM].x = cos(childang) * 75 + boss.x;
    child[CHILD_NUM].y = sin(childang) * 75 + boss.y;

    if (t % 4 == 0) {
        for (j = 0; j < 2; j++) {
            for (i = 0; i < 7; i++) {
                if ((k = search_boss_shot()) != -1) {
                    boss_shot.bullet[k].flag = 1;
                    boss_shot.bullet[k].cnt = 0;
                    boss_shot.bullet[k].knd = 5;
                    boss_shot.bullet[k].col = j == 0 ? 1 : 5;
                    boss_shot.bullet[k].angle = angle + (t * 0.3) + PI2 / 7 * i;
                    boss_shot.bullet[k].spd = j == 0 ? 2.8 : 3.4;
                    boss_shot.bullet[k].x = child[CHILD_NUM].x;
                    boss_shot.bullet[k].y = child[CHILD_NUM].y;
                    boss_shot.bullet[k].power = 5;
                    se.SetSEFlag(10);
                }
            }
        }
    }
    childang += PI2 / 120;
}

//へにょり交差弾
void boss_shot_bullet013() {
#define TM013 240
    int i, j, k, t = boss_shot.cnt % TM013, t2 = boss_shot.cnt;
    static double y, angle, baseangle;
    if (t == 0) {
        baseangle = rang(PI);
    }
    if (t % 9 == 0 && t < 150) {
        angle = baseangle + t * 0.1;
        for (j = 0; j < 2; j++) {
            for (i = 0; i < 10; i++) {
                if ((k = search_boss_shot()) != -1) {
                    boss_shot.bullet[k].flag = 1;
                    boss_shot.bullet[k].cnt = 0;
                    boss_shot.bullet[k].knd = 0;
                    boss_shot.bullet[k].col = 4;
                    boss_shot.bullet[k].x = boss.x;
                    boss_shot.bullet[k].y = boss.y;
                    boss_shot.bullet[k].angle = angle + PI2 / 10 * i;
                    boss_shot.bullet[k].spd = 4.4;
                    boss_shot.bullet[k].till = 50;
                    boss_shot.bullet[k].power = 3;
                    boss_shot.bullet[k].state = j == 0 ? 0 : 1;
                    boss_shot.bullet[k].base_angle[0] = j == 0 ? PI2 / 360 : -PI2 / 360;
                    se.SetSEFlag(10);
                }
            }
        }
    }
    for (i = 0; i < BOSS_BULLET_MAX; i++) {
        if (boss_shot.bullet[i].flag > 0) {
            if (boss_shot.bullet[i].cnt < 90) {
                boss_shot.bullet[i].angle += boss_shot.bullet[i].base_angle[0];
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
