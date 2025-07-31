#include "core_model.hpp"

namespace core
{
	CoreModel::CoreModel(const std::vector<Vertex>& vertices, uint32_t indices[], uint32_t indexCount) :
		m_indexCount{ indexCount }
	{
		CreateBuffers(vertices, indices);
	}
	CoreModel::~CoreModel() {}

	void CoreModel::Bind()
	{
		glBindVertexArray(m_VAO);
	}
	void CoreModel::Draw()
	{
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
	}

	void CoreModel::CreateBuffers(const std::vector<Vertex>& vertices, uint32_t indices[])
	{
		m_vertexCount = static_cast<uint32_t>(vertices.size());

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(uint32_t), indices, GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}
}