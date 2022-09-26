#pragma once

#include "task.hpp"

class AbstractBackground : public Task {
public:
    AbstractBackground() = default;
    virtual ~AbstractBackground() = default;

    virtual int get_bg() const = 0;
    virtual void set_bg(int type) = 0;
};
