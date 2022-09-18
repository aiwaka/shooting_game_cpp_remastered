#include <DxLib.h>
#include "keyboard.hpp"

bool Keyboard::update() {
    char current_key_status[KEY_NUM];
    GetHitKeyStateAll(current_key_status);
    for (int i = 0; i < KEY_NUM; ++i) {
        if (current_key_status[i] != 0) {
            // ‚ ‚éƒL[‚ª‰Ÿ‚³‚ê‚Ä‚¢‚é‚Æ‚«
            if (_releasing_count[i] > 0) _releasing_count[i] = 0;
            ++_pressing_count[i];
        }
        else {
            if (_pressing_count[i] > 0) _pressing_count[i] = 0;
            ++_releasing_count[i];
        }
    }
    return true;
}

int Keyboard::get_pressing_count(int KeyCode) {
    if (!is_available_code(KeyCode))  return -1;
    return _pressing_count[KeyCode];
}
int Keyboard::get_releasing_count(int KeyCode) {
    if (!is_available_code(KeyCode))  return -1;
    return _releasing_count[KeyCode];
}

bool Keyboard::is_available_code(int KeyCode) {
    return (0 <= KeyCode && KeyCode < KEY_NUM);
}
