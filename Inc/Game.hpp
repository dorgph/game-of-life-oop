#pragma once
#include "ViewController.hpp"
#include <chrono>

class Game {
    private:

    using TimePoint = std::chrono::steady_clock::time_point;

    public:
    struct Config {

        size_t GridW;

        size_t GridH;

        size_t CellSizePx;

        size_t UpdatePeriod;
    };
    private:

    std::unique_ptr<Model> ModelPtr;

    std::unique_ptr<View> ViewPtr;

    std::unique_ptr<Controller> ContrPtr;

    Config Conf;

    size_t WSizeX;

    size_t WSizeY;

    private:

    size_t GetCellI(int y) const;

    size_t GetCellJ(int x) const;

    TimePoint GetTime() const;

    long GetTimeDiffMs(TimePoint t2, TimePoint t1) const;

    public:

    Game(Config config, std::unique_ptr<View>&& view,
       std::unique_ptr<Controller>&& contr);

    void Run();
};