#pragma once

//libs
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

namespace core
{
	class CoreCamera
	{
	public:
		CoreCamera(int width, int height, glm::vec3 pos);
		~CoreCamera();

		CoreCamera(const CoreCamera&) = delete;
		CoreCamera& operator=(const CoreCamera&) = delete;

		void SetDimensions(int width, int height);
		void SetPosition(glm::vec3 pos);
		glm::vec3 GetPosition() { return m_position; }
		glm::mat4 GetViewMatrix() { return m_viewMatrix; }
		glm::mat4 GetProjectionMatrix() { return m_projectionMatrix; }

	private:
		glm::vec3 m_position;
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
	};
}