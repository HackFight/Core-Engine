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

		GLFWwindow* GetGLFWWindow() { return window; }
		void SetWindowShouldClose() { glfwSetWindowShouldClose(window, true); }
		bool ShouldClose() { return glfwWindowShouldClose(window); }
		void StartFrame();
		void EndFrame();

	private:
		void InitGLAD();
		void InitWindow();

		int width, height;
		bool frameBufferResized;
		bool frameStarted{ false };
		const std::string name;
		GLFWwindow* window;
	};
}