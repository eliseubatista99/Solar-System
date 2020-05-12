// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include "include/camera.h"

GLuint VertexArrayID;
// Create and compile our GLSL program from the shaders
GLuint programID;
// Get a handle for our "MVP" uniform
GLuint MatrixID;
glm::mat4 Projection;
glm::mat4 View;
// Get a handle for our "myTextureSampler" uniform
GLuint TextureID;
Camera camera(glm::vec3(0.0f, 10.0f, 30.0f));
const unsigned int screenWidth = 1200, screenHeight = 1200;

//---SUN------------------------------------------
std::vector<glm::vec3> sunVertices;
std::vector<glm::vec3> mercuryVertices;
std::vector<glm::vec3> venusVertices;
std::vector<glm::vec3> earthVertices;
std::vector<glm::vec3> moonVertices;
std::vector<glm::vec3> marsVertices;
std::vector<glm::vec3> jupiterVertices;
std::vector<glm::vec3> saturnVertices;
std::vector<glm::vec3> uranusVertices;
std::vector<glm::vec3> neptuneVertices;

std::vector<glm::vec2> sunUvs;
std::vector<glm::vec2> mercuryUvs;
std::vector<glm::vec2> venusUvs;
std::vector<glm::vec2> earthUvs;
std::vector<glm::vec2> moonUvs;
std::vector<glm::vec2> marsUvs;
std::vector<glm::vec2> jupiterUvs;
std::vector<glm::vec2> saturnUvs;
std::vector<glm::vec2> uranusUvs;
std::vector<glm::vec2> neptuneUvs;

std::vector<glm::vec3> sunNormals; // Won't be used at the moment.
std::vector<glm::vec3> mercuryNormals; // Won't be used at the moment.
std::vector<glm::vec3> venusNormals; // Won't be used at the moment.
std::vector<glm::vec3> earthNormals; // Won't be used at the moment.
std::vector<glm::vec3> moonNormals; // Won't be used at the moment.
std::vector<glm::vec3> marsNormals; // Won't be used at the moment.
std::vector<glm::vec3> jupiterNormals; // Won't be used at the moment.
std::vector<glm::vec3> saturnNormals; // Won't be used at the moment.
std::vector<glm::vec3> uranusNormals; // Won't be used at the moment.
std::vector<glm::vec3> neptuneNormals; // Won't be used at the moment.


// Load the texture
GLuint sunTexture;
GLuint mercuryTexture;
GLuint venusTexture;
GLuint earthTexture;
GLuint moonTexture;
GLuint marsTexture;
GLuint jupiterTexture;
GLuint saturnTexture;
GLuint uranusTexture;
GLuint neptuneTexture;

GLuint sunVertexbuffer;
GLuint mercuryVertexbuffer;
GLuint venusVertexbuffer;
GLuint earthVertexbuffer;
GLuint moonVertexbuffer;
GLuint marsVertexbuffer;
GLuint jupiterVertexbuffer;
GLuint saturnVertexbuffer;
GLuint uranusVertexbuffer;
GLuint neptuneVertexbuffer;

GLuint sunUvbuffer;
GLuint mercuryUvbuffer;
GLuint venusUvbuffer;
GLuint earthUvbuffer;
GLuint moonUvbuffer;
GLuint marsUvbuffer;
GLuint jupiterUvbuffer;
GLuint saturnUvbuffer;
GLuint uranusUvbuffer;
GLuint neptuneUvbuffer;


glm::mat4 sunModelMatrix;
glm::mat4 mercuryModelMatrix;
glm::mat4 venusModelMatrix;
glm::mat4 earthModelMatrix;
glm::mat4 moonModelMatrix;
glm::mat4 marsModelMatrix;
glm::mat4 jupiterModelMatrix;
glm::mat4 saturnModelMatrix;
glm::mat4 uranusModelMatrix;
glm::mat4 neptuneModelMatrix;


glm::mat4 sunMVP;
glm::mat4 mercuryMVP;
glm::mat4 venusMVP;
glm::mat4 earthMVP;
glm::mat4 moonMVP;
glm::mat4 marsMVP;
glm::mat4 jupiterMVP;
glm::mat4 saturnMVP;
glm::mat4 uranusMVP;
glm::mat4 neptuneMVP;

//----------------------------------------
float planetLocations[9][3] = {
	{3.0f,0.0f,0.0f}, //MERCURY
	{6.0f,0.0f,0.0f}, //VENUS
	{9.0f,0.0f,0.0f}, //EARTH
	{9.0f,0.0f,0.0f}, //MOON
	{12.0f,0.0f,0.0f}, //MARS
	{15.0f,0.0f,0.0f}, //JUPITER
	{18.0f,0.0f,0.0f}, //SATURN
	{21.0f,0.0f,0.0f}, //URANUS
	{24.0f,0.0f,0.0f}, //NEPTUNE

};

