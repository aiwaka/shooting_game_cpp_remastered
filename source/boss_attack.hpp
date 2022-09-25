#pragma once

#include <vector>
#include <memory>


class Boss;

/**
 * @brief ボス敵の攻撃を扱うクラス.
 * @brief 攻撃内容だけでなく制限時間・体力も扱う
 */
class BossAttack {
public:
    BossAttack();
    virtual ~BossAttack() = default;
    void attack(Boss* boss);

    //! @brief 指定されたidの攻撃の体力と制限時間を返す
    std::array<int, 2> get_hp_and_time(int id);

private:
    using AttackFunc = void(BossAttack::*)(Boss* boss);
    //! @brief パターンに体力・時間の情報を持たせるための構造体. これらはボスクラスで攻撃を登録するときにコピーするためのみに使用される.
    //! @brief _patternは攻撃中常に参照される
    struct AttackPattern {
        int _hp;
        int _time_limit;
        AttackFunc _pattern;
    };
    // 体力や制限時間も一緒に保持した配列を作成する.
    std::vector<AttackPattern> _attack_pattern_list;

    //! @brief 配列埋め用ダミー
    void pattern_dummy(Boss* boss);
    void pattern_001(Boss* boss);
    void pattern_002(Boss* boss);
    void pattern_003(Boss* boss);
    void pattern_004(Boss* boss);
    //void pattern_010(Boss* boss);
    //void pattern_011(Boss* boss);
    //void pattern_012(Boss* boss);
    //void pattern_013(Boss* boss);
    //void pattern_014(Boss* boss);
};

/*
memo
bg1: 6, 9, 7, 5, 15
bg2: 12, 9, 11, 5, 10
bg3: 13, 9, 7, 5, 14
6->1, 12->2, 13->3, 9->4, 7->5, dummy 11->7, 5->8, 15->9, 10->10, 14->11, と変更
*/
