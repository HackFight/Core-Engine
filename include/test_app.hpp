#pragma once

#include "core_window.hpp"
#include "game_object.hpp"
#include "simple_render_system.hpp"

//std
#include <memory>

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
    void ProcessInput();
    void LoadAssets();

    core::CoreWindow coreWindow{ WIDTH, HEIGHT, "OpenGL test app" };
    core::CoreTextureManager coreTextureManager;
    std::vector<GameObject> gameObjects;
};