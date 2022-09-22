#pragma once

#include <array>
#include <memory>
#include <list>
#include "task.hpp"
#include "euclid_vec.hpp"
#include "enemy_mover.hpp"
#include "enemy_attack.hpp"
#include "enemy_bullet.hpp"

class EnemyManager;
struct EnemyInfo;

class AbstractEnemy : public Task {
public:
    AbstractEnemy(const EnemyInfo& info, EnemyManager* manager);
    virtual ~AbstractEnemy() = default;
    void initialize();
    bool update() override;

    Vec2 get_pos() const;
    void set_pos(Vec2 pos);
    int get_counter() const;
    Vec2 get_speed() const;
    void set_speed(Vec2 speed);
    int get_move_pattern() const;
    int get_enemy_type_id() const;
    int get_start_attack_count() const;
    int get_attack_pattern_id() const;
    int get_hp() const;
    void modify_hp(int delta);
    int get_bullet_id() const;
    int get_bullet_color() const;
    std::array<int, 6> get_item_id() const;

    // 敵管理クラスへのポインタを通じて自機の情報を得られるようにする
    Vec2 get_player_pos() const;
    //! @brief 自分（敵）から自機への角度を返す. 近すぎるときは鉛直下向きをを返す
    float get_angle_to_player() const;

    void push_bullet(EnemyBulletInfo& info);
    std::list<std::shared_ptr<EnemyBullet>> get_bullet_iterator() const;

    void set_f_slot(size_t idx, float val);
    void set_i_slot(size_t idx, int val);
    float get_f_slot(size_t idx) const;
    int get_i_slot(size_t idx) const;

protected:
    virtual void set_size() = 0;
    /**
     * @brief 現在位置が画面内かどうか
     */
    bool is_inside_field() const;

    EnemyMover _mover;
    EnemyAttack _attack;
    //! @brief この敵が撃った弾のポインタリスト. 弾を登録するときここに登録すれば, この敵が生きている間参照して情報を書き換えられる.
    std::list<std::shared_ptr<EnemyBullet>> _bullet_list;
    // 自分を管理するマネージャへの問い合わせ用ポインタ
    EnemyManager* _manager;

    int _counter;
    int _move_pattern_id;
    int _enemy_type_id;
    Vec2 _pos;
    Vec2 _speed;
    //! @brief 弾幕を撃ち始めるカウント
    int _start_attack_count;
    int _attack_pattern_id;
    int _hp;
    int _bullet_id;
    int _bullet_color;
    //! @brief 移動で使う、待機時間
    int _wait_time;
    //! @brief アイテムidを6個まで入れられる.
    std::array<int, 6> _item_slot;

    //! @brief テクスチャの大きさ
    int _texture_width;
    int _texture_height;

    //! @brief 実数の好きに使える値を保存するスロット.
    std::array<float, 5> _f_var_slot;
    std::array<int, 5> _i_var_slot;
};

inline Vec2 AbstractEnemy::get_pos() const { return _pos; }
inline void AbstractEnemy::set_pos(Vec2 pos) { _pos = pos; }
inline int AbstractEnemy::get_counter() const { return _counter; }
inline Vec2 AbstractEnemy::get_speed() const { return _speed; }
inline void AbstractEnemy::set_speed(Vec2 speed) { _speed = speed; }
inline int AbstractEnemy::get_move_pattern() const { return _move_pattern_id; }
inline int AbstractEnemy::get_enemy_type_id() const { return _enemy_type_id; }
inline int AbstractEnemy::get_start_attack_count() const { return _start_attack_count; }
inline int AbstractEnemy::get_attack_pattern_id() const { return _attack_pattern_id; }
inline int AbstractEnemy::get_hp() const { return _hp; }
inline void AbstractEnemy::modify_hp(int delta) { _hp += delta; }
inline int AbstractEnemy::get_bullet_id() const { return _bullet_id; }
inline int AbstractEnemy::get_bullet_color() const { return _bullet_color; }
inline std::array<int, 6> AbstractEnemy::get_item_id() const { return _item_slot; }

