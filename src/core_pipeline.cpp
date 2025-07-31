#include "core_pipeline.hpp"

namespace core
{
	CorePipeline::CorePipeline(const char* vertexPath, const char* fragmentPath)
	{
		m_coreShader = std::make_unique<core::CoreShader>(vertexPath, fragmentPath);
	}
	CorePipeline::~CorePipeline() {}

	void CorePipeline::Bind()
	{
		m_coreShader->Bind();
	}
}