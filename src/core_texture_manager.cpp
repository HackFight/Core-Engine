#include "core_texture_manager.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//libs
#include <stdexcept>

namespace core
{
	CoreTextureManager::CoreTextureManager() {}
	CoreTextureManager::~CoreTextureManager() {}

	GLuint CoreTextureManager::CreateTexture(const char* texPath)
	{
		GLuint ID;
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(texPath, &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			throw std::runtime_error("Failed to load texture!");
		}

		stbi_image_free(data);
		m_textures.push_back(ID);
	}
	void CoreTextureManager::BindTexture(uint32_t index)
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, m_textures[index]);
	}
}