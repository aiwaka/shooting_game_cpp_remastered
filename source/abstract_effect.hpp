#pragma once

#include <array>
#include <memory>
#include <list>
#include "task.hpp"
#include "euclid_vec.hpp"

class EffectManager;

class AbstractEffect : public Task {
public:
    AbstractEffect();
    virtual ~AbstractEffect() = default;

    void increment_counter();
    bool is_finished() const;

protected:
    void set_f_slot(size_t idx, float val);
    void set_i_slot(size_t idx, int val);
    float get_f_slot(size_t idx) const;
    int get_i_slot(size_t idx) const;

    //! @brief _finishedをtrueにする.
    void finish();
    int get_counter() const;

private:
    int _counter;
    bool _finished;

    //! @brief 実数の好きに使える値を保存するスロット.
    std::array<float, 6> _f_var_slot;
    std::array<int, 6> _i_var_slot;
};

inline void AbstractEffect::finish() { _finished = true; }
inline bool AbstractEffect::is_finished() const { return _finished; }
inline void AbstractEffect::increment_counter() { ++_counter; }
inline int AbstractEffect::get_counter() const { return _counter; }
