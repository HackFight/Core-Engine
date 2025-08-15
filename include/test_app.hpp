#pragma once

#include "core/core_window.hpp"
#include "layers_render_system.hpp"
#include "sprite_render_system.hpp"

//std
#include <memory>

class TestApp
{
public:

    static constexpr int WIDTH = 1920, HEIGHT = 1080;

    TestApp();
    ~TestApp();

    TestApp(const TestApp&) = delete;
    TestApp& operator=(const TestApp&) = delete;

    void Run();

    WinInfo winInfo = { coreWindow.GetWindowsDimensions().first, coreWindow.GetWindowsDimensions().second };;

private:
    void ProcessInput(double dt);
    void LoadAssets();

    core::CoreTextureManager coreTextureManager;
    core::CoreFramebufferManager coreFramebufferManager{coreTextureManager};
    core::CoreWindow coreWindow{ WIDTH, HEIGHT, "OpenGL test app" };
    core::CoreCamera coreCamera{ glm::vec2(10.0f, 10.0f * 9.0f/16.0f), glm::vec3{0.0f, 0.0f, -1.0f}};

    std::vector<Sprite> sprites;
};