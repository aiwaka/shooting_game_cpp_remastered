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
    void attack_pattern_dummy(Boss* boss);
    //void attack_pattern_00(Boss* boss);
    //void attack_pattern_01(Boss* boss);
    //void attack_pattern_02(Boss* boss);
    //void attack_pattern_04(Boss* boss);
    //void attack_pattern_05(Boss* boss);
    //void attack_pattern_07(Boss* boss);
};

