#pragma once

#include <memory>
#include "task.hpp"
#include "euclid_vec.hpp"

class PlayerBulletManager;

class Player : public Task {
public:
    Player(std::shared_ptr<PlayerBulletManager> manager);
    virtual ~Player() = default;
    bool update() override;
    void draw() const override;

    Vec2 get_pos() const;

private:
    void move();
    void shot();

    std::shared_ptr<PlayerBulletManager>_bullet_manager;

    Vec2 _pos;
    int _counter;
    //! @brief ‚±‚ÌƒtƒŒ[ƒ€‚Å‚ÌˆÚ“®•ûŒü.
    Vec2 _move_dir;
};

inline Vec2 Player::get_pos() const { return _pos; }
