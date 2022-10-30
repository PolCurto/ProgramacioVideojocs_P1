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
		spr->filepath = "textures/game_over.png";
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

