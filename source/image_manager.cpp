#include "image_manager.hpp"

ImageManager::ImageManager() {
    load();
}

// TODO: ƒV[ƒ“‚Å•ª‚¯‚Ä‰æ‘œ‚ğ“Ç‚İ‚ß‚é‚æ‚¤‚É‚·‚é‚Æ‚æ‚³‚»‚¤
void ImageManager::load() {
    _black = app_load_graph("./dat/img/black.png");
    _board[0] = app_load_graph("./dat/img/10.png");
    _board[1] = app_load_graph("./dat/img/11.png");
    _board[2] = app_load_graph("./dat/img/12.png");
    _board[3] = app_load_graph("./dat/img/20.png");

    // ”wŒi
    _background[0] = app_load_graph("./dat/img/title.png");
    _background[1] = app_load_graph("./dat/img/backg_2.png");
    _background[2] = app_load_graph("./dat/img/backg_6.png");
    _background[3] = app_load_graph("./dat/img/backg_7.png");
    _background[4] = app_load_graph("./dat/img/backg_9.png");
    _background[5] = app_load_graph("./dat/img/backg_5_0.png");
    _background[6] = app_load_graph("./dat/img/backg_5_1.png");

    // ƒ|[ƒY‰æ‘œ‚ğ“Ç‚İ‚İ
    _pause_bg = LoadPauseGraph("./dat/img/pause.png");

    // ƒfƒWƒ^ƒ‹”š‰æ‘œ
    app_load_div_graph("./dat/img/number_0.png", 10, 10, 1, 30, 55, _numbers);

    // ƒXƒe[ƒWÅ‰‚Ì‰æ‘œ
    _mission_display = app_load_graph("./dat/img/stagetitle.png");

    // ©‹@‰æ‘œ
    app_load_div_graph("./dat/img/player1.png", 6, 2, 3, 70, 60, _player_a);

    // ©‹@ƒVƒ‡ƒbƒg‰æ‘œ
    _player_shot[0] = app_load_graph("./dat/img/chshot1.png");
    _player_shot[1] = app_load_graph("./dat/img/chshot2.png");

    _bomb = app_load_graph("./dat/img/bomb0.png");

    // “G‰æ‘œ
    app_load_div_graph("./dat/img/enemy_a.png", 3, 3, 1, 30, 30, _enemies[0]);
    app_load_div_graph("./dat/img/enemy_b.png", 3, 3, 1, 30, 40, _enemies[1]);
    app_load_div_graph("./dat/img/enemy_c.png", 3, 3, 1, 64, 64, _enemies[2]);
    app_load_div_graph("./dat/img/enemy_d.png", 3, 3, 1, 80, 50, _enemies[3]);

    // ƒAƒCƒeƒ€
    app_load_div_graph("./dat/img/p0.png", 2, 2, 1, 35, 35, _items[0]); // hp
    app_load_div_graph("./dat/img/p1.png", 2, 2, 1, 35, 35, _items[1]); // hp_big
    app_load_div_graph("./dat/img/p2.png", 2, 2, 1, 35, 35, _items[2]); // power
    app_load_div_graph("./dat/img/p3.png", 2, 2, 1, 35, 35, _items[3]); // life;
    app_load_div_graph("./dat/img/p4.png", 2, 2, 1, 35, 35, _items[4]); // point
    app_load_div_graph("./dat/img/p5.png", 2, 2, 1, 35, 35, _items[5]); // point_up
    app_load_div_graph("./dat/img/p6.png", 2, 2, 1, 35, 35, _items[6]); // bomb;


    // “G’e‰æ‘œ
    app_load_div_graph("dat/img/bullet_0.png", 6, 6, 1, 64, 64, _enemy_bullet[0]);//Œõ’e
    app_load_div_graph("dat/img/bullet_1.png", 6, 6, 1, 60, 28, _enemy_bullet[1]);//•Ä—±’e
    app_load_div_graph("dat/img/bullet_2.png", 6, 6, 1, 60, 28, _enemy_bullet[2]);//•Ä—±’eF”½“]
    app_load_div_graph("dat/img/bullet_3.png", 6, 6, 1, 25, 20, _enemy_bullet[3]);//D’e
    app_load_div_graph("dat/img/bullet_4.png", 6, 6, 1, 60, 60, _enemy_bullet[4]);//’†’e
    app_load_div_graph("dat/img/bullet_5.png", 6, 6, 1, 80, 80, _enemy_bullet[5]);//¶’e

    // “GŒ‚”jƒGƒtƒFƒNƒg
    app_load_div_graph("./dat/img/hit_effect2.png", 5, 5, 1, 140, 140, _destroy_enemy_effect);
}

void ImageManager::release() {
    const size_t size = _images.size();
    for (size_t i = 0; i < size; ++i) {
        DeleteGraph(_images[i]);
    }
    _images.clear();
}


const int ImageManager::get_black() const {
    return _black;
}
const int* ImageManager::get_player_a() const {
    return _player_a;
}
std::array<int, 4> ImageManager::get_board() const {
    return std::array<int, 4>{_board[0], _board[1], _board[2], _board[3]};
}
std::array<int, 7> ImageManager::get_background() const {
    auto temp = std::array<int, 7>{};
    for (int i = 0; i < 7; ++i) {
        temp[i] = _background[i];
    }
    return temp;
}
const int* ImageManager::get_enemy(int type) const {
    return _enemies[type];
}
const int* ImageManager::get_item(int type) const {
    return _items[type];
}

const int* ImageManager::get_numbers() const {
    return _numbers;
}

const int ImageManager::get_mission_display() const {
    return _mission_display;
}
const int ImageManager::get_enemy_bullet(int type, int color) const {
    return _enemy_bullet[type][color];
}

const int ImageManager::get_player_shot(int type) const {
    return _player_shot[type];
}

const int ImageManager::get_bomb() const {
    return _bomb;
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