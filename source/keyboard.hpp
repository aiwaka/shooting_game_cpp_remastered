#pragma once

#include <array>
#include "singleton.hpp"

/**
 * @brief �V���O���g���Ƃ��ăL�[�{�[�h���͂��Ǘ�����N���X. �Ȃ�KeyCode��enum�I�Ɉ����̂Ŗ����K���̗�O�Ƃ��Ă���.
 */
class Keyboard final : public Singleton<Keyboard> {
    //friend Singleton<Keyboard>;

public:
    Keyboard() = default;
    bool update();
    //! @brief KeyCode�̃L�[��������Ă���t���[�������擾.
    int get_pressing_count(int KeyCode);
    int get_releasing_count(int KeyCode);

private:
    // �L�[�̑���
    static const int KEY_NUM = 256;
    std::array<int, KEY_NUM> _pressing_count;
    std::array<int, KEY_NUM> _releasing_count;
    // KeyCode���L���ł��邩
    bool is_available_code(int KeyCode);
};
