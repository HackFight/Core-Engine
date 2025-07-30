#pragma once

namespace renderer
{
	class SimpleRenderSystem
	{
	public:
		SimpleRenderSystem();
		~SimpleRenderSystem();

		SimpleRenderSystem(const SimpleRenderSystem&) = delete;
		SimpleRenderSystem& operator=(const SimpleRenderSystem&) = delete;

		void Render();
	private:
		void CreatePipelineLayout();
		void CreatePipeline();
	};
}