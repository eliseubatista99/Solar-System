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
#include <common/objloader.hpp>
#include "include/camera.h"
//#include <include/shader_m.h>

GLuint VertexArrayID;
// Create and compile our GLSL program from the shaders
GLuint programID;
// Get a handle for our "MVP" uniform
GLuint MatrixID;
glm::mat4 Projection;
glm::mat4 View;
// Get a handle for our "myTextureSampler" uniform
GLuint TextureID;
Camera camera(glm::vec3(0.0f, 30.0f, 120.0f));
unsigned int screenWidth = 1280, screenHeight = 768;
float lastX = screenWidth / 2.0f;
float lastY = screenHeight / 2.0f;
bool firstMouse = true;
bool paused = false;
bool firstFrame = true;

float camMoveSpeed = 100.0f;

void framebuffer_size_callback(GLFWwindow* window, int screenWidth, int screenHeight);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float sunScale = 20.0f;
float offsetFromNeptune = 140.0f;
float offsetFromLookToPlanet = 2.0f;
bool rochosos = true;
bool gasosos = true;
bool toLook = false;
bool canT = true, canRight = true, canLeft = true, canSpace = true, canL = true, canI = true;
int planetIndex = -1;
int currentVision = 0; //0 - sun, 1 - top, 2 - Initial, 3 - on planet, 4 - free
glm::vec3 lookDestination(0.0f, 0.0f, 0.0f);
glm::vec3 topVision(0.0f, 0.0f, 0.0f);
glm::vec3 initVision(0.0f, 30.0f, 120.0f);

//---SUN------------------------------------------
std::vector<glm::vec3> sunVertices;
std::vector<glm::vec3> mercuryVertices;
std::vector<glm::vec3> mercuryOrbitVertices;
std::vector<glm::vec3> venusVertices;
std::vector<glm::vec3> venusOrbitVertices;
std::vector<glm::vec3> earthVertices;
std::vector<glm::vec3> earthOrbitVertices;
std::vector<glm::vec3> moonVertices;
std::vector<glm::vec3> moonOrbitVertices;
std::vector<glm::vec3> marsVertices;
std::vector<glm::vec3> marsOrbitVertices;
std::vector<glm::vec3> jupiterVertices;
std::vector<glm::vec3> jupiterOrbitVertices;
std::vector<glm::vec3> saturnVertices;
std::vector<glm::vec3> saturnOrbitVertices;
std::vector<glm::vec3> uranusVertices;
std::vector<glm::vec3> uranusOrbitVertices;
std::vector<glm::vec3> uranusRingsVertices;
std::vector<glm::vec3> neptuneVertices;
std::vector<glm::vec3> neptuneOrbitVertices;

std::vector<glm::vec2> sunUvs;
std::vector<glm::vec2> mercuryUvs;
std::vector<glm::vec2> mercuryOrbitUvs;
std::vector<glm::vec2> venusUvs;
std::vector<glm::vec2> venusOrbitUvs;
std::vector<glm::vec2> earthUvs;
std::vector<glm::vec2> earthOrbitUvs;
std::vector<glm::vec2> moonUvs;
std::vector<glm::vec2> moonOrbitUvs;
std::vector<glm::vec2> marsUvs;
std::vector<glm::vec2> marsOrbitUvs;
std::vector<glm::vec2> jupiterUvs;
std::vector<glm::vec2> jupiterOrbitUvs;
std::vector<glm::vec2> saturnUvs;
std::vector<glm::vec2> saturnOrbitUvs;
std::vector<glm::vec2> uranusUvs;
std::vector<glm::vec2> uranusRingsUvs;
std::vector<glm::vec2> uranusOrbitUvs;
std::vector<glm::vec2> neptuneUvs;
std::vector<glm::vec2> neptuneOrbitUvs;

std::vector<glm::vec3> sunNormals; // Won't be used at the moment.
std::vector<glm::vec3> mercuryNormals; // Won't be used at the moment.
std::vector<glm::vec3> mercuryOrbitNormals; // Won't be used at the moment.
std::vector<glm::vec3> venusNormals; // Won't be used at the moment.
std::vector<glm::vec3> venusOrbitNormals; // Won't be used at the moment.
std::vector<glm::vec3> earthNormals; // Won't be used at the moment.
std::vector<glm::vec3> earthOrbitNormals; // Won't be used at the moment.
std::vector<glm::vec3> moonNormals; // Won't be used at the moment.
std::vector<glm::vec3> moonOrbitNormals; // Won't be used at the moment.
std::vector<glm::vec3> marsNormals; // Won't be used at the moment.
std::vector<glm::vec3> marsOrbitNormals; // Won't be used at the moment.
std::vector<glm::vec3> jupiterNormals; // Won't be used at the moment.
std::vector<glm::vec3> jupiterOrbitNormals; // Won't be used at the moment.
std::vector<glm::vec3> saturnNormals; // Won't be used at the moment.
std::vector<glm::vec3> saturnOrbitNormals; // Won't be used at the moment.
std::vector<glm::vec3> uranusNormals; // Won't be used at the moment.
std::vector<glm::vec3> uranusRingsNormals; // Won't be used at the moment.
std::vector<glm::vec3> uranusOrbitNormals; // Won't be used at the moment.
std::vector<glm::vec3> neptuneNormals; // Won't be used at the moment.
std::vector<glm::vec3> neptuneOrbitNormals; // Won't be used at the moment.


// Load the texture
GLuint sunTexture;
GLuint mercuryTexture;
GLuint mercuryOrbitTexture;
GLuint venusTexture;
GLuint venusOrbitTexture;
GLuint earthTexture;
GLuint earthOrbitTexture;
GLuint moonTexture;
GLuint moonOrbitTexture;
GLuint marsTexture;
GLuint marsOrbitTexture;
GLuint jupiterTexture;
GLuint jupiterOrbitTexture;
GLuint saturnTexture;
GLuint saturnOrbitTexture;
GLuint uranusTexture;
GLuint uranusRingsTexture;
GLuint uranusOrbitTexture;
GLuint neptuneTexture;
GLuint neptuneOrbitTexture;

