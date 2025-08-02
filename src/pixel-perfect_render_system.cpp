#include "pixel-perfect_render_system.hpp"

PixelPerfectRenderSystem::PixelPerfectRenderSystem(core::CoreTextureManager& textureManager, core::CoreFramebufferManager& framebufferManager, core::CoreCamera& camera, WinInfo& winInfo, int ratio) :
	m_textureManager{textureManager},
	m_framebufferManager{framebufferManager},
	m_camera{camera},
	m_winInfo{winInfo},
	m_ratio{ratio}
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	CreateQuad();
	CreatePipeline();
	m_framebufferInfo = m_framebufferManager.CreateFramebuffer(80, 60);
}
PixelPerfectRenderSystem::~PixelPerfectRenderSystem() {}

void PixelPerfectRenderSystem::RenderGameObjects(std::vector<GameObject>& gameObjects)
{
	int width = m_winInfo.width / m_ratio;
	int height = m_winInfo.height / m_ratio;
	m_framebufferManager.ModifyFramebuffer({ m_framebufferInfo.FBO, m_framebufferInfo.textureID, width, height});
	glViewport(0, 0, width, height);
	m_camera.SetDimensions(width, height);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_defaultShader->Bind();
	for (auto& obj : gameObjects)
	{
		m_defaultShader->set3f("Color", obj.color.r, obj.color.g, obj.color.b);
		m_defaultShader->setmat4("ViewMatrix", m_camera.GetViewMatrix());
		m_defaultShader->setmat4("ModelViewMatrix", m_camera.GetViewMatrix() * obj.transfrom2D.mat4());
		m_defaultShader->setmat4("ProjectionMatrix", m_camera.GetProjectionMatrix());
		m_textureManager.BindTexture(obj.texture);
		obj.model->Bind();
		obj.model->Draw();
	}

	m_framebufferManager.BindFramebuffer(0);
	glViewport(0, 0, m_winInfo.width, m_winInfo.height);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_compositeShader->Bind();
	m_textureManager.BindTexture(m_framebufferInfo.textureID);
	m_quad->Bind();
	m_quad->Draw();
}

void PixelPerfectRenderSystem::CreatePipeline()
{
	m_defaultShader = std::make_unique<core::CoreShader>(RESOURCES_PATH "shaders/default.vert", RESOURCES_PATH "shaders/default.frag");
	m_compositeShader = std::make_unique<core::CoreShader>(RESOURCES_PATH "shaders/default_composite.vert", RESOURCES_PATH "shaders/default_composite.frag");
}
void PixelPerfectRenderSystem::CreateQuad()
{
	std::vector<core::CoreModel::Vertex> quadVertices
	{
		{{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
		{{ 1.0f, -1.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
		{{ 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
		{{-1.0f,  1.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}}
	};
	uint32_t indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	m_quad = std::make_unique<core::CoreModel>(quadVertices, indices, 6);
}