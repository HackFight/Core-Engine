#pragma once

#include "core_shader.hpp"

//std
#include <memory>

namespace core
{
	class CorePipeline
	{
	public:
		CorePipeline(const char* vertexPath, const char* fragmentPath);
		~CorePipeline();

		CorePipeline(const CorePipeline&) = delete;
		CorePipeline& operator=(const CorePipeline&) = delete;

		void Bind();

	private:
		std::unique_ptr<core::CoreShader> m_coreShader;
	};
}