float planetDistance[9] = { 3.0f, 6.0f, 9.0f, 2.0f, 12.0f, 15.0f, 18.0f, 21.0f, 24.0f };

float planetTranslationSpeed[9] = { 0.005f, 0.005f,  0.000f,  0.005f,  0.005f,  0.005f,  0.005f,  0.005f,  0.005f};

float planetRotationSpeed[9] = { 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f };

float planetRotationValue[9] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

float planetAngles[9] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

void loadTextures() {
	// Load the texture
	sunTexture = loadDDS("resources/textures/sun_texture.dds");
	mercuryTexture = loadDDS("resources/textures/mercury_texture.dds");
	venusTexture = loadDDS("resources/textures/venus_texture.dds");
	earthTexture = loadDDS("resources/textures/earth_texture.dds");
	moonTexture = loadDDS("resources/textures/moon_texture.dds");
	marsTexture = loadDDS("resources/textures/mars_texture.dds");
	jupiterTexture = loadDDS("resources/textures/jupiter_texture.dds");
	saturnTexture = loadDDS("resources/textures/saturn_texture.dds");
	uranusTexture = loadDDS("resources/textures/uranus_texture.dds");
	neptuneTexture = loadDDS("resources/textures/neptune_texture.dds");
}

void loadObjects() {
	if (!loadOBJ("resources/models/no_rings_planet.obj", sunVertices, sunUvs, sunNormals)) {
		printf("Sun not found\n");
	}
	if (!loadOBJ("resources/models/no_rings_planet.obj", mercuryVertices, mercuryUvs, mercuryNormals)) {
		printf("Mercury not found\n");
	}
	if (!loadOBJ("resources/models/no_rings_planet.obj", venusVertices, venusUvs, venusNormals)) {
		printf("Venus not found\n");
	}
	if (!loadOBJ("resources/models/no_rings_planet.obj", earthVertices, earthUvs, earthNormals)) {
		printf("Venus not found\n");
	}
	if (!loadOBJ("resources/models/no_rings_planet.obj", moonVertices, moonUvs, moonNormals)) {
		printf("Venus not found\n");
	}
	if (!loadOBJ("resources/models/no_rings_planet.obj", marsVertices, marsUvs, marsNormals)) {
		printf("Venus not found\n");
	}
	if (!loadOBJ("resources/models/no_rings_planet.obj", jupiterVertices, jupiterUvs, jupiterNormals)) {
		printf("Venus not found\n");
	}
	if (!loadOBJ("resources/models/saturn.obj", saturnVertices, saturnUvs, saturnNormals)) {
		printf("Venus not found\n");
	}
	if (!loadOBJ("resources/models/no_rings_planet.obj", uranusVertices, uranusUvs, uranusNormals)) {
		printf("Venus not found\n");
	}
	if (!loadOBJ("resources/models/no_rings_planet.obj", neptuneVertices, neptuneUvs, neptuneNormals)) {
		printf("Venus not found\n");
	}
}

