#include "BlockScript.h"

void BlockScript::setParameters(Entity* obj, int secs) {
	target = obj;
	delay = secs;
}

void BlockScript::moveToTarget(float deltaTime) {

	ComponentHandle<Transform> posObj = entity->get<Transform>();
	ComponentHandle<Transform> posTarget = target->get<Transform>();

	if (!notSpawned) {
		currDir = glm::normalize(posObj->position - posTarget->position);
		posObj->position -= (currDir * deltaTime / 5.f) * (stage / 1.5f);
	}

}

void BlockScript::spawn() {
	ComponentHandle<Transform> posObj = entity->get<Transform>();
	
	if (notSpawned) {
		if (glfwGetTime() > delay) {

			if (rand() % 100 > 50) {
				posObj->position.x = 200;
				posObj->position.y = 400;
			}
			else {
				posObj->position.x = 1400;
				posObj->position.y = 400;
			}
			notSpawned = false;
		}
	}
}

void BlockScript::tickScript(float deltaTime) {

	if (destroyed) return;

	ComponentHandle<BoxCollider> collider = entity->get<BoxCollider>();

	ComponentHandle<Sprite> spr = entity->get<Sprite>();

	if (collider->collidedWith) {
		collider->collidedWith = false;
		hp--;

		if (hp == 2) {
			spr->filepath = "Textures/enemy 2.png";
			stage = 2;
		}

		if (hp == 1) {
			spr->filepath = "Textures/enemy 3.png";
			stage = 3;
		}

		if (hp <= 0) {
			world->destroy(entity);
			destroyed = true;
		}
	}

	spawn();
	moveToTarget(deltaTime);
	checkCollisions();

}

void BlockScript::endGame() {
	world->destroy(entity);
}

void BlockScript::checkCollisions() {

	ComponentHandle<Transform> transform = entity->get<Transform>();
	ComponentHandle<BoxCollider> collider = entity->get<BoxCollider>();

	world->each<BoxCollider>([&](Entity* other_ent, ComponentHandle<BoxCollider> other_collider) {

		if (!(other_ent->getEntityId() == target->getEntityId())) {
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
			world->destroy(entity);
			destroyed = true;
			other_collider->collidedWith = true;
		}
		});
}