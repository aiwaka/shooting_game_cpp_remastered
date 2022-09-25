#pragma once

#include <DxLib.h>
#include <string>
#include <vector>
#include <array>
#include "singleton.hpp"

class ImageManager final : public Singleton<ImageManager> {
public:
    ImageManager();
    ~ImageManager() = default;
    void load();
    void release();

    const int get_black() const;
    const int* get_player_a() const;
    std::array<int, 4> get_board() const;
    std::array<int, 7> get_background() const;
    const int* get_enemy(int type) const;
    const int get_boss() const;
    const int get_boss_child() const;

    const int* get_item(int type) const;

    const int* get_numbers() const;
    const int get_mission_display() const;

    const int get_player_shot(int type) const;
    const int get_bomb() const;

    const int get_enemy_bullet(int type, int color) const;

    const int get_destroy_enemy_effect(int color) const;

private:
    /**
     * @brief �摜��ǂݍ���, ���̃f�[�^�ւ̃n���h��������Ԃ�.
     * @return -1: �ǂݍ��ݎ��s. otherwise: �n���h������.
     */
    int app_load_graph(std::string filename);
    /**
     * @brief �摜�𕪊��Ǎ�����buf�Ƀn���h����ۑ�����.
     * @return -1: �ǂݍ��ݎ��s. 0: ����
     */
    int app_load_div_graph(std::string filename, int n, int xn, int yn, int width, int height, int* buf);

    //! @brief �摜�n���h������ׂĊi�[����z��. �ꊇ�J�����\�ɂ���.
    std::vector<int> _images;

    //! @brief ��ʃT�C�Y�̐^�����ȉ摜
    int _black;
    //! @brief �f�W�^�������摜
    int _numbers[10];
    //! @brief �X�e�[�W�ŏ��̕\��
    int _mission_display;

    int _player_a[6];
    int _player_shot[2];

    int _bomb;
    int _board[4];
    //! @brief �|�[�Y��Ԃ̉摜
    int _pause_bg;
    int _background[7];

    int _enemies[4][3];
    int _boss[24];
    int _boss_child;

    int _items[7][2];

    int _destroy_enemy_effect[5];

    //! @brief 6���x6�F�̔z��Ƃ��邪, �����Ă���F������.�i�����̓��߉摜�ƂȂ�̂ŕ\������Ȃ��j
    int _enemy_bullet[6][6];
};
