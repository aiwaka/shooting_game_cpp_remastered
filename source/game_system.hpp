#pragma once

class GameSystem {
public:
    GameSystem() = default;
    ~GameSystem() = default;
    bool initialize() const;
    void main() const;
    void finalize() const;
};
