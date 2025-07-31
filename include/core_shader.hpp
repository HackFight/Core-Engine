#pragma once

//libs
#include <glad/glad.h>

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
	};
}