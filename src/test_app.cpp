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
	SimpleRenderSystem simpleRendererSystem{
		coreTextureManager,
		coreCamera,
		winInfo};
	PixelPerfectRenderSystem pixelPerfectRenderSystem{
		coreTextureManager,
		coreFramebufferManager,
		coreCamera,
		winInfo,
		20};

	while (!coreWindow.ShouldClose())
	{
		winInfo = { coreWindow.GetWindowsDimensions().first, coreWindow.GetWindowsDimensions().second};
		ProcessInput();

		coreWindow.StartFrame();
		pixelPerfectRenderSystem.RenderGameObjects(gameObjects);
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
		coreCamera.SetPosition(coreCamera.GetPosition() + glm::vec3(0.0001f, 0.0f, 0.0f));
	}
	if (glfwGetKey(coreWindow.GetGLFWWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		coreCamera.SetPosition(coreCamera.GetPosition() - glm::vec3(0.0001f, 0.0f, 0.0f));
	}
}
void TestApp::LoadAssets()
{
	std::vector<core::CoreModel::Vertex> quadVertices
	{
		{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
		{{ 0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
		{{ 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
		{{-0.5f,  0.5f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}}
	};
	uint32_t indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	auto coreModel = std::make_shared<core::CoreModel>(quadVertices, indices, 6);
	coreTextureManager.LoadTexture(RESOURCES_PATH "textures/Donut.png", GL_NEAREST, GL_RGBA);

	auto quad = GameObject::createGameObject();
	quad.model = coreModel;
	quad.color = {1.0f, 1.0f, 0.0f};
	quad.texture = 0;
	quad.transfrom2D.scale = { 2.0f, 2.0f };

	gameObjects.push_back(std::move(quad));
}