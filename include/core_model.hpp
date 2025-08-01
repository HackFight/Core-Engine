#pragma once

//libs
#include <glad/glad.h>
#include <glm/glm.hpp>

// std
#include <vector>

namespace core
{
	class CoreModel
	{
	public:
		struct Vertex
		{
			glm::vec3 position;
			glm::vec3 color;
			glm::vec2 texCoord;
		};

		CoreModel(const std::vector<Vertex>& vertices, uint32_t indices[], uint32_t indexCount);
		~CoreModel();

		CoreModel(const CoreModel&) = delete;
		CoreModel& operator=(const CoreModel&) = delete;

		void Bind();
		void Draw();


	private:
		void CreateBuffers(const std::vector<Vertex>& vertices, uint32_t indices[]);

		uint32_t m_VAO;
		uint32_t m_VBO;
		uint32_t m_EBO;
		uint32_t m_vertexCount;
		uint32_t m_indexCount;
	};
}