#include <DxLib.h>
#include "global_define.hpp"
#include "abstract_effect.hpp"
#include "effect_manager.hpp"
#include "image_manager.hpp"


AbstractEffect::AbstractEffect() :
    _counter(0),
    _finished(false),

    _f_var_slot{ std::array<float, 6>{} },
    _i_var_slot{ std::array<int, 6>{} }
{}

void AbstractEffect::set_f_slot(size_t idx, float val) {
    this->_f_var_slot[idx] = val;
}
void AbstractEffect::set_i_slot(size_t idx, int val) {
    this->_i_var_slot[idx] = val;
}
float AbstractEffect::get_f_slot(size_t idx) const {
    return this->_f_var_slot[idx];
}
int AbstractEffect::get_i_slot(size_t idx) const {
    return this->_i_var_slot[idx];
}