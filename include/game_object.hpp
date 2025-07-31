#pragma once

#include "core_model.hpp"
#include "core_texture_manager.hpp"

//libs
#include <glm/gtc/matrix_transform.hpp>

//std
#include <memory>


struct Transform2DComponent
{
	glm::vec2 translation{};
	glm::vec2 scale{ 1.0f, 1.0f };
	float rotation;

	glm::mat4 mat4()
	{
		glm::mat4 mat = glm::translate(glm::mat4{ 1.0f }, glm::vec3(translation, 0.0f));
		mat = glm::rotate(mat, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		mat = glm::scale(mat, glm::vec3(scale, 1.0f));;
		return mat;
	}
};

class GameObject
{
public:
	using id_t = unsigned int;

	static GameObject createGameObject()
	{
		static id_t currentID = 0;
		return GameObject{ currentID++ };
	}

	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;
	GameObject(GameObject&&) = default;
	GameObject& operator=(GameObject&&) = default;

	const id_t getID() { return m_id; }

	std::shared_ptr<core::CoreModel> model;
	glm::vec3 color{};
	Transform2DComponent transfrom2D{};
	uint32_t texture;

private:
	GameObject(id_t objID) : m_id{ objID } {}

	id_t m_id;
};