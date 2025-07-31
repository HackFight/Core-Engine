#pragma once

//libs
#include <glad/glad.h>
#include <glfw/glfw3.h>

//std
#include <string>

namespace core
{
	void FramebufferResizedCallback(GLFWwindow* window, int width, int height);

	class CoreWindow
	{
	public:
		CoreWindow(int w, int h, std::string n);
		~CoreWindow();

		CoreWindow(const CoreWindow&) = delete;
		CoreWindow& operator=(const CoreWindow&) = delete;

		GLFWwindow* GetGLFWWindow() { return m_window; }
		void SetWindowShouldClose() { glfwSetWindowShouldClose(m_window, true); }
		bool ShouldClose() { return glfwWindowShouldClose(m_window); }
		void StartFrame();
		void EndFrame();

	private:
		void InitWindow();
		void InitGLAD();

		int m_width, m_height;
		bool m_frameBufferResized;
		bool m_frameStarted{ false };
		const std::string m_name;
		GLFWwindow* m_window;
	};
}