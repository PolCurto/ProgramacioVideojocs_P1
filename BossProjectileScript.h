#pragma once

#include "Script.h"

using namespace std;

class BossProjectileScript : public Script
{

    using Script::Script;

public:

    void startScript() override;

    void tickScript(float deltaTime) override;

    void setEntities(Entity* player, Entity* boss, Entity* player_projectile);

    void endGame();

private:

    void spawnProjectile();

    void CheckCollisions();

    Entity* player;
    Entity* boss;
    Entity* player_projectile;
    int delay = 46;
    glm::vec2 currDir;
    bool spawned = false;
};