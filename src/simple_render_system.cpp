#include "simple_render_system.hpp"

SimpleRenderSystem::SimpleRenderSystem()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	CreatePipeline();
}
SimpleRenderSystem::~SimpleRenderSystem() {}

void SimpleRenderSystem::RenderGameObjects(std::vector<GameObject>& gameObjects)
{
	m_corePipeline->Bind();
	for (auto& obj : gameObjects)
	{
		//push uniforms here
		obj.model->Bind();
		obj.model->Draw();
	}
}

void SimpleRenderSystem::CreatePipeline()
{
	m_corePipeline = std::make_unique<core::CorePipeline>(
		RESOURCES_PATH "shaders/default.vert",
		RESOURCES_PATH "shaders/default.frag");
}