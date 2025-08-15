#include "layers_render_system.hpp"

//std
#include <cmath>

LayersRenderSystem::LayersRenderSystem(
	SpriteRenderSystem& spriteRenderSystem,
	core::CoreTextureManager& textureManager,
	core::CoreFramebufferManager& framebufferManager,
	core::CoreCamera& camera,
	WinInfo& winInfo) :
	m_spriteRenderSystem{ spriteRenderSystem },
	m_textureManager{ textureManager },
	m_framebufferManager{ framebufferManager },
	m_camera{ camera },
	m_winInfo{ winInfo }
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	CreatePipeline();
	LoadAssets();
	m_framebufferInfo = m_framebufferManager.CreateFramebuffer(BUFFER_WIDTH, BUFFER_HEIGHT);
}
LayersRenderSystem::~LayersRenderSystem() {}


void LayersRenderSystem::BindFramebuffer()
{
	//Bind framebuffer
	m_framebufferManager.BindFramebuffer(m_framebufferInfo.FBO);
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_SCISSOR_TEST);
}
void LayersRenderSystem::BindLayer(uint32_t index)
{
	//Find coords
	int x = index % LAYERS_AMOUNT;
	int y = index / LAYERS_AMOUNT;

	//Select viewport zone
	glScissor(0 + VIEWPORT_WIDTH * x, 0 + VIEWPORT_HEIGHT * y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
	glViewport(0 + VIEWPORT_WIDTH * x, 0 + VIEWPORT_HEIGHT * y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
}

void LayersRenderSystem::DrawLayers()
{
	glDisable(GL_SCISSOR_TEST);

	m_framebufferManager.BindFramebuffer(0);
	glViewport(0, 0, BUFFER_WIDTH, BUFFER_HEIGHT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_spriteShader->Bind();
	m_textureManager.BindTexture(m_framebufferInfo.textureID);
	m_layer.texture = m_framebufferInfo.textureID;
	m_textureManager.BindTexture(m_framebufferInfo.textureID);

	for (int j = 0; j < LAYERS_AMOUNT * LAYERS_AMOUNT; j++)
	{
		int x = j % LAYERS_AMOUNT;
		int y = j / LAYERS_AMOUNT;
		m_layer.UVTransform.translation = { x * (1.0f / LAYERS_AMOUNT), y * (1.0f / LAYERS_AMOUNT) };

		m_spriteShader->setmat4("ModelViewMatrix", m_layer.transform.mat4());
		m_spriteShader->setmat4("ProjectionMatrix", glm::mat4{1.0f});
		m_spriteShader->set2f("UVscale", m_layer.UVTransform.scale.x, m_layer.UVTransform.scale.y);
		m_spriteShader->set2f("UVtranslate", m_layer.UVTransform.translation.x, m_layer.UVTransform.translation.y);
		m_layer.model->Bind();
		m_layer.model->Draw();
	}
}

void LayersRenderSystem::CreatePipeline()
{
	m_spriteShader = std::make_unique<core::CoreShader>(RESOURCES_PATH "shaders/default.vert", RESOURCES_PATH "shaders/sprite.frag");
}
void LayersRenderSystem::LoadAssets()
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

	auto quadModel = std::make_shared<core::CoreModel>(quadVertices, indices, 6);

	m_layer.model = quadModel;
	m_layer.transform.scale = { 2.0f, 2.0f, 1.0f };
	m_layer.UVTransform.scale = { 1.0f / LAYERS_AMOUNT, 1.0f / LAYERS_AMOUNT };
}

float LayersRenderSystem::PixelToWorldScale(float sizeInPixels)
{
	return sizeInPixels * m_camera.GetUnitSize().x / VIEWPORT_WIDTH;
}
float LayersRenderSystem::WorldToPixelScale(float worldSize)
{
	return worldSize * VIEWPORT_WIDTH / m_camera.GetUnitSize().x;
}