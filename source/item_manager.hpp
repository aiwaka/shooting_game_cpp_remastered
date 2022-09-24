#pragma once

#include <memory>
#include <list>
#include <string>
#include <array>
#include "euclid_vec.hpp"
#include "item.hpp"
#include "task.hpp"

class GameScene;

class ItemManager : public Task {
public:
    ItemManager(GameScene* scene);
    virtual ~ItemManager() = default;
    bool update() override;
    void draw() const override;

    Vec2 get_player_pos() const;

    void push_item(Vec2 pos, int type);

private:
    GameScene* _game_scene;
    int _counter;

    std::list<std::shared_ptr<Item>> _list;

    void collision_against_player() const;
};
