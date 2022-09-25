#pragma once

#include <array>
#include <memory>
#include <list>
#include <queue>
#include "task.hpp"
#include "euclid_vec.hpp"
#include "boss_attack.hpp"
#include "boss_child.hpp"
#include "enemy_bullet.hpp"

class BossManager;
struct EnemyInfo;

class Boss : public Task {
public:
    Boss(std::queue<int> attack_patterns, bool is_big_boss, BossManager* manager);
    virtual ~Boss() = default;
    bool update() override;
    void draw() const override;

    void set_move(Vec2 target);

    Vec2 get_pos() const;
    void set_pos(Vec2 pos);
    int get_counter() const;
    int get_attack_pattern_id() const;
    int get_hp() const;
    int get_max_hp() const;
    void modify_hp(int delta);

    // 敵管理クラスへのポインタを通じて自機の情報を得られるようにする
    Vec2 get_player_pos() const;
    //! @brief 自分（敵）から自機への角度を返す. 近すぎるときは鉛直下向きをを返す
    float get_angle_to_player() const;

    void push_bullet(EnemyBulletInfo& info);
    void push_child(EnemyBulletInfo& info);
    std::list<std::shared_ptr<EnemyBullet>> get_bullet_iterator() const;
    std::list<std::shared_ptr<BossChild>> get_child_iterator() const;

    void set_f_slot(size_t idx, float val);
    void set_i_slot(size_t idx, int val);
    float get_f_slot(size_t idx) const;
    int get_i_slot(size_t idx) const;

protected:
    BossAttack _attack;
    //! @brief この敵が撃った弾のポインタリスト. 弾を登録するときここに登録すれば, この敵が生きている間参照して情報を書き換えられる.
    std::list<std::shared_ptr<EnemyBullet>> _bullet_list;
    //! @brief 子機を保存する
    std::list<std::shared_ptr<BossChild>> _child_list;
    BossManager* _manager;

    bool _is_big_boss;
    int _counter;
    int _time_limit;
    int _hp;
    int _max_hp;
    Vec2 _pos;
    //! @brief 現在の攻撃パターン番号
    int _attack_pattern_id;
    //! @brief 攻撃内容を入れておくキュー. ここから順番に取り出して処理していく.
    std::queue<int> _attack_patterns;

    //! @brief 実数の好きに使える値を保存するスロット.
    std::array<float, 5> _f_var_slot;
    std::array<int, 5> _i_var_slot;

    Vec2 _move_target;

    void move();
};

inline Vec2 Boss::get_pos() const { return _pos; }
inline void Boss::set_pos(Vec2 pos) { _pos = pos; }
inline int Boss::get_counter() const { return _counter; }
inline int Boss::get_attack_pattern_id() const { return _attack_pattern_id; }
inline int Boss::get_hp() const { return _hp; }
inline int Boss::get_max_hp() const { return _max_hp; }
inline void Boss::modify_hp(int delta) { _hp += delta; }


