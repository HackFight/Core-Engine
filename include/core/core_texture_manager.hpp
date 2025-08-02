#pragma once

//libs
#include <glad/glad.h>

//std
#include <vector>

namespace core
{
	class CoreTextureManager
	{
	public:
		struct TextureInfo
		{
			GLuint ID;
			int width, height;
			GLint param;
			GLenum format;
		};

		CoreTextureManager();
		~CoreTextureManager();

		CoreTextureManager(const CoreTextureManager&) = delete;
		CoreTextureManager& operator=(const CoreTextureManager&) = delete;

		TextureInfo LoadTexture(const char* texPath, GLint param, GLenum format);
		TextureInfo CreateTexture(int width, int height, GLint param, GLenum format);
		TextureInfo CreateTexture(int width, int height, GLint param, GLenum format, const void* data);
		void ModifyTexture(CoreTextureManager::TextureInfo info);
		void BindTexture(GLuint index);

	private:
		std::vector<TextureInfo> m_textures;
	};
}