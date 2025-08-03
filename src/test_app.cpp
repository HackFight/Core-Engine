#include "test_app.hpp"

// std
#include <iostream>

TestApp::TestApp()
{
	LoadAssets();
}
TestApp::~TestApp() {}

void TestApp::Run()
{
	PixelLayersRenderSystem pixelLayersRenderSystem{
		coreTextureManager,
		coreFramebufferManager,
		coreCamera,
		winInfo};

	while (!coreWindow.ShouldClose())
	{
		winInfo = { coreWindow.GetWindowsDimensions().first, coreWindow.GetWindowsDimensions().second};
		ProcessInput();

		coreWindow.StartFrame();
		pixelLayersRenderSystem.RenderLayers(layers);
		coreWindow.EndFrame();

		glfwPollEvents();
	}
}

void TestApp::ProcessInput()
{
	if (glfwGetKey(coreWindow.GetGLFWWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		coreWindow.SetWindowShouldClose();
	}

	if (glfwGetKey(coreWindow.GetGLFWWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		coreCamera.SetPosition(coreCamera.GetPosition() - glm::vec3(0.0001f, 0.0f, 0.0f));
	}
	if (glfwGetKey(coreWindow.GetGLFWWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		coreCamera.SetPosition(coreCamera.GetPosition() + glm::vec3(0.0001f, 0.0f, 0.0f));
	}
	if (glfwGetKey(coreWindow.GetGLFWWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		coreCamera.SetPosition(coreCamera.GetPosition() - glm::vec3(0.0f, 0.0f, 0.0001f));
	}
	if (glfwGetKey(coreWindow.GetGLFWWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		coreCamera.SetPosition(coreCamera.GetPosition() + glm::vec3(0.0f, 0.0f, 0.0001f));
	}
}
void TestApp::LoadAssets()
{
	auto layerTexInfo = coreTextureManager.LoadTexture(RESOURCES_PATH "textures/Parallax test.png", GL_NEAREST, GL_RGBA);

	for (size_t i = 0; i < 4; i++)
	{
		auto layer = Layer::createLayer();
		layer.texture = layerTexInfo.ID;
		layer.texOffset = glm::vec2(0, 0.75f - i*0.25f);
		layer.depth = 1.0f - (1.0f/3.0f)*i;

		layers.push_back(std::move(layer));
	}
}