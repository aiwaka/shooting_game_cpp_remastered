#pragma once

#include <list>

class FrameRateManager {
public:
    FrameRateManager();
    //! @brief フレームレート管理のために待機や更新を行う.
    void wait();
    //! @brief fps描画. 更新等の処理は行わないので描画させたくない場合は呼び出さなければいい.
    void draw() const;

private:
    //! @brief 「Windowsが起動してからの経過時間（ms）」を並べて保存する配列
    std::list<int> _list;
    float _fps;
    unsigned int _counter;

    //! @brief 呼び出されると現在の時間を記録し, リストサイズが一定以上になれば古いものを消去する.
    void regist();
    //! @brief 直近の一定時間区間からFPSを計算
    void updateAverage();
    //! @brief FPSを指定されたものにするためにこのフレームで待つべき時間（ms）を計算する
    unsigned int getWaitTime() const;

};
