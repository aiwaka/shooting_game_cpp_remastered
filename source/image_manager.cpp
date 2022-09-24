#include "image_manager.hpp"

ImageManager::ImageManager() {
    load();
}

// TODO: �V�[���ŕ����ĉ摜��ǂݍ��߂�悤�ɂ���Ƃ悳����
void ImageManager::load() {
    _board[0] = app_load_graph("./dat/img/10.png");
    _board[1] = app_load_graph("./dat/img/11.png");
    _board[2] = app_load_graph("./dat/img/12.png");
    _board[3] = app_load_graph("./dat/img/20.png");
    _background = app_load_graph("./dat/img/backg_2.png");

    // �|�[�Y�摜��ǂݍ���
    _pause_bg = LoadPauseGraph("./dat/img/pause.png");

    // �f�W�^�������摜
    app_load_div_graph("./dat/img/number_0.png", 10, 10, 1, 30, 55, _numbers);

    // ���@�摜
    app_load_div_graph("./dat/img/player1.png", 6, 2, 3, 70, 60, _player_a);

    // ���@�V���b�g�摜
    _player_shot[0] = app_load_graph("./dat/img/chshot1.png");
    _player_shot[1] = app_load_graph("./dat/img/chshot2.png");

    // �G�摜
    app_load_div_graph("./dat/img/enemy_a.png", 3, 3, 1, 30, 30, _enemy_a);
    app_load_div_graph("./dat/img/enemy_b.png", 3, 3, 1, 30, 40, _enemy_b);

    // �G�e�摜
    app_load_div_graph("dat/img/bullet_0.png", 6, 6, 1, 64, 64, _enemy_bullet[0]);//���e
    app_load_div_graph("dat/img/bullet_1.png", 6, 6, 1, 60, 28, _enemy_bullet[1]);//�ė��e
    app_load_div_graph("dat/img/bullet_2.png", 6, 6, 1, 60, 28, _enemy_bullet[2]);//�ė��e�F���]
    app_load_div_graph("dat/img/bullet_3.png", 6, 6, 1, 25, 20, _enemy_bullet[3]);//�D�e
    app_load_div_graph("dat/img/bullet_4.png", 6, 6, 1, 60, 60, _enemy_bullet[4]);//���e
    app_load_div_graph("dat/img/bullet_5.png", 6, 6, 1, 80, 80, _enemy_bullet[5]);//���e

    // �G���j�G�t�F�N�g
    app_load_div_graph("./dat/img/hit_effect2.png", 5, 5, 1, 140, 140, _destroy_enemy_effect);
}

void ImageManager::release() {
    const size_t size = _images.size();
    for (size_t i = 0; i < size; ++i) {
        DeleteGraph(_images[i]);
    }
    _images.clear();
}

const int* ImageManager::get_player_a() const {
    return _player_a;
}
std::array<int, 4> ImageManager::get_board() const {
    return std::array<int, 4>{_board[0], _board[1], _board[2], _board[3]};
}
int ImageManager::get_background() const {
    return _background;
}
const int* ImageManager::get_enemy_a() const {
    return _enemy_a;
}
const int* ImageManager::get_enemy_b() const {
    return _enemy_b;
}


const int* ImageManager::get_numbers() const {
    return _numbers;
}
const int ImageManager::get_enemy_bullet(int type, int color) const {
    return _enemy_bullet[type][color];
}

const int ImageManager::get_player_shot(int type) const {
    return _player_shot[type];
}
const int ImageManager::get_destroy_enemy_effect(int color) const {
    return _destroy_enemy_effect[color];
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