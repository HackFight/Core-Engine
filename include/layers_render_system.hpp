#pragma once

#include "utils.hpp"
#include "sprite.hpp"
#include "sprite_render_system.hpp"
#include "core/core_model.hpp"
#include "core/core_shader.hpp"
#include "core/core_camera.hpp"
#include "core/core_texture_manager.hpp"
#include "core/core_framebuffer_manager.hpp"

//std
#include <vector>
#include <memory>


class LayersRenderSystem
{
public:
	LayersRenderSystem(
		SpriteRenderSystem& spriteRenderSystem,
		core::CoreTextureManager& textureManager,
		core::CoreFramebufferManager& framebufferManager,
		core::CoreCamera& camera,
		WinInfo& winInfo);
	~LayersRenderSystem();

	LayersRenderSystem(const LayersRenderSystem&) = delete;
	LayersRenderSystem& operator=(const LayersRenderSystem&) = delete;

	void BindFramebuffer();
	void BindLayer(uint32_t index);
	void DrawLayers();

	const int LAYERS_AMOUNT = 4; //The actual number of layers will be the square of this
	const int BUFFER_WIDTH = 1924, BUFFER_HEIGHT = 1084;
	const int VIEWPORT_WIDTH = 481, VIEWPORT_HEIGHT = 271;
	const float CAMERA_DEPTH = -1.0f;

private:
	void CreatePipeline();
	void LoadAssets();

	float PixelToWorldScale(float sizeInPixels);
	float WorldToPixelScale(float worldSize);

	Sprite m_layer = Sprite::createSprite();
	std::unique_ptr<core::CoreShader> m_spriteShader;
	SpriteRenderSystem& m_spriteRenderSystem;
	core::CoreTextureManager& m_textureManager;
	core::CoreFramebufferManager& m_framebufferManager;
	core::CoreCamera& m_camera;
	WinInfo& m_winInfo;

	core::CoreFramebufferManager::FrameInfo m_framebufferInfo;
};
