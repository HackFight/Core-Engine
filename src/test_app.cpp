#include "test_app.hpp"

// std
#include <iostream>

TestApp::TestApp() {}
TestApp::~TestApp() {}

void TestApp::Run()
{
	while (!coreWindow.ShouldClose())
	{
		glfwPollEvents();
		ProcessInput();

		coreWindow.StartFrame();
		coreWindow.EndFrame();
	}
}

void TestApp::ProcessInput()
{
	if (glfwGetKey(coreWindow.GetGLFWWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		coreWindow.SetWindowShouldClose();
	}
}