#pragma once

#include <array>
#include <memory>
#include "euclid_vec.hpp"
#include "abstract_bg.hpp"

class FullScreenPicture final : public AbstractBackground {
public:
    FullScreenPicture(int initial_type);
    ~FullScreenPicture() = default;
    bool update() override;
    void draw() const override;

    void set_bg(int type) override;
    int get_bg() const override;

private:
    int _bg_type;
    int _handle;
};
inline int FullScreenPicture::get_bg() const { return _bg_type; }