GLuint sunVertexbuffer;
GLuint mercuryVertexbuffer;
GLuint mercuryOrbitVertexbuffer;
GLuint venusVertexbuffer;
GLuint venusOrbitVertexbuffer;
GLuint earthVertexbuffer;
GLuint earthOrbitVertexbuffer;
GLuint moonVertexbuffer;
GLuint moonOrbitVertexbuffer;
GLuint marsVertexbuffer;
GLuint marsOrbitVertexbuffer;
GLuint jupiterVertexbuffer;
GLuint jupiterOrbitVertexbuffer;
GLuint saturnVertexbuffer;
GLuint saturnOrbitVertexbuffer;
GLuint uranusVertexbuffer;
GLuint uranusRingsVertexbuffer;
GLuint uranusOrbitVertexbuffer;
GLuint neptuneVertexbuffer;
GLuint neptuneOrbitVertexbuffer;

GLuint sunUvbuffer;
GLuint mercuryUvbuffer;
GLuint mercuryOrbitUvbuffer;
GLuint venusUvbuffer;
GLuint venusOrbitUvbuffer;
GLuint earthUvbuffer;
GLuint earthOrbitUvbuffer;
GLuint moonUvbuffer;
GLuint moonOrbitUvbuffer;
GLuint marsUvbuffer;
GLuint marsOrbitUvbuffer;
GLuint jupiterUvbuffer;
GLuint jupiterOrbitUvbuffer;
GLuint saturnUvbuffer;
GLuint saturnOrbitUvbuffer;
GLuint uranusUvbuffer;
GLuint uranusRingsUvbuffer;
GLuint uranusOrbitUvbuffer;
GLuint neptuneUvbuffer;
GLuint neptuneOrbitUvbuffer;


glm::mat4 sunModelMatrix;
glm::mat4 mercuryModelMatrix;
glm::mat4 mercuryOrbitModelMatrix;
glm::mat4 venusModelMatrix;
glm::mat4 venusOrbitModelMatrix;
glm::mat4 earthModelMatrix;
glm::mat4 earthOrbitModelMatrix;
glm::mat4 moonModelMatrix;
glm::mat4 moonOrbitModelMatrix;
glm::mat4 marsModelMatrix;
glm::mat4 marsOrbitModelMatrix;
glm::mat4 jupiterModelMatrix;
glm::mat4 jupiterOrbitModelMatrix;
glm::mat4 saturnModelMatrix;
glm::mat4 saturnOrbitModelMatrix;
glm::mat4 uranusModelMatrix;
glm::mat4 uranusRingsModelMatrix;
glm::mat4 uranusOrbitModelMatrix;
glm::mat4 neptuneModelMatrix;
glm::mat4 neptuneOrbitModelMatrix;


glm::mat4 sunMVP;
glm::mat4 mercuryMVP;
glm::mat4 mercuryOrbitMVP;
glm::mat4 venusMVP;
glm::mat4 venusOrbitMVP;
glm::mat4 earthMVP;
glm::mat4 earthOrbitMVP;
glm::mat4 moonMVP;
glm::mat4 moonOrbitMVP;
glm::mat4 marsMVP;
glm::mat4 marsOrbitMVP;
glm::mat4 jupiterMVP;
glm::mat4 jupiterOrbitMVP;
glm::mat4 saturnMVP;
glm::mat4 saturnOrbitMVP;
glm::mat4 uranusMVP;
glm::mat4 uranusRingsMVP;
glm::mat4 uranusOrbitMVP;
glm::mat4 neptuneMVP;
glm::mat4 neptuneOrbitMVP;

//----------------------------------------
float planetLocations[9][3] = {
	{26.0f,0.0f,0.0f}, //MERCURY
	{30.0f,0.0f,0.0f}, //VENUS
	{34.0f,0.0f,0.0f}, //EARTH
	{34.0f,0.0f,0.0f}, //MOON
	{38.0f,0.0f,0.0f}, //MARS
	{45.0f,0.0f,0.0f}, //JUPITER
	{55.0f,0.0f,0.0f}, //SATURN
	{65.0f,0.0f,0.0f}, //URANUS
	{75.0f,0.0f,0.0f}, //NEPTUNE
};

//----------------------------------------
float lookToPlanetLocations[9][3] = {
	{26.0f,0.0f,0.0f}, //MERCURY
	{30.0f,0.0f,0.0f}, //VENUS
	{34.0f,0.0f,0.0f}, //EARTH
	{34.0f,0.0f,0.0f}, //MOON
	{38.0f,0.0f,0.0f}, //MARS
	{45.0f,0.0f,0.0f}, //JUPITER
	{55.0f,0.0f,0.0f}, //SATURN
	{65.0f,0.0f,0.0f}, //URANUS
	{75.0f,0.0f,0.0f}, //NEPTUNE
};

float planetDistance[9] = { 26.0f, 30.0f, 34.0f, 2.0f, 38.0f, 45.0f, 55.0f, 65.0f, 75.0f };

float planetTranslationSpeed[9] = { 0.85f, -0.63f,  -0.53f, 1.89f , -0.43f,  -0.23f,  -0.17f,  -0.12f,  -0.9f };

float planetRotationSpeed[9] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

float planetRotationValue[9] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

float planetAngles[9] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

float planetScales[9] = { 1.0f, 1.2f, 1.6f, 0.2f, 0.8f, 5.0f, 4.25f, 3.0f, 2.9f };

float planetOffsets[9] = { 2.0f, 2.2f, 2.6f, 1.2f, 1.8f, 6.5f, 6.25f, 4.5f, 4.0f };

