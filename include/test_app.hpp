#pragma once

#include "core/core_window.hpp"
#include "simple_render_system.hpp"
#include "pixel-perfect_render_system.hpp"

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

    WinInfo winInfo = { coreWindow.GetWindowsDimensions().first, coreWindow.GetWindowsDimensions().second };;

private:
    void ProcessInput();
    void LoadAssets();

    core::CoreTextureManager coreTextureManager;
    core::CoreFramebufferManager coreFramebufferManager{coreTextureManager};
    core::CoreWindow coreWindow{ WIDTH, HEIGHT, "OpenGL test app" };
    core::CoreCamera coreCamera{ WIDTH, HEIGHT, glm::vec3{0.0f, 0.0f, -5.0f} };
    std::vector<GameObject> gameObjects;
};