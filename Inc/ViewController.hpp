#pragma once
#include <memory>
#include <string>
#include "Model.hpp"

struct View {
    public:

    virtual void Init(size_t width, size_t height, const std::string& wname) = 0;

    virtual void Stop() = 0;

    virtual void DrawField(const Model::FieldT& field) = 0;

    virtual ~View() = default;
};

struct Controller {
    public:

    struct MouseState{

    enum ClickType { None, Left, Right } Click;

    bool ClickUpdated;

    int X;
    int Y;
    };

    virtual MouseState GetMouseState() = 0;

    virtual bool ShutdownPending() = 0;

    virtual ~Controller() = default;
};