#pragma once

#include "task.hpp"
#include "euclid_vec.hpp"

class Player : public Task {
public:
    Player();
    virtual ~Player() = default;
    bool update() override;
    void draw() const override;

    Vec2 get_pos() const;

private:
    void move();

    Vec2 _pos;
    int _counter;
    //! @brief ‚±‚ÌƒtƒŒ[ƒ€‚Å‚ÌˆÚ“®•ûŒü.
    Vec2 _move_dir;
};

inline Vec2 Player::get_pos() const { return _pos; }
