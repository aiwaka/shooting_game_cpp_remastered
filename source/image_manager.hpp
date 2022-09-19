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
     * @brief 画像を読み込み, そのデータへのハンドル整数を返す.
     * @return -1: 読み込み失敗. otherwise: ハンドル整数.
     */
    int app_load_graph(std::string filename);
    /**
     * @brief 画像を分割読込してbufにハンドルを保存する.
     * @return -1: 読み込み失敗. 0: 成功
     */
    int app_load_div_graph(std::string filename, int n, int xn, int yn, int width, int height, int* buf);

    std::vector<int> _images;
    int _player;
};
