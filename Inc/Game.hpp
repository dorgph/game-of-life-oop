#pragma once
#include "ViewController.hpp"
#include <chrono>

class Game {
    private:

    using TimePoint = std::chrono::steady_clock::time_point;

    public:
    struct Config {

        size_t GridW

        size_t GridH

        size_t UpdatePeriod
    };
    private:

    std::unique_prt<Model> ModelPtr;

    std::unique_ptr<View> ViewPtr;

    std::unique_ptr<Controller> ControllerPtr;

    Config Conf;

    size_t WSizeX;

    size_t WSizeY;

    private:

    size_t GetCelli(int y) const;

    size_t GetCellj(int x) const;

    TimePoint GetTime() const;

    long GetTimeDiffMs(TimePoint t2, Timepoint t1) const;

    public:

    Game(Config config, std::unique_ptr<IView>&& view,
       std::unique_ptr<IController>&& contr);

    void Run()
};