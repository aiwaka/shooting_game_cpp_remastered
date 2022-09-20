#pragma once
#include <cstdint>

class GlobalValues final {
public:
    const static std::uint16_t SCREEN_WIDTH;
    const static std::uint16_t SCREEN_HEIGHT;

    const static float PI;

    // OUTは外枠, INは内枠
    const static int OUT_WIDTH;
    const static int OUT_HEIGHT;
    const static int IN_WIDTH;
    const static int IN_HEIGHT;
    // 移動可能範囲の中心座標
    const static int CENTER_X;
    const static int CENTER_Y;
    // 内枠の左上の座標
    const static int IN_TOP_LEFT_X;
    const static int IN_TOP_LEFT_Y;

    enum Stage {
        Stage1,
    };

    enum Level {
        Easy,
        Normal,
        Hard,
    };
};
