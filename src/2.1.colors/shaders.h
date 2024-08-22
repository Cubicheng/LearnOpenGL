#pragma once

#include "glad/glad.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	unsigned int programID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void checkShaderCompile(const unsigned int& shader,const char* shader_name);
	void checkProgramLink(const unsigned int& program);

	void use();
	void deleteProgram();

	void setUniformBool(const std::string& name, bool value)const;
	void setUniformInt(const std::string& name, int value)const;
	void setUniformFloat(const std::string& name, float value)const;
	void setUniform4f(const std::string& name, float x, float y, float z, float w)const;
	void setUniformMatrix4fv(const std::string& name, const glm::mat4& trans)const;
	void setUniform3f(const std::string& name, float x, float y, float z)const;
};