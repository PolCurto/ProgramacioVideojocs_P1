#include "PaddleScript.h"

void PaddleScript::startScript() {
}

void PaddleScript::tickScript(float deltaTime) {

	ComponentHandle<Transform> transform = entity->get<Transform>();
	
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		transform->position += glm::vec2(1., 0.) * deltaTime / 2.f;

		if (transform->position.x > 1500) transform->position.x = 1500;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		transform->position += glm::vec2(-1., 0.) * deltaTime / 2.f;

		if (transform->position.x < 100) transform->position.x = 100;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		transform->position += glm::vec2(0., -1.) * deltaTime / 2.f;

		if (transform->position.y < 100) transform->position.y = 100;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		transform->position += glm::vec2(0., 1.) * deltaTime / 2.f;

		if (transform->position.y > 700) transform->position.y = 700;
	}
}