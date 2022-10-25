#include "BlockScript.h"

void BlockScript::setParameters(Entity* obj, int secs) {
	target = obj;
	delay = secs;

}

void BlockScript::moveToTarget() {

	ComponentHandle<Transform> posObj = entity->get<Transform>();
	ComponentHandle<Transform> posTarget = target->get<Transform>();

	if (!notSpawned) {
		currDir = glm::normalize(posObj->position - posTarget->position);
		posObj->position -= currDir;
	}

}

void BlockScript::spawn() {
	ComponentHandle<Transform> posObj = entity->get<Transform>();
	
	if (notSpawned) {
		if (glfwGetTime() > delay) {
			cout << "hola" << endl;

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

	if (collider->collidedWith) {
		hp--;
		collider->collidedWith = false;

		if (hp <= 0) {
			destroyed = true;
			world->destroy(entity);
		}
	}

	spawn();
	moveToTarget();

}