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

    int get_player() const;
    std::array<int, 4> get_board() const;
    int get_background() const;

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

    //! @brief 画像ハンドルを並べて格納する配列. 一括開放を可能にする.
    std::vector<int> _images;

    int _player;
    int _board[4];
    int _background;
};
