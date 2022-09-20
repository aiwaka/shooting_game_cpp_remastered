#pragma once

#include <vector>
#include <memory>

class AbstractEnemy;

/**
 * @brief �G�̍U���^�C�v���������N���X.
 */
class EnemyAttack {
public:
    EnemyAttack();
    virtual ~EnemyAttack() = default;
    void attack(AbstractEnemy* enemy);

private:
    using AttackFunc = void(EnemyAttack::*)(AbstractEnemy* enemy);
    std::vector<AttackFunc> _attack_pattern;

    //! @brief �z�񖄂ߗp�_�~�[
    void attack_pattern_dummy(AbstractEnemy* enemy);
    void attack_pattern_00(AbstractEnemy* enemy);
};

