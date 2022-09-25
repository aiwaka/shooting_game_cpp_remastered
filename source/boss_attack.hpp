#pragma once

#include <vector>
#include <memory>


class Boss;

/**
 * @brief �{�X�G�̍U���������N���X.
 * @brief �U�����e�����łȂ��������ԁE�̗͂�����
 */
class BossAttack {
public:
    BossAttack();
    virtual ~BossAttack() = default;
    void attack(Boss* boss);

    //! @brief �w�肳�ꂽid�̍U���̗̑͂Ɛ������Ԃ�Ԃ�
    std::array<int, 2> get_hp_and_time(int id);

private:
    using AttackFunc = void(BossAttack::*)(Boss* boss);
    //! @brief �p�^�[���ɑ̗́E���Ԃ̏����������邽�߂̍\����. �����̓{�X�N���X�ōU����o�^����Ƃ��ɃR�s�[���邽�߂݂̂Ɏg�p�����.
    //! @brief _pattern�͍U������ɎQ�Ƃ����
    struct AttackPattern {
        int _hp;
        int _time_limit;
        AttackFunc _pattern;
    };
    // �̗͂␧�����Ԃ��ꏏ�ɕێ������z����쐬����.
    std::vector<AttackPattern> _attack_pattern_list;

    //! @brief �z�񖄂ߗp�_�~�[
    void pattern_dummy(Boss* boss);
    void pattern_001(Boss* boss);
    void pattern_002(Boss* boss);
    void pattern_003(Boss* boss);
    void pattern_004(Boss* boss);
    //void pattern_010(Boss* boss);
    //void pattern_011(Boss* boss);
    //void pattern_012(Boss* boss);
    //void pattern_013(Boss* boss);
    //void pattern_014(Boss* boss);
};

/*
memo
bg1: 6, 9, 7, 5, 15
bg2: 12, 9, 11, 5, 10
bg3: 13, 9, 7, 5, 14
6->1, 12->2, 13->3, 9->4, 7->5, dummy 11->7, 5->8, 15->9, 10->10, 14->11, �ƕύX
*/
