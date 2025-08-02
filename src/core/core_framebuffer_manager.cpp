#include "core/core_framebuffer_manager.hpp"

#include "utils.hpp"

//std
#include <stdexcept>

namespace core
{
	CoreFramebufferManager::CoreFramebufferManager(core::CoreTextureManager& textureManager):
		m_textureManager{textureManager}
	{
		m_framebuffers.push_back({0, 0, 0, 0});
	}
	CoreFramebufferManager::~CoreFramebufferManager()
	{
		for (auto frame : m_framebuffers)
		{
			glDeleteTextures(1, &frame.textureID);
			glDeleteFramebuffers(1, &frame.FBO);
		}
	}

	CoreFramebufferManager::FrameInfo CoreFramebufferManager::CreateFramebuffer(int width, int height)
	{
		GLuint FBO;
		glGenFramebuffers(1, &FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);

		GLuint textureID = m_textureManager.CreateTexture(width, height, GL_NEAREST, GL_RGBA).ID;
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			CheckGLErrors();
			throw std::runtime_error("Failed to generate framebuffer!");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		FrameInfo info = { FBO, textureID, width, height };
		m_framebuffers.push_back(info);
		return info;
	}
	void CoreFramebufferManager::ModifyFramebuffer(FrameInfo info)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, info.FBO);
		m_textureManager.ModifyTexture({ info.textureID, info.width, info.height, GL_NEAREST, GL_RGBA });
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, info.textureID, 0);
	}
	void CoreFramebufferManager::BindFramebuffer(GLuint index)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffers[index].FBO);
	}
}