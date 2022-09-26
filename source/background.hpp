#pragma once

#include <array>
#include <memory>
#include "euclid_vec.hpp"
#include "abstract_bg.hpp"

class Background final : public AbstractBackground {
public:
    Background(int initial_type);
    ~Background() = default;
    bool update() override;
    void draw() const override;

    void set_bg(int type) override;
    int get_bg() const override;

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
    std::array<int, 7> _handles; // �w�i�^�C�v6�̓n���h���z���5�Ԃ�6�Ԃ𗼕��g��
    int _img_height;

    std::array<std::shared_ptr<Quadrangle>, BG_NUM> _list;
};


inline int Background::get_bg() const { return _bg_type; }
