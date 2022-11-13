#include "BossProjectileScript.h"

void BossProjectileScript::startScript() {
}

void BossProjectileScript::setEntities(Entity* player, Entity* boss, Entity* player_projectile) {
	this->player = player;
	this->boss = boss;
	this->player_projectile = player_projectile;
}


void BossProjectileScript::endGame() {
	world->destroy(entity);
}

void BossProjectileScript::spawnProjectile() {

	ComponentHandle<Transform> transform = entity->get<Transform>();
	ComponentHandle<Transform> posBoss = boss->get<Transform>();
	ComponentHandle<Transform> posPlayer = player->get<Transform>();

	if (spawned || glfwGetTime() < delay) {
		return;
	}

	transform->position = posBoss->position;
	currDir = glm::normalize(transform->position - posPlayer->position);
	spawned = true;
}

void BossProjectileScript::tickScript(float deltaTime) {

	ComponentHandle<Transform> transform = entity->get<Transform>();

	spawnProjectile();

	transform->position -= currDir * deltaTime;

	if (transform->position.x < 120 || transform->position.x > 1480 || transform->position.y < 120 || transform->position.y > 680) {
		transform->position = glm::vec2(-100.f, -100.f);
		spawned = false;
	}

	CheckCollisions();

}

void BossProjectileScript::CheckCollisions() {

	ComponentHandle<Transform> transform = entity->get<Transform>();
	ComponentHandle<BoxCollider> collider = entity->get<BoxCollider>();

	world->each<BoxCollider>([&](Entity* other_ent, ComponentHandle<BoxCollider> other_collider) {

		if (other_ent->getEntityId() == entity->getEntityId() || other_ent->getEntityId() == boss->getEntityId() || other_ent->getEntityId() == player_projectile->getEntityId()) {
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
			other_collider->collidedWith = true;
			transform->position = glm::vec2(-100.f, -100.f);
			spawned = false;
		}
		});

}