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
	SpriteRenderSystem spriteRenderSystem{
		coreTextureManager,
		coreCamera,
		winInfo };

	LayersRenderSystem layersRenderSystem{
		spriteRenderSystem,
		coreTextureManager,
		coreFramebufferManager,
		coreCamera,
		winInfo };

	double previous_time = glfwGetTime();
	double current_time = glfwGetTime();
	double deltaTime = 0;

	float cameraAdjustements[64]{ 0 };

	while (!coreWindow.ShouldClose())
	{
		current_time = glfwGetTime();
		deltaTime = current_time - previous_time;
		previous_time = current_time;

		winInfo = { coreWindow.GetWindowsDimensions().first, coreWindow.GetWindowsDimensions().second};
		ProcessInput(deltaTime);


		coreWindow.StartFrame();

		layersRenderSystem.BindFramebuffer();

		int i = 0;
		std::reverse(sprites.begin(), sprites.end());
		for(Sprite& sprite : sprites)
		{
			glm::mat4 viewMatrix = coreCamera.GetViewMatrix();
			glm::vec3 camPos = coreCamera.GetPosition();

			/*
			//Parallax
			float offset = sprite.transform.position.z * camPos.x;
			camPos = camPos + glm::vec3(-offset, 0.0f, 0.0f);
			sprite.transform.position.x -= offset;

			//Align camera to grid
			float pixelYSize = 1 * coreCamera.GetUnitSize().y / layersRenderSystem.VIEWPORT_HEIGHT;
			float p = camPos.x / pixelYSize;
			p = std::round(p);
			float newCamX = p * pixelYSize;
			float camAdjustement = newCamX - camPos.x;

			cameraAdjustements[i] = camAdjustement * layersRenderSystem.VIEWPORT_WIDTH / coreCamera.GetUnitSize().y;
			viewMatrix = glm::translate(viewMatrix, glm::vec3(camAdjustement, 0.0f, 0.0f));
			*/

			layersRenderSystem.BindLayer(i);
			spriteRenderSystem.DrawSprite(sprite);
			i++;
		}
		std::reverse(sprites.begin(), sprites.end());

		layersRenderSystem.DrawLayers();

		coreWindow.EndFrame();


		glfwPollEvents();
	}
}

void TestApp::ProcessInput(double dt)
{
	if (glfwGetKey(coreWindow.GetGLFWWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		coreWindow.SetWindowShouldClose();
	}

	if (glfwGetKey(coreWindow.GetGLFWWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		coreCamera.SetPosition(coreCamera.GetPosition() - glm::vec3(0.5f * dt, 0.0f, 0.0f));
	}
	if (glfwGetKey(coreWindow.GetGLFWWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		coreCamera.SetPosition(coreCamera.GetPosition() + glm::vec3(0.5f * dt, 0.0f, 0.0f));
	}
}
void TestApp::LoadAssets()
{
	auto layerTexInfo = coreTextureManager.LoadTexture(RESOURCES_PATH "textures/Parallax test.png", GL_NEAREST, GL_RGBA);

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

	auto quadModel = std::make_shared<core::CoreModel>(quadVertices, indices, 6);

	for (size_t i = 0; i < 4; i++)
	{
		Sprite sprite = Sprite::createSprite();

		sprite.model = quadModel;
		sprite.transform.scale = { 40.0f, 5.625f, 1.0f };
		sprite.transform.position = { -15.0f , 0.0f, 0.0f + i*0.25f };
		sprite.UVTransform.scale = { 1.0f, 0.25f };
		sprite.UVTransform.translation = { 0.0f, i * 0.25f};
		sprite.texture = layerTexInfo.ID;

		sprites.push_back(std::move(sprite));
	}
}