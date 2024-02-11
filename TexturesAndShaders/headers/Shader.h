#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

class Shader {
public:
	//program id
	unsigned int shaderID;
	//constructor to read and build shader
	Shader(const char* vertexPath, const char* fragmentPath) {
		// 1.) retrieve the file path for vertex/ fragment code
		std::string vertexCode, fragmentCode;
		std::ifstream vShaderFile, fShaderFile;
		//ensure the ifStream objects can throw exceptions
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			//open the files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			//read file's buffer contents into stream
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//convert stream to string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "Shader File Not Read Successfully" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		// 2.) compile the shaders (Not checking if compilation failed this time)
		unsigned int vertex, fragment;

		//Vertex Shader and fragment shaders compilation
		vertex = glCreateShader(GL_VERTEX_SHADER);
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(vertex);
		glCompileShader(fragment);

		// Shader Program
		shaderID = glCreateProgram();
		glAttachShader(shaderID, vertex);
		glAttachShader(shaderID, fragment);
		glLinkProgram(shaderID);
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	//use the shader
	void use() {
		glUseProgram(shaderID);
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 4) + 0.3f;
		float blueValue = (cos(timeValue) / 3) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderID, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, blueValue, 1.0f);
	}
	//time to make sense of some more complex things
	void setBool(const std::string &name, bool value) {
		glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) {
		glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) {
		glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
	}
};

#endif