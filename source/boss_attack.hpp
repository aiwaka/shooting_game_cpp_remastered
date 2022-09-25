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
    //void pattern_005(Boss* boss);
    void pattern_006(Boss* boss);
    //void pattern_007(Boss* boss);
    //void pattern_008(Boss* boss);
    //void pattern_009(Boss* boss);
    //void pattern_010(Boss* boss);
    //void pattern_011(Boss* boss);
    //void pattern_012(Boss* boss);
    //void pattern_013(Boss* boss);
    //void pattern_014(Boss* boss);
};

