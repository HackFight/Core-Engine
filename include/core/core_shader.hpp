#pragma once

//libs
#include <glad/glad.h>
#include <glm/glm.hpp>

//std
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace core
{
	class CoreShader
	{
	public:
		uint32_t ID;

		CoreShader(const char* vertexPath, const char* fragmentPath);
		~CoreShader();

		CoreShader(const CoreShader&) = delete;
		CoreShader& operator=(const CoreShader&) = delete;

		void Bind();

		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
		void set3f(const std::string& name, float v1, float v2, float v3) const;
		void setmat4(const std::string& name, glm::mat4 mat) const;
	};
}