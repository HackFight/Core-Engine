#include "core/core_camera.hpp"

//libs
#include <glm/gtc/matrix_transform.hpp>

namespace core
{
	CoreCamera::CoreCamera(int width, int height, glm::vec3 pos) :
		m_position{ pos }
	{
		m_viewMatrix = glm::translate(glm::mat4(1.0f), m_position);
		m_projectionMatrix = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	}
	CoreCamera::~CoreCamera() {}

	void CoreCamera::SetDimensions(int width, int height)
	{
		m_projectionMatrix = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	}
	void CoreCamera::SetPosition(glm::vec3 pos)
	{
		m_position = pos;
		m_viewMatrix = glm::translate(glm::mat4(1.0f), m_position);
	}
}