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

    const int* get_player_a() const;
    std::array<int, 4> get_board() const;
    int get_background() const;
    const int* get_enemy_a() const;
    const int* get_enemy_b() const;

    const int get_enemy_bullet(int type, int color) const;


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

    int _player_a[6];
    int _board[4];
    //! @brief �|�[�Y��Ԃ̉摜
    int _pause_bg;
    int _background;
    int _enemy_a[3];
    int _enemy_b[3];

    //! @brief 6���x6�F�̔z��Ƃ��邪, �����Ă���F������.�i�����̓��߉摜�ƂȂ�̂ŕ\������Ȃ��j
    int _enemy_bullet[6][6];
};
