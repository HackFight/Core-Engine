#pragma once

#include "core/core_model.hpp"
#include "core/core_texture_manager.hpp"

//libs
#include <glm/gtc/matrix_transform.hpp>

//std
#include <memory>


struct TransformComponent
{
	glm::vec3 position{0.0f, 0.0f, 0.0f};
	glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
	//float rotation;

	glm::mat4 mat4()
	{
		glm::mat4 mat = glm::translate(glm::mat4{ 1.0f }, position);
		//mat = glm::rotate(mat, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		mat = glm::scale(mat, scale);;
		return mat;
	}
};

struct UVTransformComponent
{
	glm::vec2 translation{ 0.0f , 0.0f };
	glm::vec2 scale{ 1.0f, 1.0f };
};

class Sprite
{
public:
	using id_t = unsigned int;

	static Sprite createSprite()
	{
		static id_t currentID = 0;
		return Sprite{ currentID++ };
	}

	Sprite(const Sprite&) = delete;
	Sprite& operator=(const Sprite&) = delete;
	Sprite(Sprite&&) = default;
	Sprite& operator=(Sprite&&) = default;

	const id_t getID() { return m_id; }

	std::shared_ptr<core::CoreModel> model;
	TransformComponent transform{};
	UVTransformComponent UVTransform{};
	uint32_t texture{};

private:
	Sprite(id_t objID) : m_id{ objID } {}

	id_t m_id;
};