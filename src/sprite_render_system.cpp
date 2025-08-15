#include "sprite_render_system.hpp"

//std
#include <cmath>

SpriteRenderSystem::SpriteRenderSystem(
	core::CoreTextureManager& textureManager,
	core::CoreCamera& camera,
	WinInfo& winInfo) :
	m_textureManager{ textureManager },
	m_camera{ camera },
	m_winInfo{ winInfo }
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	CreatePipeline();
}
SpriteRenderSystem::~SpriteRenderSystem() {}

void SpriteRenderSystem::DrawSprites(std::vector<Sprite>& sprites)
{
	m_spriteShader->Bind();

	for(Sprite& sprite : sprites)
	{
		m_textureManager.BindTexture(sprite.texture);
		m_spriteShader->setmat4("ModelViewMatrix", m_camera.GetViewMatrix() * sprite.transform.mat4());
		m_spriteShader->setmat4("ProjectionMatrix", m_camera.GetProjectionMatrix());
		m_spriteShader->set2f("UVscale", sprite.UVTransform.scale.x, sprite.UVTransform.scale.y);
		m_spriteShader->set2f("UVtranslate", sprite.UVTransform.translation.x, sprite.UVTransform.translation.y);
		sprite.model->Bind();
		sprite.model->Draw();
	}
}

void SpriteRenderSystem::DrawSprite(Sprite& sprite)
{
	m_spriteShader->Bind();

	m_textureManager.BindTexture(sprite.texture);
	m_spriteShader->setmat4("ModelViewMatrix", m_camera.GetViewMatrix() * sprite.transform.mat4());
	m_spriteShader->setmat4("ProjectionMatrix", m_camera.GetProjectionMatrix());
	m_spriteShader->set2f("UVscale", sprite.UVTransform.scale.x, sprite.UVTransform.scale.y);
	m_spriteShader->set2f("UVtranslate", sprite.UVTransform.translation.x, sprite.UVTransform.translation.y);
	sprite.model->Bind();
	sprite.model->Draw();

}

void SpriteRenderSystem::CreatePipeline()
{
	m_spriteShader = std::make_unique<core::CoreShader>(RESOURCES_PATH "shaders/default.vert", RESOURCES_PATH "shaders/sprite.frag");
}