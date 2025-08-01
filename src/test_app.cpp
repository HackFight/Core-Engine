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
	SimpleRenderSystem simpleRendererSystem{};

	while (!coreWindow.ShouldClose())
	{
		ProcessInput();

		coreCamera.SetDimensions(coreWindow.GetWindowsDimensions().first, coreWindow.GetWindowsDimensions().second);

		coreWindow.StartFrame();
		coreTextureManager.BindTexture(0);
		simpleRendererSystem.RenderGameObjects(coreCamera, gameObjects);
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
}
void TestApp::LoadAssets()
{
	std::vector<core::CoreModel::Vertex> quadVertices
	{
		{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
		{{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
		{{ 0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
		{{-0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
	};
	uint32_t indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	auto coreModel = std::make_shared<core::CoreModel>(quadVertices, indices, 6);
	coreTextureManager.CreateTexture(RESOURCES_PATH "textures/Donut.png");

	auto quad = GameObject::createGameObject();
	quad.model = coreModel;
	quad.color = {1.0f, 1.0f, 0.0f};
	quad.transfrom2D.scale = { 2.0f, 2.0f };

	gameObjects.push_back(std::move(quad));
}