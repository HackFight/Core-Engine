#pragma once

#include "utils.hpp"
#include "core/core_model.hpp"
#include "core/core_shader.hpp"
#include "core/core_camera.hpp"
#include "core/core_texture_manager.hpp"
#include "sprite.hpp"

//std
#include <vector>
#include <memory>


class SpriteRenderSystem
{
public:
	SpriteRenderSystem(
		core::CoreTextureManager& textureManager,
		core::CoreCamera& camera,
		WinInfo& winInfo);
	~SpriteRenderSystem();

	SpriteRenderSystem(const SpriteRenderSystem&) = delete;
	SpriteRenderSystem& operator=(const SpriteRenderSystem&) = delete;

	void DrawSprites(std::vector<Sprite>& sprites);
	void DrawSprite(Sprite& sprite);

private:
	void CreatePipeline();

	float PixelToWorldScale(float sizeInPixels);
	float WorldToPixelScale(float worldSize);

	std::unique_ptr<core::CoreShader> m_spriteShader;
	core::CoreTextureManager& m_textureManager;
	core::CoreCamera& m_camera;
	WinInfo& m_winInfo;
};
