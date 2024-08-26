#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include "shaders.h"
#include "camera.h"

#include "stb_image.h"

#include "model.h"

#include "Windows.h"

extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;

int screenWidth = 1900, screenHeight = 1200;

float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,  15.0f, -3.0f),
	glm::vec3(3.0f, 7.0f, 0.0f),
	glm::vec3(0.0f,  15.0f, 3.0f),
	glm::vec3(-3.0f,  7.0f, 0.0f)
};


glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
Camera camera(cameraPos, cameraTarget, upDirection);


glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
glm::vec3 objectColor(1.0f, 0.5f, 0.31f);
glm::vec3 lightDirection(-0.2f, -1.0f, -0.3f);


float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {

	camera.set_speed(2.5f * deltaTime);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.move_front();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.move_back();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.move_left();
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.move_right();
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.move_up();
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.move_down();
}

float lastX, lastY, sensitivity = 0.05f;
bool firstMouse = true;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}


	float deltaX = xpos - lastX;
	float deltaY = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	deltaX *= sensitivity;
	deltaY *= sensitivity;

	camera.change_direction(deltaX, deltaY);
}

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "MyWindow", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create a window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize glad" << std::endl;
		return -1;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);

	//glfwWindowHint(GLFW_SAMPLES, 16);
	//glEnable(GL_MULTISAMPLE);

	//glEnable(GL_CULL_FACE);

	Shader shader("src/3.model/vertex.shader", "src/3.model/fragment.shader");
	Shader lightShader("src/3.model/light_vertex.shader", "src/3.model/light_fragment.shader");

	//Shader modelShader("src/3.model/model_vertex.shader", "src/3.model/model_fragment.shader");
	Model ourModel("resources/objects/nanosuit/nanosuit.obj");


	unsigned int vertexBufferObject;
	unsigned int lightVAO;

	glGenBuffers(1, &vertexBufferObject);
	glGenVertexArrays(1, &lightVAO);

	//bind vertex array first!
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	stbi_set_flip_vertically_on_load(true);

	shader.use();

	glm::mat4 model, view, projection;

	shader.setUniformFloat("shininess", 32.0f);

	for (int i = 0; i < 4; i++) {
		std::string s = "pointLights[";
		std::string id = std::to_string(i);
		s = s + id + "]";
		shader.setUniformVec3(s + ".position", pointLightPositions[i]);
		shader.setUniformVec3(s + ".ambient", 0.1f * lightColor);
		shader.setUniformVec3(s + ".diffuse", 0.5f * lightColor);
		shader.setUniformVec3(s + ".specular", lightColor);
		shader.setUniformFloat(s + ".constant", 1.0f);
		shader.setUniformFloat(s + ".linear", 0.09f);
		shader.setUniformFloat(s + ".quadratic", 0.032f);
	}

	shader.setUniformVec3("spotlight.specular", lightColor);
	shader.setUniformVec3("spotlight.diffuse", 0.5f * lightColor);
	shader.setUniformVec3("spotlight.ambient", 0.1f * lightColor);
	shader.setUniformFloat("spotlight.constant", 1.0f);
	shader.setUniformFloat("spotlight.linear", 0.09f);
	shader.setUniformFloat("spotlight.quadratic", 0.032f);
	shader.setUniformFloat("spotlight.cutOff", cos(glm::radians(12.5f)));
	shader.setUniformFloat("spotlight.outCutOff", cos(glm::radians(17.5f)));


	while (!glfwWindowShouldClose(window)) {
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		processInput(window);


		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		cameraPos = camera.get_camera_pos();
		cameraTarget = cameraPos + camera.get_front_dir();


		//light
		lightShader.use();

		lightShader.setUniformVec3("lightColor", lightColor);

		//view = glm::lookAt(cameraPos, cameraTarget, upDirection);
		view = camera.get_look_at();
		lightShader.setUniformMatrix4fv("view", view);

		projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / screenHeight, 0.1f, 100.0f);
		lightShader.setUniformMatrix4fv("projection", projection);

		for (int i = 0; i < 4; i++) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f));
			lightShader.setUniformMatrix4fv("model", model);
			glBindVertexArray(lightVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		//model
		shader.use();

		shader.setUniformVec3("viewPos", camera.get_camera_pos());

		view = camera.get_look_at();
		shader.setUniformMatrix4fv("view", view);

		projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		shader.setUniformMatrix4fv("projection", projection);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f));
		shader.setUniformMatrix4fv("model", model);

		ourModel.Draw(shader);

		glfwSwapBuffers(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();
	}

	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteVertexArrays(1, &lightVAO);
	shader.deleteProgram();
	lightShader.deleteProgram();

	glfwTerminate();

	return 0;
}