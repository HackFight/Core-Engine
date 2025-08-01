#include "simple_render_system.hpp"

SimpleRenderSystem::SimpleRenderSystem()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	CreatePipeline();
}
SimpleRenderSystem::~SimpleRenderSystem() {}

void SimpleRenderSystem::RenderGameObjects(core::CoreCamera& camera, std::vector<GameObject>& gameObjects)
{
	m_coreShader->Bind();
	for (auto& obj : gameObjects)
	{
		m_coreShader->set3f("Color", obj.color.r, obj.color.g, obj.color.b);
		m_coreShader->setmat4("ViewMatrix", camera.GetViewMatrix());
		m_coreShader->setmat4("ModelViewMatrix", camera.GetViewMatrix() * obj.transfrom2D.mat4());
		m_coreShader->setmat4("ProjectionMatrix", camera.GetProjectionMatrix());
		obj.model->Bind();
		obj.model->Draw();
	}
}

void SimpleRenderSystem::CreatePipeline() 
{
	m_coreShader = std::make_unique<core::CoreShader>(RESOURCES_PATH "shaders/default.vert", RESOURCES_PATH "shaders/default.frag");
}