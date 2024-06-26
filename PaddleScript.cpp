#include "PaddleScript.h"

void PaddleScript::startScript() {
}

void PaddleScript::tickScript(float deltaTime) {

	if (!alive) {
		return;
	}

	ComponentHandle<Transform> transform = entity->get<Transform>();
	
	if (!invulnerable) {
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			transform->position += glm::vec2(1., 0.) * deltaTime / 2.f;

			if (transform->position.x > 1475) transform->position.x = 1475;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			transform->position += glm::vec2(-1., 0.) * deltaTime / 2.f;

			if (transform->position.x < 125) transform->position.x = 125;
		}

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			transform->position += glm::vec2(0., -1.) * deltaTime / 2.f;

			if (transform->position.y < 125) transform->position.y = 125;
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			transform->position += glm::vec2(0., 1.) * deltaTime / 2.f;

			if (transform->position.y > 675) transform->position.y = 675;
		}
	}
	else {
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			transform->position += glm::vec2(1., 0.) * deltaTime;

			if (transform->position.x > 1475) transform->position.x = 1475;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			transform->position += glm::vec2(-1., 0.) * deltaTime;

			if (transform->position.x < 125) transform->position.x = 125;
		}

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			transform->position += glm::vec2(0., -1.) * deltaTime;

			if (transform->position.y < 125) transform->position.y = 125;
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			transform->position += glm::vec2(0., 1.) * deltaTime;

			if (transform->position.y > 675) transform->position.y = 675;
		}
	}

	checkHits();
	checkVulnerability();
}

void PaddleScript::checkHits() {

	ComponentHandle<BoxCollider> collider = entity->get<BoxCollider>();
	ComponentHandle<Transform> transform = entity->get<Transform>();
	ComponentHandle<Sprite> spr = entity->get<Sprite>();

	if (invulnerable) {
		spr->filepath = "Textures/main_character 4.png";
	}

	if (collider->collidedWith) {
		
		collider->collidedWith = false;

		if (!invulnerable) {
			hp--;
			timeRef = glfwGetTime();
			invulnerable = true;

			if (hp == 2) {
				spr->filepath = "Textures/main_character 2.png";
				stage = 2;
			}

			if (hp == 1) {
				spr->filepath = "Textures/main_character 3.png";
				stage = 3;
			}

			if (hp <= 0) {
				transform->position = glm::vec2(-100.f, -100.f);
				alive = false;
			}
		}
	}
	
	

}

void PaddleScript::endGame() {
	ComponentHandle<Transform> transform = entity->get<Transform>();

	alive = false;
	transform->position = glm::vec2(-100.f, -100.f);
	
}

void PaddleScript::checkVulnerability() {

	ComponentHandle<Sprite> spr = entity->get<Sprite>();

	if (invulnerable) {

		if (glfwGetTime() > timeRef + 1.) {
			invulnerable = false;
			if (stage == 1) {
				spr->filepath = "Textures/main_character 1.png";
			}
			if (stage == 2) {
				spr->filepath = "Textures/main_character 2.png";
			}
			if (stage == 3) {
				spr->filepath = "Textures/main_character 3.png";
			}
		}
	}
}

bool PaddleScript::isAlive() {
	return alive;
}