void loadAllVBOs() {
	// Load it into a VBO
	glGenBuffers(1, &sunVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, sunVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sunVertices.size() * sizeof(glm::vec3), &sunVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &sunUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, sunUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sunUvs.size() * sizeof(glm::vec2), &sunUvs[0], GL_STATIC_DRAW);
	// Load it into a VBO
	glGenBuffers(1, &mercuryVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mercuryVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, mercuryVertices.size() * sizeof(glm::vec3), &mercuryVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &mercuryUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mercuryUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, mercuryUvs.size() * sizeof(glm::vec2), &mercuryUvs[0], GL_STATIC_DRAW);
	// Load it into a VBO
	glGenBuffers(1, &venusVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, venusVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, venusVertices.size() * sizeof(glm::vec3), &venusVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &venusUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, venusUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, venusUvs.size() * sizeof(glm::vec2), &venusUvs[0], GL_STATIC_DRAW);
	// Load it into a VBO
	glGenBuffers(1, &earthVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, earthVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, earthVertices.size() * sizeof(glm::vec3), &earthVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &earthUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, earthUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, earthUvs.size() * sizeof(glm::vec2), &earthUvs[0], GL_STATIC_DRAW);
	// Load it into a VBO
	glGenBuffers(1, &moonVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, moonVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, moonVertices.size() * sizeof(glm::vec3), &moonVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &moonUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, moonUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, moonUvs.size() * sizeof(glm::vec2), &moonUvs[0], GL_STATIC_DRAW);
	// Load it into a VBO
	glGenBuffers(1, &marsVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, marsVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, marsVertices.size() * sizeof(glm::vec3), &marsVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &marsUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, marsUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, marsUvs.size() * sizeof(glm::vec2), &marsUvs[0], GL_STATIC_DRAW);
	// Load it into a VBO
	glGenBuffers(1, &jupiterVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, jupiterVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, jupiterVertices.size() * sizeof(glm::vec3), &jupiterVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &jupiterUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, jupiterUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, jupiterUvs.size() * sizeof(glm::vec2), &jupiterUvs[0], GL_STATIC_DRAW);
	// Load it into a VBO
	glGenBuffers(1, &saturnVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, saturnVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, saturnVertices.size() * sizeof(glm::vec3), &saturnVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &saturnUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, saturnUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, saturnUvs.size() * sizeof(glm::vec2), &saturnUvs[0], GL_STATIC_DRAW);
	// Load it into a VBO
	glGenBuffers(1, &uranusVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uranusVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, uranusVertices.size() * sizeof(glm::vec3), &uranusVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uranusUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uranusUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uranusUvs.size() * sizeof(glm::vec2), &uranusUvs[0], GL_STATIC_DRAW);
	// Load it into a VBO
	glGenBuffers(1, &neptuneVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, neptuneVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, neptuneVertices.size() * sizeof(glm::vec3), &neptuneVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &neptuneUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, neptuneUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, neptuneUvs.size() * sizeof(glm::vec2), &neptuneUvs[0], GL_STATIC_DRAW);

}

void calcNewLocations() {
	for (int i = 0; i < 9; i++) {
		planetAngles[i] += planetTranslationSpeed[i];
		planetRotationValue[i] += planetRotationSpeed[i];
		if (planetRotationValue[i] >= 360.0f) {
			planetRotationValue[i] = -360.0f;
		}
		if (i == 3) {
			planetLocations[i][0] = planetLocations[2][0] + (planetDistance[i] * sin(planetAngles[i]));
			planetLocations[i][1] = planetLocations[2][1] + (planetDistance[i] * cos(planetAngles[i]));
			planetLocations[i][2] = planetLocations[2][2] + (planetDistance[i] * cos(planetAngles[i]));
		}
		else {
			planetLocations[i][0] = planetDistance[i] * cos(planetAngles[i]);
			planetLocations[i][2] = planetDistance[i] * sin(planetAngles[i]);
		}
		
	}
}

