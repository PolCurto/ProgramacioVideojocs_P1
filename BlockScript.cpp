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
		cout << hp << endl;
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

}