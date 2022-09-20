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
};

