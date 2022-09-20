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

    // NOTE: ���݂̈ړ��p�^�[���͔z��Y��0, 5, 6, 9, 11, 12, 13�̂ݗp�����Ă���̂ł���ȊO�͓K���ɖ��߂�
    //! @brief �z�񖄂ߗp�_�~�[
    void move_pattern_dummy(AbstractEnemy* enemy);
    //! @brief �������Ď~�܂�, �㏸����
    void move_pattern_00(AbstractEnemy* enemy);
    //! @brief �������Ď~�܂�, �����ֈړ�
    //void move_pattern_01(AbstractEnemy* enemy);
    //! @brief �������Ď~�܂�, �E���ֈړ�
    //void move_pattern_02(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    //void move_pattern_03(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    //void move_pattern_04(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    void move_pattern_05(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    void move_pattern_06(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    //void move_pattern_07(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    //void move_pattern_08(AbstractEnemy* enemy);
    //! @brief ����Ĉ�莞�Ԓ�؂��ď㏸
    void move_pattern_09(AbstractEnemy* enemy);
    //! @brief �E���ֈړ�
    //void move_pattern_10(AbstractEnemy* enemy);
    //! @brief ���@��_��
    void move_pattern_11(AbstractEnemy* enemy);
    //! @brief ������E�ֈړ�
    void move_pattern_12(AbstractEnemy* enemy);
    //! @brief �E���獶�ֈړ�
    void move_pattern_13(AbstractEnemy* enemy);
};

