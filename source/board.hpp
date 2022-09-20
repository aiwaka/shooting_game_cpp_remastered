#pragma once

#include "task.hpp"

class Board final : public Task {
public:
    Board() = default;
    virtual ~Board() = default;
    bool update() override;
    void draw() const override;

private:
    //void drawFrame() const;
};
