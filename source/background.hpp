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

    void set_bg(int type);

private:
    class Quadrangle {
    public:
        const int img;
        Vec2 pos;

        Quadrangle(float x, float y, int img) : pos(Vec2{ x, y }), img(img) {}
    };

    int _bg_type;
    //! @brief �w�i����ׂ閇��
    const static int BG_NUM = 6;
    std::array<int, 7> _handles;
    int _img_height;

    std::array<std::shared_ptr<Quadrangle>, BG_NUM> _list;
};