void loadTextures() {
	// Load the texture
	sunTexture = loadDDS("resources/textures/sun_texture_8k.dds");
	if (sunTexture == -1) exit(EXIT_FAILURE);
	mercuryTexture = loadDDS("resources/textures/mercury_texture.dds");
	if (mercuryTexture == -1) exit(EXIT_FAILURE);
	venusTexture = loadDDS("resources/textures/venus_texture.dds");
	if (venusTexture == -1) exit(EXIT_FAILURE);
	earthTexture = loadDDS("resources/textures/earth_texture.dds");
	if (earthTexture == -1) exit(EXIT_FAILURE);
	moonTexture = loadDDS("resources/textures/moon_texture.dds");
	if (moonTexture == -1) exit(EXIT_FAILURE);
	marsTexture = loadDDS("resources/textures/mars_texture.dds");
	if (marsTexture == -1) exit(EXIT_FAILURE);
	jupiterTexture = loadDDS("resources/textures/jupiter_texture.dds");
	if (jupiterTexture == -1) exit(EXIT_FAILURE);
	saturnTexture = loadDDS("resources/textures/saturn_texture.dds");
	if (saturnTexture == -1) exit(EXIT_FAILURE);
	uranusTexture = loadDDS("resources/textures/uranus_texture.dds");
	if (uranusTexture == -1) exit(EXIT_FAILURE);
	uranusRingsTexture = loadDDS("resources/textures/uranus_rings_texture.dds");
	if (uranusRingsTexture == -1) exit(EXIT_FAILURE);
	neptuneTexture = loadDDS("resources/textures/neptune_texture.dds");
	if (neptuneTexture == -1) exit(EXIT_FAILURE);
	mercuryOrbitTexture = uranusRingsTexture;
	venusOrbitTexture = uranusRingsTexture;
	earthOrbitTexture = uranusRingsTexture;
	moonOrbitTexture = uranusRingsTexture;
	marsOrbitTexture = uranusRingsTexture;
	jupiterOrbitTexture = uranusRingsTexture;
	saturnOrbitTexture = uranusRingsTexture;
	uranusOrbitTexture = uranusRingsTexture;
	neptuneOrbitTexture = uranusRingsTexture;
}

