#pragma once

#include "utils.hpp"
#include "game_object.hpp"
#include"core/core_model.hpp"
#include "core/core_shader.hpp"
#include "core/core_camera.hpp"
#include "core/core_texture_manager.hpp"
#include "core/core_framebuffer_manager.hpp"

//std
#include <vector>
#include <memory>


class PixelPerfectRenderSystem
{
public:
	PixelPerfectRenderSystem(
		core::CoreTextureManager& textureManager,
		core::CoreFramebufferManager& frambufferManager,
		core::CoreCamera& camera,
		WinInfo& winInfo,
		int ratio);
	~PixelPerfectRenderSystem();

	PixelPerfectRenderSystem(const PixelPerfectRenderSystem&) = delete;
	PixelPerfectRenderSystem& operator=(const PixelPerfectRenderSystem&) = delete;

	void RenderGameObjects(std::vector<GameObject>& gameObjects);

private:
	void CreatePipeline();
	void CreateQuad();

	std::unique_ptr<core::CoreModel> m_quad;
	std::unique_ptr<core::CoreShader> m_defaultShader;
	std::unique_ptr<core::CoreShader> m_compositeShader;
	core::CoreTextureManager& m_textureManager;
	core::CoreFramebufferManager& m_framebufferManager;
	core::CoreCamera& m_camera;
	WinInfo& m_winInfo;

	core::CoreFramebufferManager::FrameInfo m_framebufferInfo;
	int m_ratio;
};
