#include "GameManagerScript.h"
#include "PaddleScript.h"
#include "BlockScript.h"
#include "BossScript.h"
#include "BossProjectileScript.h"

void GameManagerScript::tickScript(float deltaTime) {

	ComponentHandle<Sprite> spr = entity->get<Sprite>();

	if (boss->getStage() == 3) {
		projectile->endGame();
	}

	if (!(player->isAlive())) {
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->endGame();
		}
		boss->endGame();
		projectile->endGame();
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

void GameManagerScript::addBoss(BossScript* boss, BossProjectileScript* projectile) {
	this->boss = boss;
	this->projectile = projectile;
}

