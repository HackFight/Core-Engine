#include "pixel_layers_render_system.hpp"

//std
#include <cmath>

PixelLayersRenderSystem::PixelLayersRenderSystem(
	core::CoreTextureManager& textureManager,
	core::CoreFramebufferManager& framebufferManager,
	core::CoreCamera& camera,
	WinInfo& winInfo) :
	m_textureManager{ textureManager },
	m_framebufferManager{ framebufferManager },
	m_camera{ camera },
	m_winInfo{ winInfo }
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	CreatePipeline();
	CreateQuad();
	m_framebufferInfo = m_framebufferManager.CreateFramebuffer(BUFFER_WIDTH, BUFFER_HEIGHT);
}
PixelLayersRenderSystem::~PixelLayersRenderSystem() {}

void PixelLayersRenderSystem::RenderLayers(std::vector<Layer>& layers)
{
	//Bind framebuffer
	m_framebufferManager.BindFramebuffer(m_framebufferInfo.FBO);
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_SCISSOR_TEST);

	//Render each layer in buffer
	int i = 0;
	int x = 0;
	int y = 0;
	for (Layer& layer : layers)
	{
		glm::mat4 viewMatrix = m_camera.GetViewMatrix();
		glm::vec3 camPos = m_camera.GetPosition();

		//Parallax
		float offset = layer.depth * camPos.x;
		camPos = camPos + glm::vec3(-offset, 0.0f, 0.0f);
		viewMatrix = glm::translate(viewMatrix, glm::vec3(-offset, 0.0f, 0.0f));

		//Align camera to grid
		float pixelXSize = PixelToWorldScale(1);
		float p = camPos.x / pixelXSize;
		p = std::round(p);
		float newCamX = p * pixelXSize;
		float camAdjustement = newCamX - camPos.x;
		
		cameraAdjustements[i] = WorldToPixelScale(camAdjustement);
		viewMatrix = glm::translate(viewMatrix, glm::vec3(camAdjustement, 0.0f, 0.0f));


		//Select viewport zone
		glScissor(0 + VIEWPORT_WIDTH * x, 0 + VIEWPORT_HEIGHT * y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
		glViewport(0 + VIEWPORT_WIDTH * x, 0 + VIEWPORT_HEIGHT * y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);

		m_opaqueShader->Bind();
		m_opaqueShader->setmat4("ViewMatrix", viewMatrix);
		m_opaqueShader->setmat4("ModelViewMatrix", viewMatrix);
		m_opaqueShader->setmat4("ProjectionMatrix", m_camera.GetProjectionMatrix());
		m_opaqueShader->set2f("TexCoordOffset", layer.texOffset.x, layer.texOffset.y);
		m_textureManager.BindTexture(layer.texture);
		m_layerModel->Bind();
		m_layerModel->Draw();

		i++;
		if (x < LAYERS_WIDTH) { x++; }
		else { x = 0; y++; }
		if (y >= LAYERS_WIDTH) throw std::runtime_error("Not enough space in framebuffer for more layers!");
	}
	glDisable(GL_SCISSOR_TEST);

	m_framebufferManager.BindFramebuffer(0);
	glViewport(0, 0, BUFFER_WIDTH, BUFFER_HEIGHT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_compositeShader->Bind();
	m_textureManager.BindTexture(m_framebufferInfo.textureID);
	x = 0;
	y = 0;
	for (int j = 0; j < layers.size(); j++)
	{
		float horizontalOffset = cameraAdjustements[j] * 2.0f / VIEWPORT_WIDTH;
		m_compositeShader->setFloat("HorizontalOffset", -horizontalOffset);
		m_compositeShader->set2f("TexCoordOffset", x * (1.0f / LAYERS_WIDTH), y * (1.0f / LAYERS_WIDTH));
		m_quad->Bind();
		m_quad->Draw();

		if (x < LAYERS_WIDTH) { x++; }
		else { x = 0; y++; }
		if (y >= LAYERS_WIDTH) throw std::runtime_error("Not enough space in framebuffer for more layers!");
	}
}

void PixelLayersRenderSystem::CreatePipeline()
{
	m_opaqueShader = std::make_unique<core::CoreShader>(RESOURCES_PATH "shaders/textured.vert", RESOURCES_PATH "shaders/textured.frag");
	m_compositeShader = std::make_unique<core::CoreShader>(RESOURCES_PATH "shaders/default_composite.vert", RESOURCES_PATH "shaders/default_composite.frag");
}
void PixelLayersRenderSystem::CreateQuad()
{
	std::vector<core::CoreModel::Vertex> quadVertices
	{
		{{-2.0f - 0.5f / LAYERS_WIDTH, -2.0f - 0.5f / LAYERS_WIDTH, 0.0f}, {0.0f,                0.0f               }, {1.0f, 0.0f, 0.0f}},
		{{ 2.0f + 0.5f / LAYERS_WIDTH, -2.0f - 0.5f / LAYERS_WIDTH, 0.0f}, {1.0f / LAYERS_WIDTH, 0.0f               }, {0.0f, 1.0f, 0.0f}},
		{{ 2.0f + 0.5f / LAYERS_WIDTH,  2.0f + 0.5f / LAYERS_WIDTH, 0.0f}, {1.0f / LAYERS_WIDTH, 1.0f / LAYERS_WIDTH}, {0.0f, 0.0f, 1.0f}},
		{{-2.0f - 0.5f / LAYERS_WIDTH,  2.0f + 0.5f / LAYERS_WIDTH, 0.0f}, {0.0f,                1.0f / LAYERS_WIDTH}, {1.0f, 1.0f, 1.0f}}
	};
	uint32_t indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};
	m_quad = std::make_unique<core::CoreModel>(quadVertices, indices, 6);

	std::vector<core::CoreModel::Vertex> layerVertices
	{
		{{-5.0f, -2.8125f, 0.0f}, {0.0f, 0.0f }, {1.0f, 0.0f, 0.0f}},
		{{ 35.0f, -2.8125f, 0.0f}, {1.0f, 0.0f }, {0.0f, 1.0f, 0.0f}},
		{{ 35.0f,  2.8125f, 0.0f}, {1.0f, 0.25f}, {0.0f, 0.0f, 1.0f}},
		{{-5.0f,  2.8125f, 0.0f}, {0.0f, 0.25f}, {1.0f, 1.0f, 1.0f}}
	};
	m_layerModel = std::make_unique<core::CoreModel>(layerVertices, indices, 6);
}

float PixelLayersRenderSystem::PixelToWorldScale(float sizeInPixels)
{
	return sizeInPixels * m_camera.GetUnitSize().x / VIEWPORT_WIDTH;
}
float PixelLayersRenderSystem::WorldToPixelScale(float worldSize)
{
	return worldSize * VIEWPORT_WIDTH / m_camera.GetUnitSize().x;
}