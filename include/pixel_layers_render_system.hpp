#pragma once

#include "utils.hpp"
#include "core/core_model.hpp"
#include "core/core_shader.hpp"
#include "core/core_camera.hpp"
#include "core/core_texture_manager.hpp"
#include "core/core_framebuffer_manager.hpp"

#include "layer.hpp"

//std
#include <vector>
#include <memory>


class PixelLayersRenderSystem
{
public:
	PixelLayersRenderSystem(
		core::CoreTextureManager& textureManager,
		core::CoreFramebufferManager& framebufferManager,
		core::CoreCamera& camera,
		WinInfo& winInfo);
	~PixelLayersRenderSystem();

	PixelLayersRenderSystem(const PixelLayersRenderSystem&) = delete;
	PixelLayersRenderSystem& operator=(const PixelLayersRenderSystem&) = delete;

	void RenderLayers(std::vector<Layer>& layers);

private:
	const int BUFFER_WIDTH = 1920, BUFFER_HEIGHT = 1080;
	const int VIEWPORT_WIDTH = 240, VIEWPORT_HEIGHT = 135;
	const float CAMERA_DEPTH = -1.0f;

	void CreatePipeline();
	void CreateQuad();

	float PixelToWorldScale(float sizeInPixels);
	float WorldToPixelScale(float worldSize);

	std::unique_ptr<core::CoreModel> m_quad;
	std::unique_ptr<core::CoreModel> m_layerModel;
	std::unique_ptr<core::CoreShader> m_opaqueShader;
	std::unique_ptr<core::CoreShader> m_compositeShader;
	core::CoreTextureManager& m_textureManager;
	core::CoreFramebufferManager& m_framebufferManager;
	core::CoreCamera& m_camera;
	WinInfo& m_winInfo;

	float cameraAdjustements[64]{ 0 };

	core::CoreFramebufferManager::FrameInfo m_framebufferInfo;
};
