#pragma once

#include <vector>
#include <memory>

// abstract_enemy.hpp‚Åenemy_mover.hpp‚ğ“Ç‚İ‚ñ‚Å‚¨‚èzŠÂQÆ‚É‚È‚é‚Ì‚Å, Œ^–¼‚¾‚¯éŒ¾‚µ‚Ä‚¨‚«Œã‚Å‰ğŒˆ‚µ‚Ä‚à‚ç‚¤.
class AbstractEnemy;

class EnemyMover {
public:
    EnemyMover();
    virtual ~EnemyMover() = default;
    void move(AbstractEnemy* enemy);

private:
    using MoveFunc = void(EnemyMover::*)(AbstractEnemy* enemy);
    std::vector<MoveFunc> _move_pattern;

    //! @brief ‰º‚ª‚Á‚Ä~‚Ü‚èA‚Ü‚½‰º‚ª‚é
    void move_pattern_00(AbstractEnemy* enemy);
    //! @brief ¶‰º‚ÖˆÚ“®
    void move_pattern_01(AbstractEnemy* enemy);
    //! @brief ‰E‰º‚ÖˆÚ“®
    void move_pattern_02(AbstractEnemy* enemy);
};

