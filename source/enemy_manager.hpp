#pragma once

#include <memory>
#include <list>
#include <string>
#include <array>
#include "abstract_enemy.hpp"
#include "task.hpp"

/**
 * @brief 敵の出現や移動・攻撃等の情報を格納する構造体. ファイルから読み込んで作成し, 実体の生成に使う
 */
struct EnemyInfo {
    // _speed, wait_timeは不要と思われるので後で消す
    int spawn_count, move_pattern, enemy_type, start_fire_count, fire_pattern, bullet_id, bullet_color, hp, wait_time;
    float x, y, _speed;
    std::array<int, 6> item;
};

class EnemyManager : public Task {
public:
    EnemyManager();
    virtual ~EnemyManager() = default;
    bool update() override;
    void draw() const override;

private:
    int _counter;
    /**
     * @brief 敵の出現情報をcsvファイルから読み込んで格納する.
     * @brief csvの書式はデータファイル自体を参照のこと.
     */
    void load_enemy_story(std::string filename);
    std::list<std::shared_ptr<AbstractEnemy>> _list;
    std::list<EnemyInfo> _enemy_info_list;

};

