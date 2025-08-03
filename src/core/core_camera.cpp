#include "core/core_camera.hpp"

//libs
#include <glm/gtc/matrix_transform.hpp>

namespace core
{
	CoreCamera::CoreCamera(glm::vec2 sizeInUnits, glm::vec3 pos) :
		m_sizeInUnits{ sizeInUnits },
		m_position{ pos }
	{
		m_viewMatrix = glm::translate(glm::mat4(1.0f), m_position);
		m_projectionMatrix = glm::ortho(-m_sizeInUnits.x / 2.0f, m_sizeInUnits.x / 2.0f, -m_sizeInUnits.y / 2.0f, m_sizeInUnits.y / 2.0f, 0.0f, 1000.0f);
	}
	CoreCamera::~CoreCamera() {}

	void CoreCamera::SetDimensions(glm::vec2 sizeInUnits)
	{
		m_sizeInUnits = sizeInUnits;
		m_projectionMatrix = glm::ortho(-m_sizeInUnits.x / 2.0f, m_sizeInUnits.x / 2.0f, -m_sizeInUnits.y / 2.0f, m_sizeInUnits.y / 2.0f, 0.0f, 1000.0f);
	}
	void CoreCamera::SetPosition(glm::vec3 pos)
	{
		m_position = pos;
		m_viewMatrix = glm::translate(glm::mat4(1.0f), m_position);
	}
}