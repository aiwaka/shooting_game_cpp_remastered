#include <cmath>
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
    _attack_pattern_list.push_back(AttackPattern{ 1000, 3600, &BossAttack::pattern_005 });
    _attack_pattern_list.push_back(AttackPattern{ 1000, 3600, &BossAttack::pattern_dummy }); // あとで追加するかもしれないので欠番
    _attack_pattern_list.push_back(AttackPattern{ 1000, 3600, &BossAttack::pattern_007 });
    _attack_pattern_list.push_back(AttackPattern{ 1000, 3600, &BossAttack::pattern_008 });
    _attack_pattern_list.push_back(AttackPattern{ 1000, 3600, &BossAttack::pattern_009 });
    _attack_pattern_list.push_back(AttackPattern{ 1000, 3600, &BossAttack::pattern_010 });
    _attack_pattern_list.push_back(AttackPattern{ 1000, 3600, &BossAttack::pattern_011 });
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

// 二重逆回転ワインダー
void BossAttack::pattern_005(Boss* boss) {
    int count = boss->get_counter();
    int local_count = count % 320; // 320フレーム周期
    Vec2 boss_pos = boss->get_pos();
    //static double angle, aangle, base_angle;
    static float base_angle = 0.0; // 基本の発射角度
    static float angle = 0.0; // 基本の発射角度からの回転角度
    static float angle_acc = 0.0; // 回転角度加算の加算量. これを増加させる
    if (local_count == 0) {
        base_angle = angle = utils::rand_in_range(GlobalValues::PI);
        angle_acc = 0.0;
    }
    if (local_count % 2 == 0 && local_count < 240) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 4; ++j) {
                EnemyBulletInfo info;
                info.bullet_type = 0;
                info.color = 2;
                info.damage = 3;
                info.x = boss_pos.x;
                info.y = boss_pos.y;
                info.angle = base_angle + (i == 0 ? angle : -angle) + GlobalValues::PI * static_cast<float>(j) / 2.0;
                info.speed = 3.0;
                info.fx_detail = 1;
                boss->push_bullet(info);
            }
        }
        // se
        angle_acc += GlobalValues::PI / 1080.0;
    }
    angle += angle_acc;
}

// 花火
void BossAttack::pattern_007(Boss* boss) {
    int count = boss->get_counter();
    int local_count = count % 240; // 240フレーム周期
    Vec2 boss_pos = boss->get_pos();
    static float angle = 0.0;
    if (local_count == 0) {
        angle = utils::rand_in_range(GlobalValues::PI);
        int num = 0;

        for (int i = 0; i < 3; ++i) {
            // 枠付きの弾を発射
            EnemyBulletInfo info;
            info.bullet_type = 4;
            info.color = i + 1;
            info.damage = 70;
            info.x = boss_pos.x;
            info.y = boss_pos.y;
            info.angle = GlobalValues::PI * (-5.0 / 6.0 + static_cast<float>(i) / 3.0);
            info.speed = 3.1;
            boss->push_bullet(info);
        }

    }
    auto bullet_list = boss->get_bullet_iterator();
    for (auto& bullet : bullet_list) {
        if (bullet->get_type() == 4 && bullet->get_counter() == 40) {
            Vec2 bullet_pos = bullet->get_pos();
            int bullet_color = bullet->get_color();
            bullet->set_delete_flag();
            float base_angle = utils::rand_in_range(GlobalValues::PI);
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 20; ++j) {
                    float angle = base_angle + GlobalValues::PI * (static_cast<float>(j) + static_cast<float>(i) / 3.0) / 10.0;
                    float speed = 1.5f + static_cast<float>(i) * 0.5;
                    EnemyBulletInfo info;
                    info.bullet_type = 0;
                    info.color = bullet_color;
                    info.endure_count = 150;
                    info.damage = 3;
                    info.x = bullet_pos.x;
                    info.y = bullet_pos.y;
                    info.angle = angle;
                    info.speed = speed;
                    boss->push_bullet(info);
                }
            }
        }
        int bullet_count = bullet->get_counter();
        if (bullet->get_type() == 0) {
            Vec2 pos = bullet->get_pos();
            // 重力で落下するように見せるための補正. 130カウント以降は加速度はなくなるとする
            int pos_y_offset = 0.0008 * static_cast<float>(min(16900, bullet_count * bullet_count));
            pos.y += pos_y_offset;
            bullet->set_pos(pos);
        }
    }
}