void loadObjects() {
	if (!loadOBJ("resources/models/no_rings_planet.obj", sunVertices, sunUvs, sunNormals)) {
		exit(EXIT_FAILURE);
	}
	if (!loadOBJ("resources/models/saturn.obj", saturnVertices, saturnUvs, saturnNormals)) {
		exit(EXIT_FAILURE);
	}
	if (!loadOBJ("resources/models/uranus_rings.obj", uranusRingsVertices, uranusRingsUvs, uranusRingsNormals)) {
		exit(EXIT_FAILURE);
	}
	if (!loadOBJ("resources/models/orbit.obj", mercuryOrbitVertices, mercuryOrbitUvs, mercuryOrbitNormals)) {
		exit(EXIT_FAILURE);
	}

	mercuryVertices = sunVertices;
	mercuryUvs = sunUvs;
	mercuryNormals = sunNormals;

	venusVertices = sunVertices;
	venusUvs = sunUvs;
	venusNormals = sunNormals;

	venusOrbitVertices = mercuryOrbitVertices;
	venusOrbitUvs = mercuryOrbitUvs;
	venusOrbitNormals = mercuryOrbitNormals;

	earthVertices = sunVertices;
	earthUvs = sunUvs;
	earthNormals = sunNormals;

	earthOrbitVertices = mercuryOrbitVertices;
	earthOrbitUvs = mercuryOrbitUvs;
	earthOrbitNormals = mercuryOrbitNormals;

	moonVertices = sunVertices;
	moonUvs = sunUvs;
	moonNormals = sunNormals;

	moonOrbitVertices = mercuryOrbitVertices;
	moonOrbitUvs = mercuryOrbitUvs;
	moonOrbitNormals = mercuryOrbitNormals;

	marsVertices = sunVertices;
	marsUvs = sunUvs;
	marsNormals = sunNormals;

	marsOrbitVertices = mercuryOrbitVertices;
	marsOrbitUvs = mercuryOrbitUvs;
	marsOrbitNormals = mercuryOrbitNormals;

	jupiterVertices = sunVertices;
	jupiterUvs = sunUvs;
	jupiterNormals = sunNormals;

	jupiterOrbitVertices = mercuryOrbitVertices;
	jupiterOrbitUvs = mercuryOrbitUvs;
	jupiterOrbitNormals = mercuryOrbitNormals;

	saturnOrbitVertices = mercuryOrbitVertices;
	saturnOrbitUvs = mercuryOrbitUvs;
	saturnOrbitNormals = mercuryOrbitNormals;

	uranusVertices = sunVertices;
	uranusUvs = sunUvs;
	uranusNormals = sunNormals;

	uranusOrbitVertices = mercuryOrbitVertices;
	uranusOrbitUvs = mercuryOrbitUvs;
	uranusOrbitNormals = mercuryOrbitNormals;

	neptuneVertices = sunVertices;
	neptuneUvs = sunUvs;
	neptuneNormals = sunNormals;

	neptuneOrbitVertices = mercuryOrbitVertices;
	neptuneOrbitUvs = mercuryOrbitUvs;
	neptuneOrbitNormals = mercuryOrbitNormals;

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
	glGenBuffers(1, &uranusRingsVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uranusRingsVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, uranusRingsVertices.size() * sizeof(glm::vec3), &uranusRingsVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uranusRingsUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uranusRingsUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uranusRingsUvs.size() * sizeof(glm::vec2), &uranusRingsUvs[0], GL_STATIC_DRAW);
	// Load it into a VBO
	glGenBuffers(1, &neptuneVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, neptuneVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, neptuneVertices.size() * sizeof(glm::vec3), &neptuneVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &neptuneUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, neptuneUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, neptuneUvs.size() * sizeof(glm::vec2), &neptuneUvs[0], GL_STATIC_DRAW);
	// Load it into a VBO
	glGenBuffers(1, &mercuryOrbitVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mercuryOrbitVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, mercuryOrbitVertices.size() * sizeof(glm::vec3), &mercuryOrbitVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &mercuryOrbitUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mercuryOrbitUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, mercuryOrbitUvs.size() * sizeof(glm::vec2), &mercuryOrbitUvs[0], GL_STATIC_DRAW);
	// Load it into a VBO
	glGenBuffers(1, &venusOrbitVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, venusOrbitVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, venusOrbitVertices.size() * sizeof(glm::vec3), &venusOrbitVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &venusOrbitUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, venusOrbitUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, venusOrbitUvs.size() * sizeof(glm::vec2), &venusOrbitUvs[0], GL_STATIC_DRAW);
	// Load it into a VBO
	glGenBuffers(1, &earthOrbitVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, earthOrbitVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, earthOrbitVertices.size() * sizeof(glm::vec3), &earthOrbitVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &earthOrbitUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, earthOrbitUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, earthOrbitUvs.size() * sizeof(glm::vec2), &earthOrbitUvs[0], GL_STATIC_DRAW);
	// Load it into a VBO
	glGenBuffers(1, &moonOrbitVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, moonOrbitVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, moonOrbitVertices.size() * sizeof(glm::vec3), &moonOrbitVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &moonOrbitUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, moonOrbitUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, moonOrbitUvs.size() * sizeof(glm::vec2), &moonOrbitUvs[0], GL_STATIC_DRAW);
	// Load it into a VBO
	glGenBuffers(1, &marsOrbitVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, marsOrbitVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, marsOrbitVertices.size() * sizeof(glm::vec3), &marsOrbitVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &marsOrbitUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, marsOrbitUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, marsOrbitUvs.size() * sizeof(glm::vec2), &marsOrbitUvs[0], GL_STATIC_DRAW);
	// Load it into a VBO
	glGenBuffers(1, &jupiterOrbitVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, jupiterOrbitVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, jupiterOrbitVertices.size() * sizeof(glm::vec3), &jupiterOrbitVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &jupiterOrbitUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, jupiterOrbitUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, jupiterOrbitUvs.size() * sizeof(glm::vec2), &jupiterOrbitUvs[0], GL_STATIC_DRAW);
	// Load it into a VBO
	glGenBuffers(1, &saturnOrbitVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, saturnOrbitVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, saturnOrbitVertices.size() * sizeof(glm::vec3), &saturnOrbitVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &saturnOrbitUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, saturnOrbitUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, saturnOrbitUvs.size() * sizeof(glm::vec2), &saturnOrbitUvs[0], GL_STATIC_DRAW);
	// Load it into a VBO
	glGenBuffers(1, &uranusOrbitVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uranusOrbitVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, uranusOrbitVertices.size() * sizeof(glm::vec3), &uranusOrbitVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uranusOrbitUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uranusOrbitUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uranusOrbitUvs.size() * sizeof(glm::vec2), &uranusOrbitUvs[0], GL_STATIC_DRAW);
	// Load it into a VBO
	glGenBuffers(1, &neptuneOrbitVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, neptuneOrbitVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, neptuneOrbitVertices.size() * sizeof(glm::vec3), &neptuneOrbitVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &neptuneOrbitUvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, neptuneOrbitUvbuffer);
	glBufferData(GL_ARRAY_BUFFER, neptuneOrbitUvs.size() * sizeof(glm::vec2), &neptuneOrbitUvs[0], GL_STATIC_DRAW);

}

void calculateNewLookLocations(int i) {
	for (int i = 0; i < 9; i++) {
		if (i == 3) {
			lookToPlanetLocations[i][0] = planetLocations[2][0] + ((planetDistance[i] + (offsetFromLookToPlanet * planetOffsets[i])) * sin(planetAngles[i]));
			lookToPlanetLocations[i][1] = 2.0f;
			lookToPlanetLocations[i][2] = planetLocations[2][2] + ((planetDistance[i] + (offsetFromLookToPlanet * planetOffsets[i])) * cos(planetAngles[i]));
		}
		else {
			lookToPlanetLocations[i][0] = (planetDistance[i] + (offsetFromLookToPlanet * planetOffsets[i])) * cos(planetAngles[i]);
			lookToPlanetLocations[i][1] = 2.0f;
			lookToPlanetLocations[i][2] = (planetDistance[i] + (offsetFromLookToPlanet * planetOffsets[i])) * sin(planetAngles[i]);
		}
	}
}

void calcNewLocations() {

	if (paused)
		return;

	for (int i = 0; i < 9; i++) {
		planetAngles[i] += (planetTranslationSpeed[i] * deltaTime);
		planetRotationValue[i] += (planetRotationSpeed[i] * deltaTime);
		if (planetRotationValue[i] >= 360.0f) {
			planetRotationValue[i] = -360.0f;
		}
		if (i == 3) {
			planetLocations[i][0] = planetLocations[2][0] + (planetDistance[i] * sin(planetAngles[i]));
			planetLocations[i][2] = planetLocations[2][2] + (planetDistance[i] * cos(planetAngles[i]));

		}
		else {
			planetLocations[i][0] = planetDistance[i] * cos(planetAngles[i]);
			planetLocations[i][2] = planetDistance[i] * sin(planetAngles[i]);
		}
		calculateNewLookLocations(i);
	}
}



