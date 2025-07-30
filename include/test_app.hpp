#pragma once

#include "core_window.hpp"

class TestApp
{
public:
    static constexpr int WIDTH = 800, HEIGHT = 600;

    TestApp();
    ~TestApp();

    TestApp(const TestApp&) = delete;
    TestApp& operator=(const TestApp&) = delete;

    void Run();

private:
    core::CoreWindow coreWindow{ WIDTH, HEIGHT, "OpenGL test app" };

    void ProcessInput();
};