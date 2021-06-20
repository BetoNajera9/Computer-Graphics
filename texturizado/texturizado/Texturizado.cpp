/*
Semestre 2021-2
Práctica Texturizado
Usando librería stb_image.h 
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

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
#include <gtc\random.hpp>
//clases para dar orden y limpieza al còdigo
#include"Mesh.h"
#include"Shader.h"
//#include "Sphere.h"
#include"Window.h"
#include "Camera.h"
#include"Texture.h"

//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
float codo = 0.0f;

Texture T_dado;
Texture T_dado8;
Texture T_ladrillos;
Texture T_asfalto;
Camera camera;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader_t.vert";
static const char* fShader = "shaders/shader_t.frag";
//Sphere sp = Sphere(1, 20, 20);

void CreateObject()
{
	unsigned int indices[] = { 
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.5f,	0.0f,	0.0f,
		0.0f,-0.5f,0.5f,	1.0f,	0.0f,
		0.5f,-0.5f, 0.0f,	1.0f,	1.0f,
		0.0f,0.5f,0.0f,		0.0f,	1.0f
	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}
//ejercicio 1 para hacer en clase, el cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,
		// left
		8, 9, 10,
		10, 11, 8,
		// back
		12, 13, 14,
		14, 15, 12,
		// top
		16, 17, 18,
		18, 19, 16,
		// bottom
		20, 21, 22,
		22, 23, 20

		
	};

GLfloat cubo_vertices[] = {
	// front
	//x		y		z		u		v
	-0.5f, -0.5f,  0.5f,	0.51f,	0.01f,	//0
	 0.5f, -0.5f,  0.5f,	0.74f,	0.01f,	//1
	 0.5f,  0.5f,  0.5f,	0.74f,	0.32f,	//2
	-0.5f,  0.5f,  0.5f,	0.51f,	0.32f,	//3

	//right
	0.5f, -0.5f,   0.5f,	0.76f,	0.34f,	//4
	0.5f, -0.5f,  -0.5f,	0.99f,	0.34f,	//5
	0.5f,  0.5f,  -0.5f,	0.99f,	0.65F,	//6
	0.5f,  0.5f,   0.5f,	0.76F,	0.65F,	//7

	//left
	-0.5f, -0.5f,  -0.5f,	0.51f, 0.34f,	//8
	-0.5f, -0.5f,   0.5f,	0.74f, 0.34f,	//9
	-0.5f,  0.5f,   0.5f,	0.74f, 0.65f,	//10
	-0.5f,  0.5f,  -0.5f,	0.51f, 0.65f,	//11

	//back
	-0.5f, -0.5f, -0.5f,	0.01f,	0.35f,	//12
	 0.5f, -0.5f, -0.5f,	0.24f,	0.35f,	//13
	 0.5f,  0.5f, -0.5f,	0.24f,	0.65f,	//14
	-0.5f,  0.5f, -0.5f,	0.01f,	0.65f,	//15

	//top
	-0.5f,	0.5f,  0.5f,	0.51f,	0.67f,	//16
	 0.5f,  0.5f,  0.5f,	0.74f,	0.67f,	//17
	 0.5f,  0.5f, -0.5f,	0.74f,	0.99f,	//18
	-0.5f,  0.5f, -0.5f,	0.51f,	0.99f,	//19

	//bottom
	-0.5f, -0.5f,  0.5f,	0.26f,	0.34f,	//20
	 0.5f, -0.5f,  0.5f,	0.49f,	0.34f,	//21
	 0.5f, -0.5f, -0.5f,	0.49f,	0.65f,	//22
	-0.5f, -0.5f, -0.5f,	0.26f,	0.65f	//23
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,120, 36);
meshList.push_back(cubo);

}

void CreateCuboEight(){
	unsigned int cubo8_indices[] = {
		//1
		0, 1, 2,
		//2
		3, 4, 5,
		//3
		6, 7, 8,
		//4
		9, 10, 11,
		//5
		12, 13, 14,
		//6
		15, 16, 17,
		//7
		18, 19, 20,
		//8
		21, 22, 23

	};

	GLfloat cubo8_vertices[] = {
		// 1
		//x		 y		  z		  u		  v
		1.0f,   0.0f,	 0.0f,	0.35f,	0.5f,	//0
		1.94f,   0.0f,	 0.0f,	0.63f,	0.5f,	//1
		1.47f,   -0.27f, 0.77f,	0.5f,	0.75f,	//2

		//2
		1.94f,	0.0f,	0.0f,	0.5f,	0.25f,	//3
		1.94f,	0.54f,	0.77f,	0.35f,	0.5f,	//4
		1.47f,	-0.27f,	0.77f,	0.20f,	0.25f,	//5

		//3
		1.94f,	0.54f,	0.77f,	0.35f,	0.5f,	//6
		1.0f,	0.54f,	0.77f,	0.5f,	0.75f,	//7
		1.47f,	-0.27f,	0.77f,	0.22f,	0.74f,	//8

		//4
		1.0f,	0.54f,	0.77f,	0.63f,	0.5f,	//9
		1.0f,	0.0f,	0.0f,	0.35f,	0.5f,	//10
		1.47f,	-0.27f,	0.77f,	0.5f,	0.25f,	//11

		//5
		1.94f,	0.0f,	0.0f,	0.5f,	0.75f,	//12
		1.0f,	0.0f,	0.0f,	0.77f,	0.75f,	//13
		1.47f,	0.82f,	0.0f,	0.63f,	1.0f,	//14

		//6
		1.0f,	0.0f,	0.0f,	0.63f,	0.5f,	//15
		1.0f,	0.54f,	0.77f,	0.5f,	0.25f,	//16
		1.47f,	0.82f,	0.0f,	0.77f,	0.25f,	//17

		//7
		1.0f,	0.54f,	0.77f,	0.5f,	0.75f,	//18
		1.94f,	0.54f,	0.77f,	0.63f,	0.5f,	//19
		1.47f,	0.82f,	0.0f,	0.76f,	0.75f,	//20

		//8
		1.94f,	0.54f,	0.77f,	0.76f,	0.25f,	//21
		1.94f,	0.0f,	0.0f,	0.5f,	0.25f,	//22
		1.47f,	0.82f,	0.0f,	0.63f,	0.0f	//23
	};

	Mesh *cubo8 = new Mesh();
	cubo8->CreateMesh(cubo8_vertices, cubo8_indices, 120, 24);
	meshList.push_back(cubo8);
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
	CreateObject();
	CrearCubo();
	CreateCuboEight();
	CreateShaders();
	camera = Camera(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 3.0f, 0.3f);
	//para crear la textura
	T_ladrillos = Texture("Textures/ladrillos.tga");
	T_ladrillos.LoadTexture();
	T_asfalto = Texture("Textures/dirt.png");
	T_asfalto.LoadTexture();
	// Dato
	T_dado = Texture("Textures/dado.tga");
	T_dado.LoadTexture();

	//Dado 8 caras
	T_dado8 = Texture("Textures/dado_8.tga");
	T_dado8.LoadTexture();

	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime(); // SDL_GetPerformanceCounter();
		deltaTime = now - lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
		lastTime = now;
		//Recibir eventos del usuario
		glfwPollEvents();
		
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		uniformView = shaderList[0].getViewLocation();
		//ejercicio 1:
		glm::mat4 model(1.0); 

		model = glm::translate(model, glm::vec3(1.0f, 0.0f, -2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		T_dado.UseTexture();
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f, 1.0f, -2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T_dado.UseTexture();
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f, 0.75f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T_dado8.UseTexture();
		meshList[2]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}