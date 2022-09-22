#include <DxLib.h>
#include <string>
#include <algorithm>
#include "pad_input.hpp"
#include "keyboard.hpp"
#include "global_define.hpp"

using std::max;

PadInput::PadInput() : _pad_input{ std::array<int, PAD_KEY_NUM>{} }
{
    _id_assign[PadInputType::Down] = 0;
    _id_assign[PadInputType::Left] = 1;
    _id_assign[PadInputType::Right] = 2;
    _id_assign[PadInputType::Up] = 3;
    _id_assign[PadInputType::Bomb] = 4;
    _id_assign[PadInputType::Shot] = 5;
    _id_assign[PadInputType::Slow] = 11;
    _id_assign[PadInputType::Start] = 12;
    _id_assign[PadInputType::Sub] = 8;
}

void PadInput::update()
{
    int pad_input;
    pad_input = GetJoypadInputState(DX_INPUT_PAD1);
    for (int i = 0; i < 16; ++i) {
        // ビット探索ですべての入力を更新できる
        if (pad_input & (1 << i)) {
            _pad_input[i]++;
        }
        else {
            _pad_input[i] = 0;
        }
    }
    merge();
}

void PadInput::merge()
{
    _pad_input[_id_assign[PadInputType::Left]] = max(_pad_input[_id_assign[PadInputType::Left]], Keyboard::get_instance()->get_pressing_count(KEY_INPUT_LEFT));
    _pad_input[_id_assign[PadInputType::Up]] = max(_pad_input[_id_assign[PadInputType::Up]], Keyboard::get_instance()->get_pressing_count(KEY_INPUT_UP));
    _pad_input[_id_assign[PadInputType::Right]] = max(_pad_input[_id_assign[PadInputType::Right]], Keyboard::get_instance()->get_pressing_count(KEY_INPUT_RIGHT));
    _pad_input[_id_assign[PadInputType::Down]] = max(_pad_input[_id_assign[PadInputType::Down]], Keyboard::get_instance()->get_pressing_count(KEY_INPUT_DOWN));
    // shotはZでもEnterでも同じ働きになるように
    _pad_input[_id_assign[PadInputType::Shot]] = max(_pad_input[_id_assign[PadInputType::Shot]], Keyboard::get_instance()->get_pressing_count(KEY_INPUT_Z));
    _pad_input[_id_assign[PadInputType::Shot]] = max(_pad_input[_id_assign[PadInputType::Shot]], Keyboard::get_instance()->get_pressing_count(KEY_INPUT_RETURN));
    _pad_input[_id_assign[PadInputType::Bomb]] = max(_pad_input[_id_assign[PadInputType::Bomb]], Keyboard::get_instance()->get_pressing_count(KEY_INPUT_X));
    _pad_input[_id_assign[PadInputType::Slow]] = max(_pad_input[_id_assign[PadInputType::Slow]], Keyboard::get_instance()->get_pressing_count(KEY_INPUT_LSHIFT));
    _pad_input[_id_assign[PadInputType::Start]] = max(_pad_input[_id_assign[PadInputType::Start]], Keyboard::get_instance()->get_pressing_count(KEY_INPUT_ESCAPE));
    // subは左CtrlとCで同じ動き
    _pad_input[_id_assign[PadInputType::Sub]] = max(_pad_input[_id_assign[PadInputType::Sub]], Keyboard::get_instance()->get_pressing_count(KEY_INPUT_LCONTROL));
    _pad_input[_id_assign[PadInputType::Sub]] = max(_pad_input[_id_assign[PadInputType::Sub]], Keyboard::get_instance()->get_pressing_count(KEY_INPUT_C));
}

/*!
@brief 渡されたパッドキー番号の入力フレーム数を返す
*/
int PadInput::get(PadInputType id) const
{
    return _pad_input[_id_assign[id]];
}