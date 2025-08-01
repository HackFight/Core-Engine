#pragma once

#include "game_object.hpp"
#include "core_shader.hpp"
#include "core_camera.hpp"

//std
#include <vector>
#include <memory>


class SimpleRenderSystem
{
public:
	SimpleRenderSystem();
	~SimpleRenderSystem();

	SimpleRenderSystem(const SimpleRenderSystem&) = delete;
	SimpleRenderSystem& operator=(const SimpleRenderSystem&) = delete;

	void RenderGameObjects(core::CoreCamera& camera, std::vector<GameObject>& gameObjects);

private:
	void CreatePipeline();
	std::unique_ptr<core::CoreShader> m_coreShader;
};
