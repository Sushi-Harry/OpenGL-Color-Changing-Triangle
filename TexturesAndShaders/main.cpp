#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "headers/Shader.h"

void framebuffer_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Window", NULL, NULL);
	if (window == NULL) { std::cout << "WINDOW CREATION FAILED" << std::endl; glfwTerminate();  return -1; }
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { std::cout << "FAILED TO LOAD GLAD" << std::endl; return -1; }
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_callback);

	//using the shader class we made earlier
	Shader myShader("shaders/vertexShader.vs", "shaders/fragmentShader.fs");

	//vertex data
	float vertices[] = {
		//positions			//color
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//Bind VAO first
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//color attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);



	//mainloop
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.1f, 0.2f, 0.2f, 1.0f);

		//1. use shader program, 2. bind vertex array, 3. draw triangle
		myShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}