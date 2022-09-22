#pragma once

#include <vector>
#include <memory>

class AbstractEnemy;

/**
 * @brief 敵の攻撃タイプ情報を扱うクラス.
 */
class EnemyAttack {
public:
    EnemyAttack();
    virtual ~EnemyAttack() = default;
    void attack(AbstractEnemy* enemy);

private:
    using AttackFunc = void(EnemyAttack::*)(AbstractEnemy* enemy);
    std::vector<AttackFunc> _attack_pattern;

    //! @brief 配列埋め用ダミー
    void attack_pattern_dummy(AbstractEnemy* enemy);
    void attack_pattern_00(AbstractEnemy* enemy);
    void attack_pattern_01(AbstractEnemy* enemy);
    void attack_pattern_02(AbstractEnemy* enemy);
    void attack_pattern_04(AbstractEnemy* enemy);
    void attack_pattern_05(AbstractEnemy* enemy);
    void attack_pattern_07(AbstractEnemy* enemy);
    void attack_pattern_08(AbstractEnemy* enemy);
    void attack_pattern_09(AbstractEnemy* enemy);
    void attack_pattern_10(AbstractEnemy* enemy);
    void attack_pattern_11(AbstractEnemy* enemy);
};

