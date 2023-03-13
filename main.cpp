
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "dependente\glew\glew.h"
#include "dependente\glfw\glfw3.h"

#include "dependente\glm\glm.hpp"
#include "dependente\glm\gtc\matrix_transform.hpp"
#include "dependente\glm\gtc\type_ptr.hpp"

#include "shader.hpp"

#include "Camera/camera.h"

GLFWwindow* window;
const int width = 1024, height = 768;
glm::vec3 centerball1(0.0, -0.5, 0.1);
glm::vec3 centerball2(0.0, -0.5, 0.1);
glm::vec3 centerball3(0.0, -0.5, 0.1);
glm::vec3 centerball4(0.0, -0.5, 0.1);
glm::vec3 centerball5(0.0, -0.5, 0.1);
glm::vec3 centerball6(0.0, -0.5, 0.1);

glm::vec3 jack(0.0, 0.0, -0.01);

// lighting
glm::vec3 lightPos(-3.0f, 0.0f, 3.0f);
glm::vec3 lightColor(1.0f);

//Time
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

//Camera
glm::vec3 cameraPos = glm::vec3(0.0f,0.0f, 100.0f);
glm::vec3 cameraDir = glm::vec3(0.0f,0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::normalize(glm::cross(cameraDir, cameraUp));
Camera cam(cameraPos, cameraDir, cameraUp);

void window_callback(GLFWwindow* window, int new_width, int new_height)
{
	glViewport(0, 0, new_width, new_height);
}



void processInput (GLFWwindow* window) {
	float cameraSpeed = 10.0f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		cam.translateFront(deltaTime*10);
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		cam.translateBack(deltaTime * 10);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		cam.translateUp(deltaTime * 10);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		cam.translateDown(deltaTime * 10);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cam.rotateOx(deltaTime * 10);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cam.rotateOx(deltaTime * (-10));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cam.rotateOy(deltaTime * (-10));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cam.rotateOy(deltaTime * (10));
	}
}

