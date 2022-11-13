#pragma once

#include "Script.h"

using namespace std;

class BossScript : public Script
{

    using Script::Script;

public:

    void setEntities(Entity* player, Entity* projectile);

    void moveToTarget(float deltaTime);

    void spawn();

    void endGame();

    void tickScript(float deltaTime) override;

    void checkCollisions();

    bool isDestroyed();

    int getStage();

    void Break();

private:

    Entity* player;
    Entity* projectile;
    glm::vec2 currDir;
    bool notSpawned = true;
    int hp = 20;
    bool destroyed = false;
    int delay = 45;
    float stage = 1;
};