#pragma once

#include <array>
#include <memory>
#include "euclid_vec.hpp"
#include "abstract_bg.hpp"

class Background final : public AbstractBackground {
public:
    Background();
    ~Background() = default;
    bool update() override;
    void draw() const override;

private:
    class Quadrangle {
    public:
        const int img;
        Vec2 pos;

        Quadrangle(float x, float y, int img) : pos(Vec2{ x, y }), img(img) {}
    };

    const static int BG_NUM = 4;
    std::array<std::shared_ptr<Quadrangle>, BG_NUM> _list;
};
