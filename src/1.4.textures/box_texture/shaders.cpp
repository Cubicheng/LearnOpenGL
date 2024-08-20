#include "shaders.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath){
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;
	//make sure ifstream can throw badbit and failbit abnormality
	vertexShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	fragmentShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	try {

		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);

		std::stringstream vertexShaderStream, fragmentShaderStream;

		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();

	}
	catch (std::ifstream::failure) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkShaderCompile(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkShaderCompile(fragment, "FRAGMENT");

	programID = glCreateProgram();
	glAttachShader(programID, vertex);
	glAttachShader(programID, fragment);
	glLinkProgram(programID);
	checkProgramLink(programID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::checkShaderCompile(const unsigned int& shader, const char* shader_name){
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512 * sizeof(char), NULL, infoLog);
		std::cout << "ERROR::SHADER::" << shader_name << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::checkProgramLink(const unsigned int& program) {
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(program, 512 * sizeof(char), NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::use(){
	glUseProgram(programID);
}

void Shader::deleteProgram(){
	glDeleteProgram(programID);
}

void Shader::setUniformBool(const std::string& name, bool value) const{
	glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}

void Shader::setUniformInt(const std::string& name, int value) const{
	glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}

void Shader::setUniformFloat(const std::string& name, float value) const{
	glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setUniform4f(const std::string& name, float x, float y, float z, float w) const{
	glUniform4f(glGetUniformLocation(programID, name.c_str()), x, y, z, w);
}
