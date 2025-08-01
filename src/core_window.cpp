#include "core_window.hpp"

//std
#include <stdexcept>

namespace core
{
	CoreWindow::CoreWindow(int w, int h, std::string n) : m_width{ w }, m_height{ h }, m_name{ n }
	{
		InitWindow();
	}
	CoreWindow::~CoreWindow()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	void CoreWindow::StartFrame()
	{
		if (m_frameStarted) { throw std::runtime_error("Can't start a frame while one is already started!"); }
		m_frameStarted = true;

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void CoreWindow::EndFrame()
	{
		if (!m_frameStarted) { throw std::runtime_error("Can't end a frame if none is started!"); }

		glfwSwapBuffers(m_window);

		m_frameStarted = false;
	}
	std::pair<int, int> CoreWindow::GetWindowsDimensions()
	{
		int width, height;
		glfwGetWindowSize(m_window, &width, &height);
		return { width, height };
	}

	void CoreWindow::InitWindow()
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		m_window = glfwCreateWindow(m_width, m_height, m_name.c_str(), NULL, NULL);
		if (m_window == NULL)
		{
			throw std::runtime_error("Failed to create GLFW window!");
		}

		glfwMakeContextCurrent(m_window);
		InitGLAD();
		glViewport(0, 0, m_width, m_height);
		glfwSetFramebufferSizeCallback(m_window, FramebufferResizedCallback);
	}
	void CoreWindow::InitGLAD()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::runtime_error("Failed to initialize GLAD!");
		}
	}

	void FramebufferResizedCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}