// 子機を展開してそこから円形発射を延々と行う
void BossAttack::pattern_008(Boss* boss) {
    int count = boss->get_counter();
    int local_count = count % 200; // 200フレーム周期
    Vec2 boss_pos = boss->get_pos();
    //#define CHILD_TIME005 240
    constexpr int CHILD_LIMIT_COUNT = 240;
    //static double tm;
    if (local_count == 0) {
        float angle = boss->get_angle_to_player();
        for (int i = 0; i < 5; ++i) {
            EnemyBulletInfo info;
            info.angle = angle + GlobalValues::PI * 2.0 * static_cast<float>(i) / 5.0f;
            info.x = boss_pos.x;
            info.y = boss_pos.y;
            info.speed = 1.8;
            boss->push_child(info);
        }
    }
    if (local_count <= 200 && local_count % 25 == 0) {
        auto child_list = boss->get_child_iterator();
        for (auto& child : child_list) {
            if (child->get_counter() > CHILD_LIMIT_COUNT) {
                child->delete_child();
            }
            Vec2 child_pos = child->get_pos();
            float angle = std::atan2f(boss_pos.y - child_pos.y, boss_pos.x - child_pos.x);
            for (int i = 0; i < 8; ++i) {
                EnemyBulletInfo info;
                info.bullet_type = 4;
                info.color = 3;
                info.endure_count = 200;
                info.damage = 3;
                info.x = child_pos.x;
                info.y = child_pos.y;
                info.angle = angle + GlobalValues::PI * static_cast<float>(i) / 4.0;
                info.speed = 4.0;
                info.fx_detail = 1;
                boss->push_bullet(info);
            }
            // se
        }
    }
}

// 2つの子機からランダムな曲がる弾
void BossAttack::pattern_009(Boss* boss) {
    int count = boss->get_counter();
    int local_count = (count - 120) % 240; // 240フレーム周期で120フレーム遅れさせる
    Vec2 boss_pos = boss->get_pos();
    static float init_angle = 0.0;
    if (count == 0) {
        // 子機用意
        for (int i = 0; i < 2; ++i) {
            EnemyBulletInfo info;
            info.angle = GlobalValues::PI * static_cast<float>(i);
            info.bullet_type = i; // 識別番号（childになったあとはstateフィールドで参照）
            info.x = boss_pos.x;
            info.y = boss_pos.y;
            info.speed = 0.7;
            boss->push_child(info);
        }
    }
    if (count < 100) return;
    if (count == 100) {
        auto child_list = boss->get_child_iterator();
        for (auto& child : child_list) {
            child->set_speed(0.0);
        }
    }
    // ここから弾幕本体
    if (local_count == 0) {
        init_angle = utils::rand_in_range(GlobalValues::PI);
    }
    if (count >= 120 && local_count % 7 == 0 && local_count < 160) {
        auto child_list = boss->get_child_iterator();
        for (auto& child : child_list) {
            int i = child->get_state();
            Vec2 child_pos = child->get_pos();
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < 3; ++k) {
                    EnemyBulletInfo info;
                    info.bullet_type = 1;
                    info.color = i + 1;
                    info.damage = 6;
                    info.x = child_pos.x;
                    info.y = child_pos.y;
                    info.angle = init_angle + GlobalValues::PI * (static_cast<float>(2 * k) / 3.0 + static_cast<float>(j) / 10.0);
                    info.speed = 2.9;
                    info.omega = GlobalValues::PI / 180.0 * ((j + k) % 2 == 0 ? 1.0 : -1.0);
                    boss->push_bullet(info);
                }
            }
        }
        // se
    }
    init_angle += GlobalValues::PI / 75.0 * 1.5;
    auto bullet_list = boss->get_bullet_iterator();
    for (auto& bullet : bullet_list) {
        if (bullet->get_counter() == 100) {
            bullet->set_omega(0.0);
        }
    }
}

