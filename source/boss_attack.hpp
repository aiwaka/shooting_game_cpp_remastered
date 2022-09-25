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
    void attack_pattern_dummy(Boss* boss);
    //void attack_pattern_00(Boss* boss);
    //void attack_pattern_01(Boss* boss);
    //void attack_pattern_02(Boss* boss);
    //void attack_pattern_04(Boss* boss);
    //void attack_pattern_05(Boss* boss);
    //void attack_pattern_07(Boss* boss);
};

