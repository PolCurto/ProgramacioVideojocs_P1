#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <math.h>
#include <ctime>
#include <chrono>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "RenderSystem.h"
#include "ScriptSystem.h"
#include "ScriptManager.h"
#include "BallScript.h"
#include "PaddleScript.h"
#include "BlockScript.h"
#include "Script.h"
#include "GameManagerScript.h"
#include "BossScript.h"
#include "BossProjectileScript.h"

#include "ECS.h"

using std::cout; 
using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
using namespace ECS;

GLFWwindow* window; // Game window
const unsigned int width = 1600;
const unsigned int height = 800;

float t = 0;
time_t current_time;

World* world;

void SetupGLFW() {

	glfwInit();

	// Tell GLFW we are using OpenGL 3.3 and the CORE profile (only the modern functions)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

bool SetupWindow() {
	//Create a GLFWwindow with size 800x800
	window = glfwCreateWindow(width, height, "The binding of isaac 0.1", NULL, NULL);
	if (window == NULL) {

		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	// Make window part of the current context
	glfwMakeContextCurrent(window);

	//Load GLAD and specify the viewport
	gladLoadGL();
	glViewport(0, 0, width, height);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

Entity* CreateEntity(glm::vec2 position, float rotation, float scale, const char* filepath, glm::vec3 color, 
	bool autoSize = true, glm::vec2 size = glm::vec2(1.0, 1.0), const char* shaderName = "default") {
	Entity* ent = world->create();
	ent->assign<Transform>(position, rotation, scale);
	ent->assign<Sprite>(filepath, color, autoSize, size, shaderName);

	return ent;
}

void SetupWorld() {

	world = World::createWorld();
	world->registerSystem(new RenderSystem(width, height));
	ScriptSystem* scriptSystem = new ScriptSystem();
	world->registerSystem(scriptSystem);

	ScriptManager* scriptManager = scriptSystem->getScriptManager();

	Entity* gameManager_ent = CreateEntity(glm::vec2(800.f, 400.f), 0.f, 1.f, "Textures/room.png", glm::vec3(1., 1., 1.), false, glm::vec2(width, height));
	GameManagerScript* gameManager = new GameManagerScript(window, world, gameManager_ent);
	gameManager_ent->assign<ScriptComponent>(scriptManager->AddScript(gameManager));

	Entity* paddle_ent = CreateEntity(glm::vec2(800.f, 400.f), 0.f, 1.f, "Textures/main_character 1.png", glm::vec3(1., 1., 1.));
	paddle_ent->assign<BoxCollider>(80.f, 80.f);

	PaddleScript* paddle_script = new PaddleScript(window, world, paddle_ent);
	paddle_ent->assign<ScriptComponent>(scriptManager->AddScript(paddle_script));

	Entity* ball_ent = CreateEntity(glm::vec2(-100.f, -100.f), 0.f, 1.f, "Textures/projectile_right.png", glm::vec3(1., 1., 1.));
	ball_ent->assign<BoxCollider>(32.f, 32.f);

	BallScript* ball_script = new BallScript(window, world, ball_ent);

	Entity* boss_ent = CreateEntity(glm::vec2(-500.f, -500.f), 0.f, 1.f, "Textures/boss 1.png", glm::vec3(1., 1., 1.));
	boss_ent->assign<BoxCollider>(90.f, 90.f);
	BossScript* boss_script = new BossScript(window, world, boss_ent);

	Entity* boss_projectile_ent = CreateEntity(glm::vec2(-200.f, -200.f), 0.f, 1.f, "Textures/boss_projectile.png", glm::vec3(1., 1., 1.));
	boss_projectile_ent->assign<BoxCollider>(32.f, 32.f);

	ball_script->setEntities(paddle_ent, boss_projectile_ent);
	ball_ent->assign<ScriptComponent>(scriptManager->AddScript(ball_script));

	boss_script->setEntities(paddle_ent, boss_projectile_ent);
	boss_ent->assign<ScriptComponent>(scriptManager->AddScript(boss_script));

	BossProjectileScript* boss_projectile_script = new BossProjectileScript(window, world, boss_projectile_ent);
	boss_projectile_script->setEntities(paddle_ent, boss_ent, ball_ent);
	boss_projectile_ent->assign<ScriptComponent>(scriptManager->AddScript(boss_projectile_script));

	gameManager->addBoss(boss_script, boss_projectile_script);
	gameManager->addPlayer(paddle_script);

	for (int i = 0; i < 20; i++) {
		Entity* block_ent = CreateEntity(glm::vec2(2000.f, 2000.f), 0.f, 1.f, "Textures/enemy 1.png", glm::vec3(1., 1., 1.));
		block_ent->assign<BoxCollider>(80.f, 80.f);

		BlockScript* block_script = new BlockScript(window, world, block_ent);
		block_script->setParameters(paddle_ent, 2 * (1 + i));
		block_ent->assign<ScriptComponent>(scriptManager->AddScript(block_script));

		gameManager->addEnemy(block_script);
	}
	
}

int main() {
	
	SetupGLFW();

	if (!SetupWindow()) {
		return -1;
	}

	SetupWorld();

	float dt = 0;
	float time = clock();

	//Program core loop
	while (!glfwWindowShouldClose(window)) {

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		dt = clock() - time;
		time = clock();
		if (dt < 50) {
			world->tick(dt);
		}

		glfwSwapBuffers(window); //Swap buffers

		// Take care of GLFW events
		glfwPollEvents();
	}

	// Cleanup

	glfwDestroyWindow(window);
	glfwTerminate();

	world->destroyWorld();

	return 0;
}