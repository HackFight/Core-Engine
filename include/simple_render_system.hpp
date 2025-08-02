#pragma once

#include "utils.hpp"
#include "game_object.hpp"
#include "core/core_shader.hpp"
#include "core/core_camera.hpp"
#include "core/core_texture_manager.hpp"

//std
#include <vector>
#include <memory>


class SimpleRenderSystem
{
public:
	SimpleRenderSystem(core::CoreTextureManager& textureManager, core::CoreCamera& camera, WinInfo& winInfo);
	~SimpleRenderSystem();

	SimpleRenderSystem(const SimpleRenderSystem&) = delete;
	SimpleRenderSystem& operator=(const SimpleRenderSystem&) = delete;

	void RenderGameObjects(std::vector<GameObject>& gameObjects);

private:
	void CreatePipeline();
	std::unique_ptr<core::CoreShader> m_coreShader;
	core::CoreTextureManager& m_textureManager;
	core::CoreCamera& m_camera;
	WinInfo& m_winInfo;
};
