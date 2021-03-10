//Práctica 3 semestre 2021-2: índices, mesh. proyecciones, transformaciones
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"

//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";

//Pirámide irregular
void CreatePyramid()
{
	unsigned int indices[] = { 
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.5f,
		0.0f,-0.5f,0.5f,
		0.5f,-0.5f, 0.0f,
		0.0f,0.5f,0.0f,
	};

	Mesh *pyramid = new Mesh();
	pyramid->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(pyramid);
}
//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);

}

//Create Pyramix
void CreatePyramix() {
	unsigned int indexes[] = {
		//Front
		0, 1, 9,
		1, 2, 10,
		2, 3, 11,
		9, 1, 10,
		10, 2, 11,
		9, 10, 15,
		10, 11, 16,
		15, 10, 16,
		15, 16, 18,

		//Rigth
		3, 4, 11,
		4, 5, 12,
		5, 6, 13,
		11, 4, 12,
		12, 5, 13,
		11, 12, 16,
		12, 13, 17,
		16, 12, 17,
		16, 17, 18,

		//Left
		6, 7, 13,
		7, 8, 14,
		8, 0, 9,
		13, 7, 14,
		14, 8, 9,
		13, 14, 17,
		14, 9, 15,
		17, 14, 15,
		17, 15, 18,

		//Down
		0, 1, 8,
		1, 2, 19,
		2, 3, 4,
		8, 1, 19,
		19, 2, 4,
		8, 19, 7,
		19, 4, 5,
		7, 19, 5,
		7, 5, 6

	};

	GLfloat vertices[] = {
		//1st 
		//A
		-0.8f, -0.45f, 0.0f, //0
		//H
		-0.27f,-0.45f, 0.0f, //1
		//I
		0.27f, -0.45f, 0.0f, //2
		//B
		0.8f, -0.45f, 0.0f, //3
		//B1
		0.53f, 0.01f, 0.0f, //4
		//H1
		0.27f, 0.47f, 0.0f, //5
		//J1
		0.0f, 0.094, 0.0f, //6
		//D1
		-0.27f, 0.47f, 0.0f, //7
		//T
		-0.53f, 0.01f, 0.0f,  //8

		//2nd
		//U
		-0.53f,-0.3f, 0.44f,  //9
		//A1
		0.0f, -0.3f, 0.44f,   //10
		//S
		0.53f, -0.3f, 0.44f,  //11
		//N1
		0.27f, 0.17f, 0.44f,  //12
		//P1
		0.0f, 0.63f, 0.44f,  //13
		//L1
		-0.27f, 0.17f, 0.44f, //14

		//3rd
		//M1
		-0.27f, -0.14f,  0.87f,  //15
		//O1
		0.27f, -0.14f, 0.87f,  //16
		//R1
		0.0f, 0.32f, 0.87f,  //17

		//4rd
		//S1
		0.0f, 0.01f, 1.31f,  //18

		//Z
		0.0f, 0.01f, 0.0f  //19

	};

	Mesh *pyramix = new Mesh();
	pyramix->CreateMesh(vertices, indexes, 60, 108);
	meshList.push_back(pyramix);


}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	//CreatePyramid();
	//CrearCubo();

	CreatePyramix();
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	//glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		glm::mat4 model(1.0); 
		//model = glm::mat4(1.0);


		//////////////// ROTACIÓN //////////////////
		//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		////////////////  ESCALA ////////////////

		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		///////////////////// T+R////////////////
		/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		*/
		/////////////R+T//////////
		/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
		*/


		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 2.0f));
		//model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshList[1]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}