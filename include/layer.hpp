#pragma once

//libs
#include <glm/gtc/matrix_transform.hpp>

class Layer
{
public:
	using id_t = unsigned int;

	static Layer createLayer()
	{
		static id_t currentID = 0;
		return Layer{ currentID++ };
	}

	Layer(const Layer&) = delete;
	Layer& operator=(const Layer&) = delete;
	Layer(Layer&&) = default;
	Layer& operator=(Layer&&) = default;

	const id_t getID() { return m_id; }

	GLuint texture;
	glm::vec2 texOffset;
	float depth;
	float posX;

private:
	Layer(id_t objID) : m_id{ objID } {}
	id_t m_id;
};