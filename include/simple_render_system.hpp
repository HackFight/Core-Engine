#pragma once

#include "game_object.hpp"
#include "core_pipeline.hpp"

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

	void RenderGameObjects(std::vector<GameObject>& gameObjects);

private:
	void CreatePipeline();

	std::unique_ptr<core::CorePipeline> m_corePipeline;
};
