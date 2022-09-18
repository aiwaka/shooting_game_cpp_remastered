#pragma once

#include <array>
#include "singleton.hpp"

enum PadInputType {
    Up,
    Down,
    Left,
    Right,
    Shot,
    Bomb,
    Slow,
    Start,
    Sub,
};

class PadInput final : public Singleton<PadInput> {
public:
    PadInput();
    ~PadInput() = default;
    void update();
    //! @brief �p�b�h�̃{�^��ID�ɑ΂�����͂��擾
    int get(PadInputType id) const;

private:
    /**
     * @brief �p�b�h�ƁA����ɑΉ�����L�[�{�[�h�̓��͏�Ԃ��}�[�W����.
     * @brief �L�[�{�[�h���͂Ɖ������Ԃ��ׂđ傫�������̗p���邱�ƂŃp�b�h���͂�z�肵���������L�[�{�[�h�ł�����ł���悤�ɂ���.
     */
    void merge();

    const static int PAD_KEY_NUM = 16;
    //! @brief �ǂ̃{�^�����ǂ̓��͂Ɋ��蓖�Ă��Ă��邩������
    std::array<int, PAD_KEY_NUM> _id_assign;
    //! @brief �p�b�h�̓��͏��
    std::array<int, PAD_KEY_NUM> _pad_input;
};
