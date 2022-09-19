#pragma once

#include <DxLib.h>
#include <string>
#include <vector>
#include "singleton.hpp"

class ImageManager final : public Singleton<ImageManager> {
public:
    ImageManager();
    ~ImageManager() = default;
    void load();
    void release();

    int get_player() const;

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

    std::vector<int> _images;
    int _player;
};