int main(void)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	window = glfwCreateWindow(width, height, "Pentaque Game", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, width, height);

	glClearColor(0.3f, 0.6f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	GLuint programIDBall1 = LoadShaders("SimpleVertexShaderball1.vertexshader", "SimpleFragmentShaderball1.fragmentshader");
	GLuint programIDBall2 = LoadShaders("SimpleVertexShaderball2.vertexshader", "SimpleFragmentShaderball2.fragmentshader");
	GLuint programIDBall3 = LoadShaders("SimpleVertexShaderball3.vertexshader", "SimpleFragmentShaderball3.fragmentshader");
	GLuint programIDBall4 = LoadShaders("SimpleVertexShaderball4.vertexshader", "SimpleFragmentShaderball4.fragmentshader");
	GLuint programIDBall5 = LoadShaders("SimpleVertexShaderball5.vertexshader", "SimpleFragmentShaderball5.fragmentshader");
	GLuint programIDBall6 = LoadShaders("SimpleVertexShaderball6.vertexshader", "SimpleFragmentShaderball6.fragmentshader");
	//GLuint programID2 = LoadShaders("LightVertexShader.vertexshader", "LightFragmentShader.fragmentshader");
	GLuint programIDPlan = LoadShaders("SimpleVertexShaderPlan.vertexshader", "SimpleFragmentShaderPlan.fragmentshader");
	GLuint programIDJack = LoadShaders("SimpleVertexShaderJack.vertexshader", "SimpleFragmentShaderJack.fragmentshader");

	//ball1
	float vertices[] = {

		0.1f, -0.5f, 0.2f,  // top right
		0.1f, -0.7f, 0.2f,  // bottom right
		-0.1f, -0.7f, 0.2f,  // bottom left
		-0.1f, -0.5f, 0.2f,   // top left 

		0.1f, -0.5f, 0.0f,  // top right
		0.1f, -0.7f, 0.0f,  // bottom right
		-0.1f, -0.7f, 0.0f,  // bottom left
		-0.1f, -0.5f, 0.0f, //top left
	};

	unsigned int indices[] = {  
		2,1,3,
		1,0,3,
		3,0,7,
		0,4,7,
		6,5,7,
		5,4,7,
		2,1,6,
		1,5,6,
		1,5,0,
		5,4,0,
		2,6,3,
		6,7,3
	};

	//ball2
	float verticesBall2[] = {

		0.1f, -0.5f, 0.2f,  // top right
		0.1f, -0.7f, 0.2f,  // bottom right
		-0.1f, -0.7f, 0.2f,  // bottom left
		-0.1f, -0.5f, 0.2f,   // top left 

		0.1f, -0.5f, 0.0f,  // top right
		0.1f, -0.7f, 0.0f,  // bottom right
		-0.1f, -0.7f, 0.0f,  // bottom left
		-0.1f, -0.5f, 0.0f, //top left
	};

	unsigned int indicesBall2[] = {
		2,1,3,
		1,0,3,
		3,0,7,
		0,4,7,
		6,5,7,
		5,4,7,
		2,1,6,
		1,5,6,
		1,5,0,
		5,4,0,
		2,6,3,
		6,7,3
	};

	//ball3
	float verticesBall3[] = {

		0.1f, -0.5f, 0.2f,  // top right
		0.1f, -0.7f, 0.2f,  // bottom right
		-0.1f, -0.7f, 0.2f,  // bottom left
		-0.1f, -0.5f, 0.2f,   // top left 

		0.1f, -0.5f, 0.0f,  // top right
		0.1f, -0.7f, 0.0f,  // bottom right
		-0.1f, -0.7f, 0.0f,  // bottom left
		-0.1f, -0.5f, 0.0f, //top left
	};

	unsigned int indicesBall3[] = {
		2,1,3,
		1,0,3,
		3,0,7,
		0,4,7,
		6,5,7,
		5,4,7,
		2,1,6,
		1,5,6,
		1,5,0,
		5,4,0,
		2,6,3,
		6,7,3
	};

	//ball4
	float verticesBall4[] = {

		0.1f, -0.5f, 0.2f,  // top right
		0.1f, -0.7f, 0.2f,  // bottom right
		-0.1f, -0.7f, 0.2f,  // bottom left
		-0.1f, -0.5f, 0.2f,   // top left 

		0.1f, -0.5f, 0.0f,  // top right
		0.1f, -0.7f, 0.0f,  // bottom right
		-0.1f, -0.7f, 0.0f,  // bottom left
		-0.1f, -0.5f, 0.0f, //top left
	};

	unsigned int indicesBall4[] = {
		2,1,3,
		1,0,3,
		3,0,7,
		0,4,7,
		6,5,7,
		5,4,7,
		2,1,6,
		1,5,6,
		1,5,0,
		5,4,0,
		2,6,3,
		6,7,3
	};

	//ball5
	float verticesBall5[] = {

		0.1f, -0.5f, 0.2f,  // top right
		0.1f, -0.7f, 0.2f,  // bottom right
		-0.1f, -0.7f, 0.2f,  // bottom left
		-0.1f, -0.5f, 0.2f,   // top left 

		0.1f, -0.5f, 0.0f,  // top right
		0.1f, -0.7f, 0.0f,  // bottom right
		-0.1f, -0.7f, 0.0f,  // bottom left
		-0.1f, -0.5f, 0.0f, //top left
	};

	unsigned int indicesBall5[] = {
		2,1,3,
		1,0,3,
		3,0,7,
		0,4,7,
		6,5,7,
		5,4,7,
		2,1,6,
		1,5,6,
		1,5,0,
		5,4,0,
		2,6,3,
		6,7,3
	};

	//ball6
	float verticesBall6[] = {

		0.1f, -0.5f, 0.2f,  // top right
		0.1f, -0.7f, 0.2f,  // bottom right
		-0.1f, -0.7f, 0.2f,  // bottom left
		-0.1f, -0.5f, 0.2f,   // top left 

		0.1f, -0.5f, 0.0f,  // top right
		0.1f, -0.7f, 0.0f,  // bottom right
		-0.1f, -0.7f, 0.0f,  // bottom left
		-0.1f, -0.5f, 0.0f, //top left
	};

	unsigned int indicesBall6[] = {
		2,1,3,
		1,0,3,
		3,0,7,
		0,4,7,
		6,5,7,
		5,4,7,
		2,1,6,
		1,5,6,
		1,5,0,
		5,4,0,
		2,6,3,
		6,7,3
	};

	//plan
	float verticesPlan[] = {
		-0.9f,-1.0f,0.0f,
		-0.3f,-1.0f,0.0f,
		-0.3f,-0.1f,0.0f,
		0.3f,-1.0f,0.0f,
		0.3f,-0.1f,0.0f,
		0.9f,-1.0f,0.0f,

		-0.9f,-1.0f,0.1f,
		-0.3f,-1.0f,0.1f,
		-0.3f,-0.1f,0.1f,
		0.3f,-1.0f,0.1f,
		0.3f,-0.1f,0.1f,
		0.9f,-1.0f,0.1f

	};

	unsigned int indicesPlan[] = { 
		0,1,2,
		1,3,2,
		3,4,2,
		3,5,4,

		6,7,8,
		7,10,8,
		7,9,10,
		9,11,10,

		5,11,10,
		5,10,4,

		0,6,8,
		0,8,2,

		2,4,10,
		10,8,2,

		0,5,11,
		11,6,0
	};

	float verticesjack[] = {
		-0.02f,-0.20f,0.0f,    //front left
		 0.02f,-0.20f,0.0f,    //front right
		 0.0f, -0.15f,-0.01f,  //varf

		-0.02f,-0.20f,-0.02f,  //back left
		 0.02f,-0.20f,-0.02f   //back right
		//0.0f,-0.15f,0.02f
	};
	
	unsigned int indicesjack[] = {
		0,1,2,
		3,4,2,

		1,4,2,
		3,0,2,

		0,1,3,
		1,4,3
	};

	
	GLuint vbo1, vao1, ibo1,
		vbop, vaop, ibop,
		vboj, vaoj, iboj,
		vbo2, vao2, ibo2,
		vbo3, vao3, ibo3,
		vbo4, vao4, ibo4,
		vbo5, vao5, ibo5,
		vbo6, vao6, ibo6;

	//ball1
	glGenVertexArrays(1, &vao1);
	glGenBuffers(1, &vbo1);
	glGenBuffers(1, &ibo1);

	glBindVertexArray(vao1);

	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//ball2
	glGenVertexArrays(1, &vao2);
	glGenBuffers(1, &vbo2);
	glGenBuffers(1, &ibo2);

	glBindVertexArray(vao2);

	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBall2), verticesBall2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesBall2), indicesBall2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//ball3
	glGenVertexArrays(1, &vao3);
	glGenBuffers(1, &vbo3);
	glGenBuffers(1, &ibo3);

	glBindVertexArray(vao3);

	glBindBuffer(GL_ARRAY_BUFFER, vbo3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBall3), verticesBall3, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesBall3), indicesBall3, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//ball4
	glGenVertexArrays(1, &vao4);
	glGenBuffers(1, &vbo4);
	glGenBuffers(1, &ibo4);

	glBindVertexArray(vao4);

	glBindBuffer(GL_ARRAY_BUFFER, vbo4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBall4), verticesBall4, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesBall4), indicesBall4, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//ball5
	glGenVertexArrays(1, &vao5);
	glGenBuffers(1, &vbo5);
	glGenBuffers(1, &ibo5);

	glBindVertexArray(vao5);

	glBindBuffer(GL_ARRAY_BUFFER, vbo5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBall5), verticesBall5, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo5);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesBall5), indicesBall5, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//ball6
	glGenVertexArrays(1, &vao6);
	glGenBuffers(1, &vbo6);
	glGenBuffers(1, &ibo6);

	glBindVertexArray(vao6);

	glBindBuffer(GL_ARRAY_BUFFER, vbo6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBall6), verticesBall6, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo5);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesBall6), indicesBall6, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	//plan
	glGenVertexArrays(1, &vaop);
	glGenBuffers(1, &vbop);
	glGenBuffers(1, &ibop);

	glBindVertexArray(vaop);

	glBindBuffer(GL_ARRAY_BUFFER, vbop);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPlan), verticesPlan, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibop);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesPlan), indicesPlan, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);	
	glBindVertexArray(0);


	//jack
	glGenVertexArrays(1, &vaoj);
	glGenBuffers(1, &vboj);
	glGenBuffers(1, &iboj);

	glBindVertexArray(vaoj);

	glBindBuffer(GL_ARRAY_BUFFER, vboj);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesjack), verticesjack, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboj);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesjack), indicesjack, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	glfwSetFramebufferSizeCallback(window, window_callback);

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 10000.0f);

	srand(time(0));
	float r = rand() % 400 + 100;
	int round = 1;
	
	float distance[7] = { 0 };
	int scorred = 0, scorblue = 0, team = 0, scor = 0;
	int flag1=0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0, flag6 = 0, flags = 0;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	while (!glfwWindowShouldClose(window))
	{
		
		glm::mat4 view;
		view = glm::lookAt(cam.getCameraPosition(), cam.getCameraViewDirection(), cam.getCameraUp());

		//calculate delta time 
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame; 

		glfwSwapBuffers(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		processInput(window);
		
		glm::mat4 matrix(1.0f);

		//plan
		glBindVertexArray(vaop);
		glUseProgram(programIDPlan);
		glm::mat4 transPlan(1.0);
		matrix = projection * view * transPlan;
		unsigned int transformLocp = glGetUniformLocation(programIDPlan, "transform");
		glUniformMatrix4fv(transformLocp, 1, GL_FALSE, glm::value_ptr(matrix));
		glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_INT, 0);

		
		//jack
		glBindVertexArray(vaoj);
		glUseProgram(programIDJack);
		glm::mat4 transJack(1.0);
		matrix = projection * view * transJack;
		unsigned int transformLocj = glGetUniformLocation(programIDJack, "transform");
		glUniformMatrix4fv(transformLocj, 1, GL_FALSE, glm::value_ptr(matrix));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		

		//ball1
		glUseProgram(programIDBall1);
		glBindVertexArray(vao1);

		glm::mat4 model(1.0f);

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && centerball1.x >= -0.7 && round==1) {
			centerball1.x = centerball1.x - 0.0002;
			
			model = glm::translate(model, glm::vec3(centerball1.x, 0.0, 0.0));
			
			glm::mat4 matrix = projection * view * model;
			unsigned int transformLoc = glGetUniformLocation(programIDBall1, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
			flag1 = 1;
			flags = 1;
		}

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && centerball1.x <= 0.7 && round==1) {
			centerball1.x = centerball1.x + 0.0002;
			
			model = glm::translate(model, glm::vec3(centerball1.x, 0.0, 0.0));
			
			glm::mat4 matrix = projection * view * model;
			unsigned int transformLoc = glGetUniformLocation(programIDBall1, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
			flag1 = 1;
		}

		
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && centerball1.z > -r && round == 1 && flag1 == 1) {/* -100 < > -500*/
			
			centerball1.z = centerball1.z - 0.05;
			
			//model = glm::rotate(model, (float)glfwGetTime() * -20, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::translate(model, glm::vec3(centerball1.x, 0.0f, centerball1.z));
				
			glm::mat4 matrix = projection * view * model;
			unsigned int transformLoc = glGetUniformLocation(programIDBall1, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
				
		}
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		if (centerball1.z <= -r && round==1) {	
			r = rand() % 400 + 100;
			distance[round] = sqrt(pow((jack.x - centerball1.x), 2) + pow((jack.y - centerball1.y), 2) + pow((jack.z - centerball1.z), 2));
			round++;
		}


		//ball2
		glUseProgram(programIDBall2);
		glBindVertexArray(vao2);

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && centerball2.x >= -0.7 && round == 2) {
			centerball2.x = centerball2.x - 0.0002;

			model = glm::translate(model, glm::vec3(centerball2.x, 0.0, 0.0));

			glm::mat4 matrix = projection * view * model;
			unsigned int transformLoc = glGetUniformLocation(programIDBall2, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
			flag2 = 1;
		}

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && centerball2.x <= 0.7 && round == 2) {
			centerball2.x = centerball2.x + 0.0002;

			model = glm::translate(model, glm::vec3(centerball2.x, 0.0, 0.0));

			glm::mat4 matrix = projection * view * model;
			unsigned int transformLoc = glGetUniformLocation(programIDBall2, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
			flag2 = 1;
		}

		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && centerball2.z > -r && round == 2 && flag2==1) {
			centerball2.z = centerball2.z - 0.05;

			//model = glm::rotate(model, (float)glfwGetTime() * -20, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::translate(model, glm::vec3(centerball2.x, 0.0f, centerball2.z));
			

			glm::mat4 matrix = projection * view * model;
			unsigned int transformLoc = glGetUniformLocation(programIDBall2, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
			

		}
		
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		if (centerball2.z <= -r && round == 2) {
			distance[round] = sqrt( pow((jack.x - centerball2.x), 2) + pow((jack.y - centerball2.y), 2) + pow((jack.z - centerball2.z), 2));
			round++;
			r = rand() % 400 + 100;
		}


		//ball3
		glUseProgram(programIDBall3);
		glBindVertexArray(vao3);

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && centerball3.x >= -0.7 && round == 3) {
			centerball3.x = centerball3.x - 0.0002;

			model = glm::translate(model, glm::vec3(centerball3.x, 0.0, 0.0));

			glm::mat4 matrix = projection * view * model;
			unsigned int transformLoc = glGetUniformLocation(programIDBall3, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
			flag3 = 1;
		}

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && centerball3.x <= 0.7 && round == 3) {
			centerball3.x = centerball3.x + 0.0002;

			model = glm::translate(model, glm::vec3(centerball3.x, 0.0, 0.0));

			glm::mat4 matrix = projection * view * model;
			unsigned int transformLoc = glGetUniformLocation(programIDBall3, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
			flag3 = 1;
		}


		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && centerball3.z > -r && round == 3 && flag3==1) {
	
			centerball3.z = centerball3.z - 0.05;

			//model = glm::rotate(model, (float)glfwGetTime() * -20, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::translate(model, glm::vec3(centerball3.x, 0.0f, centerball3.z));
			
			
			glm::mat4 matrix = projection * view * model;
			unsigned int transformLoc = glGetUniformLocation(programIDBall3, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
		

		}

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		if (centerball3.z <= -r && round == 3) {
			distance[round] = sqrt(pow((jack.x - centerball3.x), 2) + pow((jack.y - centerball3.y), 2) + pow((jack.z - centerball3.z), 2));
			round++;
			r = rand() % 400 + 100;
		}


		//ball4
		glUseProgram(programIDBall4);
		glBindVertexArray(vao4);

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && centerball4.x >= -0.7 && round == 4) {
			centerball4.x = centerball4.x - 0.0002;

			model = glm::translate(model, glm::vec3(centerball4.x, 0.0, 0.0));

			glm::mat4 matrix = projection * view * model;
			unsigned int transformLoc = glGetUniformLocation(programIDBall4, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
			flag4 = 1;
		}

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && centerball4.x <= 0.7 && round == 4) {
			centerball4.x = centerball4.x + 0.0002;

			model = glm::translate(model, glm::vec3(centerball4.x, 0.0, 0.0));

			glm::mat4 matrix = projection * view * model;
			unsigned int transformLoc = glGetUniformLocation(programIDBall4, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
			flag4 = 1;
		}


		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && centerball4.z > -r && round == 4 && flag4 == 1) {

			centerball4.z = centerball4.z - 0.05;

			//model = glm::rotate(model, (float)glfwGetTime() * -20, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::translate(model, glm::vec3(centerball4.x, 0.0f, centerball4.z));
		

			glm::mat4 matrix = projection * view * model;
			unsigned int transformLoc = glGetUniformLocation(programIDBall4, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
			
		
		}

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		if (centerball4.z <= -r && round == 4) {
			distance[round] = sqrt(pow((jack.x - centerball4.x), 2) + pow((jack.y - centerball4.y), 2) + pow((jack.z - centerball4.z), 2));
			round++;
			r = rand() % 400 + 100;
		}


		//ball5
		glUseProgram(programIDBall5);
		glBindVertexArray(vao5);

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && centerball5.x >= -0.7 && round == 5) {
			centerball5.x = centerball5.x - 0.0002;

			model = glm::translate(model, glm::vec3(centerball5.x, 0.0, 0.0));

			glm::mat4 matrix = projection * view * model;
			unsigned int transformLoc = glGetUniformLocation(programIDBall5, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
			flag5 = 1;
		}

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && centerball5.x <= 0.7 && round == 5) {
			centerball5.x = centerball5.x + 0.0002;

			model = glm::translate(model, glm::vec3(centerball5.x, 0.0, 0.0));

			glm::mat4 matrix = projection * view * model;
			unsigned int transformLoc = glGetUniformLocation(programIDBall5, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
			flag5 = 1;
		}


		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && centerball5.z > -r && round == 5 && flag5==1) {

			centerball5.z = centerball5.z - 0.05;

			//model = glm::rotate(model, (float)glfwGetTime() * -20, glm::vec3(1.0, 0.0f, 0.0f));
			model = glm::translate(model, glm::vec3(centerball5.x, 0.0f, centerball5.z));


			glm::mat4 matrix = projection * view * model;
			unsigned int transformLoc = glGetUniformLocation(programIDBall5, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
			
			

		}

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		if (centerball5.z <= -r && round == 5) {
			distance[round] = sqrt(pow((jack.x - centerball5.x), 2) + pow((jack.y - centerball5.y), 2) + pow((jack.z - centerball5.z), 2));
			round++;
			r = rand() % 400 + 100;

		}


		//ball6
		glUseProgram(programIDBall6);
		glBindVertexArray(vao6);

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && centerball6.x >= -0.7 && round == 6) {
			centerball6.x = centerball6.x - 0.0002;

			model = glm::translate(model, glm::vec3(centerball6.x, 0.0, 0.0));

			glm::mat4 matrix = projection * view * model;
			unsigned int transformLoc = glGetUniformLocation(programIDBall6, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
			flag6 = 1;
		}

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && centerball6.x <= 0.7 && round == 6) {
			centerball6.x = centerball6.x + 0.0002;

			model = glm::translate(model, glm::vec3(centerball6.x, 0.0, 0.0));

			glm::mat4 matrix = projection * view * model;
			unsigned int transformLoc = glGetUniformLocation(programIDBall6, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
			flag6 = 1;
		}


		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && centerball6.z > -r && round == 6 && flag6==1) {

			centerball6.z = centerball6.z - 0.05;

			//model = glm::rotate(model, (float)glfwGetTime() * -20, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::translate(model, glm::vec3(centerball6.x, 0.0f, centerball6.z));

			glm::mat4 matrix = projection * view * model;
			unsigned int transformLoc = glGetUniformLocation(programIDBall6, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));

		}

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		if (centerball6.z <= -r && round == 6) {
			distance[round] = sqrt(pow((jack.x - centerball6.x), 2) + pow((jack.y - centerball6.y), 2) + pow((jack.z - centerball6.z), 2));
			round++;
			r = rand() % 400 + 100;
		}

		//restart
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && round == 7 && flags==1) {
			//scor
			for (int i = 1; i < 7; i++) {
				if (distance[i] > scor) {
					scor = distance[i];
					team = i;
				}
			}
			if (team % 2 == 0) scorred++;
			else scorblue++;

			std::cout << "Red has " << scorred << " points" << std::endl;
			std::cout << "Blue has " << scorblue << " points" << std::endl;
			
			//restart
			round = 1;
			flag1 = 0;
			flag2 = 0;
			flag3 = 0;
			flag4 = 0;
			flag5 = 0;
			flag6 = 0;
			flags = 0;


			centerball1 = glm::vec3(0.0f,-0.5f,0.1f);
			centerball2 = glm::vec3(0.0f, -0.5f, 0.1f);
			centerball3 = glm::vec3(0.0f, -0.5f, 0.1f);
			centerball4 = glm::vec3(0.0f, -0.5f, 0.1f);
			centerball5 = glm::vec3(0.0f, -0.5f, 0.1f);
			centerball6 = glm::vec3(0.0f, -0.5f, 0.1f);


			//glClear(GL_ACCUM_BUFFER_BIT);
			//glClear(GL_STENCIL_BUFFER_BIT);
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}


	}


	glDeleteBuffers(1, &vbo1);
	glDeleteBuffers(1, &ibo1);
	glDeleteVertexArrays(1, &vao1);
	glDeleteBuffers(1, &vbop);
	glDeleteBuffers(1, &ibop);
	glDeleteVertexArrays(1, &vaop);
	glDeleteBuffers(1, &vboj);
	glDeleteBuffers(1, &iboj);
	glDeleteVertexArrays(1, &vaoj);
	glDeleteBuffers(1, &vbo2);
	glDeleteBuffers(1, &ibo2);
	glDeleteVertexArrays(1, &vao2);
	glDeleteBuffers(1, &vbo3);
	glDeleteBuffers(1, &ibo3);
	glDeleteVertexArrays(1, &vao3);
	glDeleteBuffers(1, &vbo4);
	glDeleteBuffers(1, &ibo4);
	glDeleteVertexArrays(1, &vao4);
	glDeleteBuffers(1, &vbo5);
	glDeleteBuffers(1, &ibo5);
	glDeleteVertexArrays(1, &vao5);
	glDeleteBuffers(1, &vbo6);
	glDeleteBuffers(1, &ibo6);
	glDeleteVertexArrays(1, &vao6);
	glDeleteProgram(programIDBall1);
	glDeleteProgram(programIDPlan);
	glDeleteProgram(programIDJack);
	glDeleteProgram(programIDBall2);
	glDeleteProgram(programIDBall3);
	glDeleteProgram(programIDBall4);
	glDeleteProgram(programIDBall5);
	glDeleteProgram(programIDBall6);

	glfwTerminate();

	return 0;
}