#pragma once

//libs
#include <glad/glad.h>

//std
#include <vector>
#include <cstdint>

namespace core
{
	class CoreTextureManager
	{
	public:
		CoreTextureManager();
		~CoreTextureManager();

		CoreTextureManager(const CoreTextureManager&) = delete;
		CoreTextureManager& operator=(const CoreTextureManager&) = delete;

		GLuint CreateTexture(const char* texPath);
		void BindTexture(uint32_t index);

	private:
		std::vector<uint32_t> m_textures;
	};
}