void setUpMVPS() {
	sunModelMatrix = glm::mat4(1.0);
	sunMVP = Projection * View * sunModelMatrix;

	mercuryModelMatrix = glm::mat4(1.0);
	mercuryModelMatrix = glm::translate(mercuryModelMatrix, glm::vec3(planetLocations[0][0], planetLocations[0][1], planetLocations[0][2]));
	mercuryModelMatrix = glm::rotate(mercuryModelMatrix, glm::radians(planetRotationValue[0]), glm::vec3(1, 1, 0));
	mercuryMVP = Projection * View * mercuryModelMatrix;

	venusModelMatrix = glm::mat4(1.0);
	venusModelMatrix = glm::translate(venusModelMatrix, glm::vec3(planetLocations[1][0], planetLocations[1][1], planetLocations[1][2]));
	venusModelMatrix = glm::rotate(venusModelMatrix, glm::radians(planetRotationValue[1]), glm::vec3(1, 1, 0));
	venusMVP = Projection * View * venusModelMatrix;

	earthModelMatrix = glm::mat4(1.0);
	earthModelMatrix = glm::translate(earthModelMatrix, glm::vec3(planetLocations[2][0], planetLocations[2][1], planetLocations[2][2]));
	earthModelMatrix = glm::rotate(earthModelMatrix, glm::radians(planetRotationValue[2]), glm::vec3(1, 1, 0));
	earthMVP = Projection * View * earthModelMatrix;

	moonModelMatrix = glm::mat4(1.0);
	moonModelMatrix = glm::translate(moonModelMatrix, glm::vec3(planetLocations[3][0], planetLocations[3][1], planetLocations[3][2]));
	moonModelMatrix = glm::scale(moonModelMatrix, glm::vec3(0.3f));
	moonModelMatrix = glm::rotate(moonModelMatrix, glm::radians(planetRotationValue[3]), glm::vec3(1, 1, 0));
	moonMVP = Projection * View * moonModelMatrix;

	marsModelMatrix = glm::mat4(1.0);
	marsModelMatrix = glm::translate(marsModelMatrix, glm::vec3(planetLocations[4][0], planetLocations[4][1], planetLocations[4][2]));
	marsModelMatrix = glm::rotate(marsModelMatrix, glm::radians(planetRotationValue[4]), glm::vec3(1, 1, 0));
	marsMVP = Projection * View * marsModelMatrix;

	jupiterModelMatrix = glm::mat4(1.0);
	jupiterModelMatrix = glm::translate(jupiterModelMatrix, glm::vec3(planetLocations[5][0], planetLocations[5][1], planetLocations[5][2]));
	jupiterModelMatrix = glm::rotate(jupiterModelMatrix, glm::radians(planetRotationValue[5]), glm::vec3(1, 1, 0));
	jupiterMVP = Projection * View * jupiterModelMatrix;

	saturnModelMatrix = glm::mat4(1.0);
	saturnModelMatrix = glm::translate(saturnModelMatrix, glm::vec3(planetLocations[6][0], planetLocations[6][1], planetLocations[6][2]));
	saturnModelMatrix = glm::rotate(saturnModelMatrix, glm::radians(planetRotationValue[6]), glm::vec3(1, 1, 0));
	saturnMVP = Projection * View * saturnModelMatrix;

	uranusModelMatrix = glm::mat4(1.0);
	uranusModelMatrix = glm::translate(uranusModelMatrix, glm::vec3(planetLocations[7][0], planetLocations[7][1], planetLocations[7][2]));
	uranusModelMatrix = glm::rotate(uranusModelMatrix, glm::radians(planetRotationValue[7]), glm::vec3(1, 1, 0));
	uranusMVP = Projection * View * uranusModelMatrix;

	neptuneModelMatrix = glm::mat4(1.0);
	neptuneModelMatrix = glm::translate(neptuneModelMatrix, glm::vec3(planetLocations[8][0], planetLocations[8][1], planetLocations[8][2]));
	neptuneModelMatrix = glm::rotate(neptuneModelMatrix, glm::radians(planetRotationValue[8]), glm::vec3(1, 1, 0));
	neptuneMVP = Projection * View * neptuneModelMatrix;
	
}

void drawSpheres() {
	// Use our shader
	glUseProgram(programID);

	// Compute the MVP matrix from keyboard and mouse input
	computeMatricesFromInputs();
	//Projection = getProjectionMatrix();
	//View = getViewMatrix();
	Projection = glm::perspective(glm::radians(camera.Zoom), (float)screenWidth / (float)screenHeight, 0.1f, 2000.0f);
	//View = camera.GetViewMatrix();
	View = camera.LookAtOrigin();
	calcNewLocations();
	setUpMVPS();
	//SUN --- ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform-----------------------------------------------------------------------------------------------
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &sunMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sunTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, sunVertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, sunUvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, sunVertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//MERCURY --- ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform-----------------------------------------------------------------------------------------------
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mercuryMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mercuryTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mercuryVertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mercuryUvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, mercuryVertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//VENUS --- ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform-----------------------------------------------------------------------------------------------
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &venusMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, venusTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, venusVertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, venusUvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, venusVertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//EARTH --- ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform-----------------------------------------------------------------------------------------------
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &earthMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, earthTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, earthVertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, earthUvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, earthVertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//MOON --- ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform-----------------------------------------------------------------------------------------------
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &moonMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, moonTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, moonVertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, moonUvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, moonVertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	
	//MARS --- ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform-----------------------------------------------------------------------------------------------
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &marsMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, marsTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, marsVertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, marsUvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, marsVertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//JUPITER --- ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform-----------------------------------------------------------------------------------------------
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &jupiterMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, jupiterTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, jupiterVertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, jupiterUvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, jupiterVertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//SATURN --- ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform-----------------------------------------------------------------------------------------------
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &saturnMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, saturnTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, saturnVertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, saturnUvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, saturnVertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//URANUS --- ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform-----------------------------------------------------------------------------------------------
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &uranusMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, uranusTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, uranusVertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uranusUvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, uranusVertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//NEPTUNE --- ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform-----------------------------------------------------------------------------------------------
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &neptuneMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, neptuneTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, neptuneVertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, neptuneUvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, neptuneVertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Tutorial 07 - Model Loading", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");

	loadTextures();

	// Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(programID, "myTextureSampler");

	loadObjects();

	loadAllVBOs();

	do {

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawSpheres();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO and shader
	glDeleteBuffers(1, &sunVertexbuffer);
	glDeleteBuffers(1, &sunUvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &sunTexture);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}