#include "BallScript.h"

void BallScript::startScript() {

}

void BallScript::tickScript(float deltaTime) {

	ComponentHandle<Transform> transform = entity->get<Transform>();

	transform->position += currDir * deltaTime / 2.f;

	if (transform->position.x < 0 || transform->position.x || transform->position.x || transform->position.x) currDir.x *= -1;

	CheckCollisions();

}

void BallScript::CheckCollisions() {

	ComponentHandle<Transform> transform = entity->get<Transform>();
	ComponentHandle<BoxCollider> collider = entity->get<BoxCollider>();

	world->each<BoxCollider>([&](Entity* other_ent, ComponentHandle<BoxCollider> other_collider) {

		if (other_ent->getEntityId() == entity->getEntityId()) {
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
			currDir = glm::normalize(transform->position - other_transform->position);
			other_collider->collidedWith = true;
		}


	});

}