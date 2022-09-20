#include "image_manager.hpp"

ImageManager::ImageManager() {
    _player = app_load_graph("./dat/img/atari.png");
    _board[0] = app_load_graph("./dat/img/10.png");
    _board[1] = app_load_graph("./dat/img/11.png");
    _board[2] = app_load_graph("./dat/img/12.png");
    _board[3] = app_load_graph("./dat/img/20.png");
    _background = app_load_graph("./dat/img/backg_2.png");
}

// ‚ ‚Æ‚Å‘‚­
void ImageManager::load() {}

void ImageManager::release() {
    const size_t size = _images.size();
    for (size_t i = 0; i < size; ++i) {
        DeleteGraph(_images[i]);
    }
    _images.clear();
}

int ImageManager::get_player() const {
    return _player;
}
std::array<int, 4> ImageManager::get_board() const {
    return std::array<int, 4>{_board[0], _board[1], _board[2], _board[3]};
}
int ImageManager::get_background() const {
    return _background;
}

int ImageManager::app_load_graph(std::string filename) {
    int handle = LoadGraph(filename.c_str());
    _images.push_back(handle);
    return handle;
}

int ImageManager::app_load_div_graph(std::string filename, int n, int xn, int yn, int width, int height, int* buf) {
    int status = LoadDivGraph(filename.c_str(), n, xn, yn, width, height, buf);
    for (int i = 0; i < n; ++i) {
        _images.push_back(buf[i]);
    }
    return status;
}