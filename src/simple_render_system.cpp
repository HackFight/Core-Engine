#include "simple_render_system.hpp"

SimpleRenderSystem::SimpleRenderSystem(core::CoreTextureManager& textureManager, core::CoreCamera& camera, WinInfo& winInfo) :
	m_textureManager{textureManager},
	m_camera{camera},
	m_winInfo{winInfo}
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	CreatePipeline();
}
SimpleRenderSystem::~SimpleRenderSystem() {}

void SimpleRenderSystem::RenderGameObjects(std::vector<GameObject>& gameObjects)
{
	m_camera.SetDimensions(m_winInfo.width, m_winInfo.height);
	m_coreShader->Bind();
	for (auto& obj : gameObjects)
	{
		m_coreShader->set3f("Color", obj.color.r, obj.color.g, obj.color.b);
		m_coreShader->setmat4("ViewMatrix", m_camera.GetViewMatrix());
		m_coreShader->setmat4("ModelViewMatrix", m_camera.GetViewMatrix() * obj.transfrom2D.mat4());
		m_coreShader->setmat4("ProjectionMatrix", m_camera.GetProjectionMatrix());
		m_textureManager.BindTexture(obj.texture);
		obj.model->Bind();
		obj.model->Draw();
	}
}

void SimpleRenderSystem::CreatePipeline() 
{
	m_coreShader = std::make_unique<core::CoreShader>(RESOURCES_PATH "shaders/default.vert", RESOURCES_PATH "shaders/default.frag");
}