// sine波が二重に出る
void BossAttack::pattern_010(Boss* boss) {
    int count = boss->get_counter();
    int local_count = count % 240; // 240フレーム周期
    Vec2 boss_pos = boss->get_pos();
    //static double y, angle;
    static float base_angle = 0.0;
    if (local_count == 0) {
        base_angle = utils::rand_in_range(GlobalValues::PI);
    }
    if (local_count % 2 == 0 && local_count < 80) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 8; ++j) {
                float count_f = static_cast<float>(local_count);
                EnemyBulletInfo info;
                info.bullet_type = 0;
                info.color = i + 1;
                info.damage = 3;
                info.x = GlobalValues::IN_WIDTH / 80.0 * count_f;
                info.y = std::sinf(GlobalValues::PI / 40.0 * count_f) * 80.0 + boss_pos.y;
                info.angle = base_angle + GlobalValues::PI * (count_f / 40.0 + static_cast<float>(j) / 4.0 + (i == 0 ? 0.0 : 0.125));
                info.speed = i == 0 ? 3.4 : 0.0;
                info.fx_detail = i;
                boss->push_bullet(info);
                //boss_shot.bullet[k].state = i == 0 ? 0 : 1;
            }
        }
        // se
    }
    auto bullet_list = boss->get_bullet_iterator();
    for (auto& bullet : bullet_list) {
        if (bullet->get_color() == 2 && bullet->get_counter() == 60) {
            bullet->set_speed(3.4);
            bullet->set_fx(0);
        }

    }
}

// 子機2つから角度加速ワインダー
void BossAttack::pattern_011(Boss* boss) {
    //#define POS014 60
    constexpr int CHILD_DIFF_X = 60;
    int count = boss->get_counter();
    int local_count = count % 150; // 150フレーム周期
    Vec2 boss_pos = boss->get_pos();
    static float  angle, angle_acc;
    if (count == 0) {
        angle = utils::rand_in_range(GlobalValues::PI);
    }
    if (local_count == 0) {
        float angle_to_player = boss->get_angle_to_player();
        for (int i = 0; i < 36; ++i) {
            EnemyBulletInfo info;
            info.bullet_type = 0;
            info.color = 1;
            info.damage = 5;
            info.x = boss_pos.x;
            info.y = boss_pos.y;
            info.angle = angle_to_player + GlobalValues::PI * static_cast<float>(i) / 18.0;
            info.speed = 5.6;
            info.fx_detail = 1;
            boss->push_bullet(info);
        }
        // se
    }
    if (local_count % 4 == 0) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 6; ++j) {
                EnemyBulletInfo info;
                info.bullet_type = 0;
                info.color = 3;
                info.damage = 2;
                info.x = boss_pos.x + (i == 0 ? CHILD_DIFF_X : -CHILD_DIFF_X);
                info.y = boss_pos.y + 20.0;
                info.angle = (i == 0 ? angle : -angle) + GlobalValues::PI * static_cast<float>(j) / 3.0;
                info.speed = 4.0;
                info.fx_detail = 1;
                boss->push_bullet(info);
            }
        }
        // se
        angle_acc += GlobalValues::PI / 1080.0;
    }
    angle -= angle_acc;
    if (angle < -GlobalValues::PI) {
        angle += GlobalValues::PI;
    }
}

/*

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

}*/