void setUpMVPS() {

	sunModelMatrix = glm::mat4(1.0);
	sunModelMatrix = glm::scale(sunModelMatrix, glm::vec3(sunScale)); //84
	sunMVP = Projection * View * sunModelMatrix;

	if (rochosos) {
		mercuryModelMatrix = glm::mat4(1.0);
		mercuryModelMatrix = glm::translate(mercuryModelMatrix, glm::vec3(planetLocations[0][0], planetLocations[0][1], planetLocations[0][2]));
		mercuryModelMatrix = glm::rotate(mercuryModelMatrix, glm::radians(planetRotationValue[0]), glm::vec3(1, 1, 0));
		mercuryModelMatrix = glm::scale(mercuryModelMatrix, glm::vec3(planetScales[0]));
		mercuryMVP = Projection * View * mercuryModelMatrix;

		mercuryOrbitModelMatrix = glm::mat4(1.0);
		mercuryOrbitModelMatrix = glm::scale(mercuryOrbitModelMatrix, glm::vec3(planetDistance[0]));
		mercuryOrbitMVP = Projection * View * mercuryOrbitModelMatrix;

		venusModelMatrix = glm::mat4(1.0);
		venusModelMatrix = glm::translate(venusModelMatrix, glm::vec3(planetLocations[1][0], planetLocations[1][1], planetLocations[1][2]));
		venusModelMatrix = glm::rotate(venusModelMatrix, glm::radians(planetRotationValue[1]), glm::vec3(1, 1, 0));
		venusModelMatrix = glm::scale(venusModelMatrix, glm::vec3(planetScales[1]));
		venusMVP = Projection * View * venusModelMatrix;

		venusOrbitModelMatrix = glm::mat4(1.0);
		venusOrbitModelMatrix = glm::scale(venusOrbitModelMatrix, glm::vec3(planetDistance[1]));
		venusOrbitMVP = Projection * View * venusOrbitModelMatrix;

		earthModelMatrix = glm::mat4(1.0);
		earthModelMatrix = glm::translate(earthModelMatrix, glm::vec3(planetLocations[2][0], planetLocations[2][1], planetLocations[2][2]));
		earthModelMatrix = glm::rotate(earthModelMatrix, glm::radians(planetRotationValue[2]), glm::vec3(1, 1, 0));
		earthModelMatrix = glm::scale(earthModelMatrix, glm::vec3(planetScales[2]));
		earthMVP = Projection * View * earthModelMatrix;

		earthOrbitModelMatrix = glm::mat4(1.0);
		earthOrbitModelMatrix = glm::scale(earthOrbitModelMatrix, glm::vec3(planetDistance[2]));
		earthOrbitMVP = Projection * View * earthOrbitModelMatrix;

		moonModelMatrix = glm::mat4(1.0);
		moonModelMatrix = glm::translate(moonModelMatrix, glm::vec3(planetLocations[3][0], planetLocations[3][1], planetLocations[3][2]));
		moonModelMatrix = glm::scale(moonModelMatrix, glm::vec3(planetScales[3]));
		moonModelMatrix = glm::rotate(moonModelMatrix, glm::radians(planetRotationValue[3]), glm::vec3(1, 1, 0));
		moonMVP = Projection * View * moonModelMatrix;

		moonOrbitModelMatrix = glm::mat4(1.0);
		moonOrbitModelMatrix = glm::translate(moonOrbitModelMatrix, glm::vec3(planetLocations[2][0], planetLocations[2][1], planetLocations[2][2]));
		moonOrbitModelMatrix = glm::scale(moonOrbitModelMatrix, glm::vec3(planetDistance[3]));
		//moonOrbitModelMatrix = glm::rotate(moonOrbitModelMatrix, glm::radians(-45.0f), glm::vec3(-1, 1, 1));
		moonOrbitMVP = Projection * View * moonOrbitModelMatrix;

		marsModelMatrix = glm::mat4(1.0);
		marsModelMatrix = glm::translate(marsModelMatrix, glm::vec3(planetLocations[4][0], planetLocations[4][1], planetLocations[4][2]));
		marsModelMatrix = glm::rotate(marsModelMatrix, glm::radians(planetRotationValue[4]), glm::vec3(1, 1, 0));
		marsModelMatrix = glm::scale(marsModelMatrix, glm::vec3(planetScales[4]));
		marsMVP = Projection * View * marsModelMatrix;

		marsOrbitModelMatrix = glm::mat4(1.0);
		marsOrbitModelMatrix = glm::scale(marsOrbitModelMatrix, glm::vec3(planetDistance[4]));
		marsOrbitMVP = Projection * View * marsOrbitModelMatrix;
	}
	else {

		mercuryModelMatrix = glm::mat4(1.0);
		mercuryModelMatrix = glm::translate(mercuryModelMatrix, glm::vec3(planetLocations[0][0], planetLocations[0][1], planetLocations[0][2]));
		mercuryModelMatrix = glm::rotate(mercuryModelMatrix, glm::radians(planetRotationValue[0]), glm::vec3(1, 1, 0));
		mercuryModelMatrix = glm::scale(mercuryModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		mercuryMVP = Projection * View * mercuryModelMatrix;

		mercuryOrbitModelMatrix = glm::mat4(1.0);
		mercuryOrbitModelMatrix = glm::scale(mercuryOrbitModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		mercuryOrbitMVP = Projection * View * mercuryOrbitModelMatrix;

		venusModelMatrix = glm::mat4(1.0);
		venusModelMatrix = glm::translate(venusModelMatrix, glm::vec3(planetLocations[1][0], planetLocations[1][1], planetLocations[1][2]));
		venusModelMatrix = glm::rotate(venusModelMatrix, glm::radians(planetRotationValue[1]), glm::vec3(1, 1, 0));
		venusModelMatrix = glm::scale(venusModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		venusMVP = Projection * View * venusModelMatrix;

		venusOrbitModelMatrix = glm::mat4(1.0);
		venusOrbitModelMatrix = glm::scale(venusOrbitModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		venusOrbitMVP = Projection * View * venusOrbitModelMatrix;

		earthModelMatrix = glm::mat4(1.0);
		earthModelMatrix = glm::translate(earthModelMatrix, glm::vec3(planetLocations[2][0], planetLocations[2][1], planetLocations[2][2]));
		earthModelMatrix = glm::rotate(earthModelMatrix, glm::radians(planetRotationValue[2]), glm::vec3(1, 1, 0));
		earthModelMatrix = glm::scale(earthModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		earthMVP = Projection * View * earthModelMatrix;

		earthOrbitModelMatrix = glm::mat4(1.0);
		earthOrbitModelMatrix = glm::scale(earthOrbitModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		earthOrbitMVP = Projection * View * earthOrbitModelMatrix;

		moonModelMatrix = glm::mat4(1.0);
		moonModelMatrix = glm::translate(moonModelMatrix, glm::vec3(planetLocations[3][0], planetLocations[3][1], planetLocations[3][2]));
		moonModelMatrix = glm::scale(moonModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		moonModelMatrix = glm::rotate(moonModelMatrix, glm::radians(planetRotationValue[3]), glm::vec3(1, 1, 0));
		moonMVP = Projection * View * moonModelMatrix;

		moonOrbitModelMatrix = glm::mat4(1.0);
		moonOrbitModelMatrix = glm::translate(moonOrbitModelMatrix, glm::vec3(planetLocations[2][0], planetLocations[2][1], planetLocations[2][2]));
		moonOrbitModelMatrix = glm::scale(moonOrbitModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		//moonOrbitModelMatrix = glm::rotate(moonOrbitModelMatrix, glm::radians(-45.0f), glm::vec3(-1, 1, 1));
		moonOrbitMVP = Projection * View * moonOrbitModelMatrix;

		marsModelMatrix = glm::mat4(1.0);
		marsModelMatrix = glm::translate(marsModelMatrix, glm::vec3(planetLocations[4][0], planetLocations[4][1], planetLocations[4][2]));
		marsModelMatrix = glm::rotate(marsModelMatrix, glm::radians(planetRotationValue[4]), glm::vec3(1, 1, 0));
		marsModelMatrix = glm::scale(marsModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		marsMVP = Projection * View * marsModelMatrix;

		marsOrbitModelMatrix = glm::mat4(1.0);
		marsOrbitModelMatrix = glm::scale(marsOrbitModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		marsOrbitMVP = Projection * View * marsOrbitModelMatrix;

	}

	if (gasosos) {
		jupiterModelMatrix = glm::mat4(1.0);
		jupiterModelMatrix = glm::translate(jupiterModelMatrix, glm::vec3(planetLocations[5][0], planetLocations[5][1], planetLocations[5][2]));
		jupiterModelMatrix = glm::rotate(jupiterModelMatrix, glm::radians(planetRotationValue[5]), glm::vec3(1, 1, 0));
		jupiterModelMatrix = glm::scale(jupiterModelMatrix, glm::vec3(planetScales[5]));
		jupiterMVP = Projection * View * jupiterModelMatrix;

		jupiterOrbitModelMatrix = glm::mat4(1.0);
		jupiterOrbitModelMatrix = glm::scale(jupiterOrbitModelMatrix, glm::vec3(planetDistance[5]));
		jupiterOrbitMVP = Projection * View * jupiterOrbitModelMatrix;

		saturnModelMatrix = glm::mat4(1.0);
		saturnModelMatrix = glm::translate(saturnModelMatrix, glm::vec3(planetLocations[6][0], planetLocations[6][1], planetLocations[6][2]));
		saturnModelMatrix = glm::rotate(saturnModelMatrix, glm::radians(planetRotationValue[6]), glm::vec3(1, 1, 0));
		saturnModelMatrix = glm::scale(saturnModelMatrix, glm::vec3(planetScales[6]));
		saturnMVP = Projection * View * saturnModelMatrix;

		saturnOrbitModelMatrix = glm::mat4(1.0);
		saturnOrbitModelMatrix = glm::scale(saturnOrbitModelMatrix, glm::vec3(planetDistance[6]));
		saturnOrbitMVP = Projection * View * saturnOrbitModelMatrix;

		uranusModelMatrix = glm::mat4(1.0);
		uranusModelMatrix = glm::translate(uranusModelMatrix, glm::vec3(planetLocations[7][0], planetLocations[7][1], planetLocations[7][2]));
		uranusModelMatrix = glm::rotate(uranusModelMatrix, glm::radians(planetRotationValue[7]), glm::vec3(1, 1, 0));
		uranusModelMatrix = glm::scale(uranusModelMatrix, glm::vec3(planetScales[7]));
		uranusMVP = Projection * View * uranusModelMatrix;

		uranusRingsModelMatrix = glm::mat4(1.0);
		uranusRingsModelMatrix = glm::translate(uranusRingsModelMatrix, glm::vec3(planetLocations[7][0], planetLocations[7][1], planetLocations[7][2]));
		uranusRingsModelMatrix = glm::rotate(uranusRingsModelMatrix, glm::radians(planetRotationValue[7]), glm::vec3(1, 1, 0));
		uranusRingsModelMatrix = glm::scale(uranusRingsModelMatrix, glm::vec3(planetScales[7]));
		uranusRingsMVP = Projection * View * uranusRingsModelMatrix;

		uranusOrbitModelMatrix = glm::mat4(1.0);
		uranusOrbitModelMatrix = glm::scale(uranusOrbitModelMatrix, glm::vec3(planetDistance[7]));
		uranusOrbitMVP = Projection * View * uranusOrbitModelMatrix;

		neptuneModelMatrix = glm::mat4(1.0);
		neptuneModelMatrix = glm::translate(neptuneModelMatrix, glm::vec3(planetLocations[8][0], planetLocations[8][1], planetLocations[8][2]));
		neptuneModelMatrix = glm::rotate(neptuneModelMatrix, glm::radians(planetRotationValue[8]), glm::vec3(1, 1, 0));
		neptuneModelMatrix = glm::scale(neptuneModelMatrix, glm::vec3(planetScales[8]));
		neptuneMVP = Projection * View * neptuneModelMatrix;

		neptuneOrbitModelMatrix = glm::mat4(1.0);
		neptuneOrbitModelMatrix = glm::scale(neptuneOrbitModelMatrix, glm::vec3(planetDistance[8]));
		neptuneOrbitMVP = Projection * View * neptuneOrbitModelMatrix;
	}
	else {

		jupiterModelMatrix = glm::mat4(1.0);
		jupiterModelMatrix = glm::translate(jupiterModelMatrix, glm::vec3(planetLocations[5][0], planetLocations[5][1], planetLocations[5][2]));
		jupiterModelMatrix = glm::rotate(jupiterModelMatrix, glm::radians(planetRotationValue[5]), glm::vec3(1, 1, 0));
		jupiterModelMatrix = glm::scale(jupiterModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		jupiterMVP = Projection * View * jupiterModelMatrix;

		jupiterOrbitModelMatrix = glm::mat4(1.0);
		jupiterOrbitModelMatrix = glm::scale(jupiterOrbitModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		jupiterOrbitMVP = Projection * View * jupiterOrbitModelMatrix;

		saturnModelMatrix = glm::mat4(1.0);
		saturnModelMatrix = glm::translate(saturnModelMatrix, glm::vec3(planetLocations[6][0], planetLocations[6][1], planetLocations[6][2]));
		saturnModelMatrix = glm::rotate(saturnModelMatrix, glm::radians(planetRotationValue[6]), glm::vec3(1, 1, 0));
		saturnModelMatrix = glm::scale(saturnModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		saturnMVP = Projection * View * saturnModelMatrix;

		saturnOrbitModelMatrix = glm::mat4(1.0);
		saturnOrbitModelMatrix = glm::scale(saturnOrbitModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		saturnOrbitMVP = Projection * View * saturnOrbitModelMatrix;

		uranusModelMatrix = glm::mat4(1.0);
		uranusModelMatrix = glm::translate(uranusModelMatrix, glm::vec3(planetLocations[7][0], planetLocations[7][1], planetLocations[7][2]));
		uranusModelMatrix = glm::rotate(uranusModelMatrix, glm::radians(planetRotationValue[7]), glm::vec3(1, 1, 0));
		uranusModelMatrix = glm::scale(uranusModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		uranusMVP = Projection * View * uranusModelMatrix;

		uranusRingsModelMatrix = glm::mat4(1.0);
		uranusRingsModelMatrix = glm::translate(uranusRingsModelMatrix, glm::vec3(planetLocations[7][0], planetLocations[7][1], planetLocations[7][2]));
		uranusRingsModelMatrix = glm::rotate(uranusRingsModelMatrix, glm::radians(planetRotationValue[7]), glm::vec3(1, 1, 0));
		uranusRingsModelMatrix = glm::scale(uranusRingsModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		uranusRingsMVP = Projection * View * uranusRingsModelMatrix;

		uranusOrbitModelMatrix = glm::mat4(1.0);
		uranusOrbitModelMatrix = glm::scale(uranusOrbitModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		uranusOrbitMVP = Projection * View * uranusOrbitModelMatrix;

		neptuneModelMatrix = glm::mat4(1.0);
		neptuneModelMatrix = glm::translate(neptuneModelMatrix, glm::vec3(planetLocations[8][0], planetLocations[8][1], planetLocations[8][2]));
		neptuneModelMatrix = glm::rotate(neptuneModelMatrix, glm::radians(planetRotationValue[8]), glm::vec3(1, 1, 0));
		neptuneModelMatrix = glm::scale(neptuneModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		neptuneMVP = Projection * View * neptuneModelMatrix;

		neptuneOrbitModelMatrix = glm::mat4(1.0);
		neptuneOrbitModelMatrix = glm::scale(neptuneOrbitModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		neptuneOrbitMVP = Projection * View * neptuneOrbitModelMatrix;

	}
}

void drawSpheres() {
	// Use our shader
	glUseProgram(programID);
	Projection = glm::perspective(glm::radians(camera.Zoom), (float)screenWidth / (float)screenHeight, 0.1f, 2000.0f);
	View = camera.GetViewMatrix(lookDestination, toLook);

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
	//MERCURY ORBIT--- ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform-----------------------------------------------------------------------------------------------
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mercuryOrbitMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mercuryOrbitTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mercuryOrbitVertexbuffer);
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
	glBindBuffer(GL_ARRAY_BUFFER, mercuryOrbitUvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, mercuryOrbitVertices.size());

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
	//VENUS ORBIT --- ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform-----------------------------------------------------------------------------------------------
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &venusOrbitMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, venusOrbitTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, venusOrbitVertexbuffer);
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
	glBindBuffer(GL_ARRAY_BUFFER, venusOrbitUvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, venusOrbitVertices.size());

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
	//EARTH ORBIT --- ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform-----------------------------------------------------------------------------------------------
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &earthOrbitMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, earthOrbitTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, earthOrbitVertexbuffer);
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
	glBindBuffer(GL_ARRAY_BUFFER, earthOrbitUvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, earthOrbitVertices.size());

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
	//MOON ORBIT --- ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform-----------------------------------------------------------------------------------------------
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &moonOrbitMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, moonOrbitTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, moonOrbitVertexbuffer);
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
	glBindBuffer(GL_ARRAY_BUFFER, moonOrbitUvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, moonOrbitVertices.size());

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
	//MARS ORBIT--- ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform-----------------------------------------------------------------------------------------------
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &marsOrbitMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, marsOrbitTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, marsOrbitVertexbuffer);
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
	glBindBuffer(GL_ARRAY_BUFFER, marsOrbitUvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, marsOrbitVertices.size());

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
	//JUPITER ORBIT--- ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform-----------------------------------------------------------------------------------------------
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &jupiterOrbitMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, jupiterOrbitTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, jupiterOrbitVertexbuffer);
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
	glBindBuffer(GL_ARRAY_BUFFER, jupiterOrbitUvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, jupiterOrbitVertices.size());

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
	//SATURN ORBIT--- ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform-----------------------------------------------------------------------------------------------
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &saturnOrbitMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, saturnOrbitTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, saturnOrbitVertexbuffer);
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
	glBindBuffer(GL_ARRAY_BUFFER, saturnOrbitUvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, saturnOrbitVertices.size());

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
	//URANUS RINGS --- ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform-----------------------------------------------------------------------------------------------
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &uranusRingsMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, uranusRingsTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, uranusRingsVertexbuffer);
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
	glBindBuffer(GL_ARRAY_BUFFER, uranusRingsUvbuffer);
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
	//URANUS ORBIT --- ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform-----------------------------------------------------------------------------------------------
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &uranusOrbitMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, uranusOrbitTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, uranusOrbitVertexbuffer);
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
	glBindBuffer(GL_ARRAY_BUFFER, uranusOrbitUvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, uranusOrbitVertices.size());

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
	//NEPTUNE ORBIT --- ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform-----------------------------------------------------------------------------------------------
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &neptuneOrbitMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, neptuneOrbitTexture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, neptuneOrbitVertexbuffer);
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
	glBindBuffer(GL_ARRAY_BUFFER, neptuneOrbitUvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, neptuneOrbitVertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}

void updateLook() {
	if (planetIndex == -1) {
		return;
	}
	glm::vec3 dest(0.0f, 0.0f, 0.0f);
	dest.x = lookToPlanetLocations[planetIndex][0];
	dest.y = lookToPlanetLocations[planetIndex][1];
	dest.z = lookToPlanetLocations[planetIndex][2];
	camera.setCameraView(dest);
	lookDestination = glm::vec3(planetLocations[planetIndex][0], planetLocations[planetIndex][1], planetLocations[planetIndex][2]);

}

void lookToSun(int view) {
	if (view == currentVision || view == 4) {
		planetIndex = -1;
		lookDestination = glm::vec3(0.0f, 0.0f, 0.0f);
		toLook = false;
		currentVision = 4;
	}
	else {
		planetIndex = -1;
		lookDestination = glm::vec3(0.0f, 0.0f, 0.0f);
		toLook = true;
		currentVision = view;
	}
	
}

void lookToPlanet(bool direction) { //false - dec /true - inc	
	if (!direction) {
		planetIndex--;
	}
	else {
		planetIndex++;
	}
	if (planetIndex > 8) {
		planetIndex = 0;
	}
	else if (planetIndex < 0) {
		planetIndex = 8;
	}
	currentVision = 3;
	toLook = true;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	screenWidth = width;
	screenHeight = height;
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (toLook) return; 

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime, sunScale + 5.0f, planetDistance[8] + offsetFromNeptune);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime, sunScale + 5.0f, planetDistance[8] + offsetFromNeptune);
	if (!toLook) {
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.ProcessKeyboard(LEFT, deltaTime, sunScale + 5.0f, planetDistance[8] + offsetFromNeptune);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.ProcessKeyboard(RIGHT, deltaTime, sunScale + 5.0f, planetDistance[8] + offsetFromNeptune);
	}
	//pause animations
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)  // If space key is pressed, pause/resume animation
	{
		if (canSpace) {
			canSpace = false;
			paused = !paused;
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
			canSpace = true;
		}
	}


	//Elimina os rochosos
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		if (rochosos) {
			rochosos = false;
		}
		else {
			if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE) {
				rochosos = true;
			}
		}
	}

	//Elimina os gasosos
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		if (gasosos) {
			gasosos = false;
		}
		else {
			if (glfwGetKey(window, GLFW_KEY_G) == GLFW_RELEASE) {
				gasosos = true;
			}
		}
	}


	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		if (canL) {
			canL = false;
			lookToSun(0);
		}
		else {
			if (glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE) {
				canL = true;
			}
		}
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		if (canT) {
			canT = false;
			camera.setCameraView(topVision);
			lookToSun(1);
		}
		else {
			if (glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE) {
				canT = true;
			}
		}
	}

	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		if (canI) {
			canI = false;
			camera.setCameraView(initVision);
			lookToSun(2);
		}
		else {
			if (glfwGetKey(window, GLFW_KEY_I) == GLFW_RELEASE) {
				canI = true;
			}
		}
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		if (canRight) {
			canRight = false;
			lookToPlanet(true);
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE) {
			canRight = true;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		if (canLeft) {
			canLeft = false;
			lookToPlanet(false);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE) {
			canLeft = true;
		}
	}
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
	printf("%d, %d\n", screenWidth, screenHeight);
	// Open a window and create its OpenGL context
	window = glfwCreateWindow(screenWidth, screenHeight, "Solar System GN7", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);
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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("shaders/TransformVertexShader.vertexshader", "shaders/TextureFragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");

	loadTextures();

	// Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(programID, "myTextureSampler");

	loadObjects();

	loadAllVBOs();
	topVision = glm::vec3(0.0f, planetDistance[8] + offsetFromNeptune, 0.0f);
	camera.setMovementSpeed(camMoveSpeed);
	do {

		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		camera.setDeltaTime(deltaTime);
		calcNewLocations();

		// input
		// -----
		//processInput(window);

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (toLook) {
			updateLook();
		}
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