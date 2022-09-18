#pragma once
#include <cstdint>

class GlobalValues final {
public:
    const static std::uint16_t SCREEN_WIDTH;
    const static std::uint16_t SCREEN_HEIGHT;

    const static float PI;

    enum Stage {
        Stage1,
    };

    enum Level {
        Easy,
        Normal,
        Hard,
    };
};
