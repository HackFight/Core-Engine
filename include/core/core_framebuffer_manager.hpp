#pragma once

#include "core_texture_manager.hpp"

//libs
#include <glad/glad.h>

//std
#include <vector>

namespace core
{
	class CoreFramebufferManager
	{
	public:
		struct FrameInfo
		{
			GLuint FBO;
			GLuint textureID;
			int width, height;
		};

		CoreFramebufferManager(core::CoreTextureManager& textureManager);
		~CoreFramebufferManager();

		CoreFramebufferManager(const CoreFramebufferManager&) = delete;
		CoreFramebufferManager& operator=(const CoreFramebufferManager&) = delete;

		FrameInfo CreateFramebuffer(int width, int height);
		void ModifyFramebuffer(FrameInfo info);
		void BindFramebuffer(GLuint index);

	private:

		core::CoreTextureManager& m_textureManager;

		std::vector<FrameInfo> m_framebuffers;
	};
}