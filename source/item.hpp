#pragma once

#include "task.hpp"
#include "euclid_vec.hpp"

class Item : public Task {
public:
    Item(Vec2 pos, int type);
    ~Item() = default;
    bool update() override;
    void draw() const override;

    Vec2 get_pos() const;
    int get_type() const;

public:
    int _counter;

    Vec2 _pos;
    int _type;

    //! @brief 出現時の位置のズレを表す
    Vec2 _spawn_offset;

    bool is_inside_field() const;
};

inline Vec2 Item::get_pos() const { return _pos; }
inline int Item::get_type() const { return _type; }
