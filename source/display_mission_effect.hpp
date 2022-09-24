#pragma once

#include "abstract_effect.hpp"
#include "effect_manager.hpp"
#include "euclid_vec.hpp"


class DisplayMissionEffect final : public AbstractEffect {
public:
    DisplayMissionEffect();
    ~DisplayMissionEffect() = default;
    bool update() override;
    void draw() const override;

private:
    int _handle;
};
