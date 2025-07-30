#include "core_window.hpp"

//std
#include <stdexcept>

namespace core
{
	CoreWindow::CoreWindow(int w, int h, std::string n) : width{ w }, height{ h }, name{ n }
	{
		InitWindow();
	}
	CoreWindow::~CoreWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void CoreWindow::StartFrame()
	{
		if (frameStarted) { throw std::runtime_error("Can't start a frame while one is already started!"); }
		frameStarted = true;

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void CoreWindow::EndFrame()
	{
		if (!frameStarted) { throw std::runtime_error("Can't end a frame if none is started!"); }

		glfwSwapBuffers(window);

		frameStarted = false;
	}

	void CoreWindow::InitGLAD()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::runtime_error("Failed to initialize GLAD!");
		}
	}
	void CoreWindow::InitWindow()
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
		if (window == NULL)
		{
			throw std::runtime_error("Failed to create GLFW window!");
		}

		glfwMakeContextCurrent(window);
		InitGLAD();
		glViewport(0, 0, width, height);
		glfwSetFramebufferSizeCallback(window, FramebufferResizedCallback);
	}


	void FramebufferResizedCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}