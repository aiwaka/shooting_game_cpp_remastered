#pragma once

#include <vector>
#include <memory>

// abstract_enemy.hpp��enemy_mover.hpp��ǂݍ���ł���z�Q�ƂɂȂ�̂�, �^�������錾���Ă�����ŉ������Ă��炤.
class AbstractEnemy;

class EnemyMover {
public:
    EnemyMover();
    virtual ~EnemyMover() = default;
    void move(AbstractEnemy* enemy);

private:
    using MoveFunc = void(EnemyMover::*)(AbstractEnemy* enemy);
    std::vector<MoveFunc> _move_pattern;

    //! @brief �������Ď~�܂�A�܂�������
    void move_pattern_00(AbstractEnemy* enemy);
    //! @brief �����ֈړ�
    void move_pattern_01(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    void move_pattern_02(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    void move_pattern_03(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    void move_pattern_04(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    void move_pattern_05(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    void move_pattern_06(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    void move_pattern_07(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    void move_pattern_08(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    void move_pattern_09(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    void move_pattern_10(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    void move_pattern_11(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    void move_pattern_12(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    void move_pattern_13(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    void move_pattern_14(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    void move_pattern_15(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    void move_pattern_16(AbstractEnemy* enemy);
};

