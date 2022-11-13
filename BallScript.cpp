#include "BallScript.h"

void BallScript::startScript() {
}

void BallScript::setEntities(Entity* player, Entity* boss_projectile) {
	this->player = player;
	this->boss_projectile = boss_projectile;
}

void BallScript::spawnProjectile() {

	ComponentHandle<Transform> transform = entity->get<Transform>();
	ComponentHandle<Transform> posPlayer = player->get<Transform>();
	ComponentHandle<Sprite> spr = entity->get<Sprite>();

	if (spawned) {
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		spr->filepath = "Textures/projectile_up.png";
		transform->position = posPlayer->position + glm::vec2(0.f, -50.f);
		currDir = glm::vec2(0.f, -1.f);
		spawned = true;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		spr->filepath = "Textures/projectile_down.png";
		transform->position = posPlayer->position + glm::vec2(0.f, 50.f);
		currDir = glm::vec2(0.f, 1.f);
		spawned = true;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		spr->filepath = "Textures/projectile_left.png";
		transform->position = posPlayer->position + glm::vec2(-50.f, 0.f);
		currDir = glm::vec2(-1.f, 0.f);
		spawned = true;
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		spr->filepath = "Textures/projectile_right.png";
		transform->position = posPlayer->position + glm::vec2(50.f, 0.f);
		currDir = glm::vec2(1.f, 0.f);
		spawned = true;
	}

}

void BallScript::tickScript(float deltaTime) {

	ComponentHandle<Transform> transform = entity->get<Transform>();

	spawnProjectile();

	transform->position += currDir * deltaTime;

	if (transform->position.x < 120 || transform->position.x > 1480 || transform->position.y < 120 || transform->position.y > 680) {
		transform->position = glm::vec2(-100.f, -100.f);
		spawned = false;
	}

	CheckCollisions();

}

void BallScript::CheckCollisions() {

	ComponentHandle<Transform> transform = entity->get<Transform>();
	ComponentHandle<BoxCollider> collider = entity->get<BoxCollider>();

	world->each<BoxCollider>([&](Entity* other_ent, ComponentHandle<BoxCollider> other_collider) {

		if (other_ent->getEntityId() == entity->getEntityId() || other_ent->getEntityId() == player->getEntityId() || other_ent->getEntityId() == boss_projectile->getEntityId()) {
			return;
		} 

		ComponentHandle<Transform> other_transform = other_ent->get<Transform>();

		glm::vec2 p1 = transform->position;
		glm::vec2 p2 = other_transform->position;
		
		if (p1.x - collider->width / 2 < p2.x + other_collider->width / 2 &&
			p1.x + collider->width / 2 > p2.x - other_collider->width / 2 &&
			p1.y - collider->height / 2 < p2.y + other_collider->height / 2 &&
			p1.y + collider->height / 2 > p2.y - other_collider->height / 2)
		{
			transform->position = glm::vec2(-100.f, -100.f);
			spawned = false;
			other_collider->collidedWith = true;
		}
	});

}