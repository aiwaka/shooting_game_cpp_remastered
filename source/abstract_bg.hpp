#pragma once

#include "task.hpp"

class AbstractBackground : public Task {
public:
    AbstractBackground() = default;
    virtual ~AbstractBackground() = default;
};
