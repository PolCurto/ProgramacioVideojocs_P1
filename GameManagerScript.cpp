#include "GameManagerScript.h"
#include "PaddleScript.h"
#include "BlockScript.h"
#include "BossScript.h"

void GameManagerScript::tickScript(float deltaTime) {

	ComponentHandle<Sprite> spr = entity->get<Sprite>();

	if (!(player->isAlive())) {
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->endGame();
		}
		boss->endGame();
		spr->filepath = "Textures/game_over.png";
	}

	if (boss->isDestroyed()) {
		spr->filepath = "Textures/you_win.png";
		player->endGame();
	}

}

void GameManagerScript::addPlayer(PaddleScript* player) {
	this->player = player;
}

void GameManagerScript::addEnemy(BlockScript* enemy) {
	this->enemies.push_back(enemy);
}

void GameManagerScript::addBoss(BossScript* boss) {
	this->boss = boss;
}

