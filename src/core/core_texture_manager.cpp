#include "core/core_texture_manager.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//libs
#include <stdexcept>

namespace core
{
	CoreTextureManager::CoreTextureManager() {}
	CoreTextureManager::~CoreTextureManager()
	{
		for (auto texture : m_textures)
		{
			glDeleteTextures(1, &texture.ID);
		}
	}

	CoreTextureManager::TextureInfo CoreTextureManager::LoadTexture(const char* texPath, GLint param, GLenum format)
	{
		TextureInfo info;

		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(texPath, &width, &height, &nrChannels, 0);

		if (data)
		{
			info = CreateTexture(width, height, param, format, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			throw std::runtime_error("Failed to load texture!");
		}

		stbi_image_free(data);

		m_textures.push_back(info);
		return info;
	}
	CoreTextureManager::TextureInfo CoreTextureManager::CreateTexture(int width, int height, GLint param, GLenum format)
	{
		GLuint ID;
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);

		TextureInfo info = { ID, width, height, param, format };
		m_textures.push_back(info);
		return info;
	}
	CoreTextureManager::TextureInfo CoreTextureManager::CreateTexture(int width, int height, GLint param, GLenum format, const void* data)
	{
		GLuint ID;
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);

		TextureInfo info = { ID, width, height, param, format };
		m_textures.push_back(info);
		return info;
	}
	void CoreTextureManager::ModifyTexture(CoreTextureManager::TextureInfo info)
	{
		glBindTexture(GL_TEXTURE_2D, info.ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info.width, info.height, 0, info.format, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, info.param);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, info.param);
	}
	void CoreTextureManager::BindTexture(GLuint ID)
	{
		glBindTexture(GL_TEXTURE_2D, ID);
	}
}