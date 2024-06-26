#pragma once

#include "Script.h"

using namespace std;

class BallScript : public Script
{

    using Script::Script;

public:

    void startScript() override;

    void setEntities(Entity* player, Entity* boss_projectile);

    void tickScript(float deltaTime) override;

private:

    void spawnProjectile();

    void CheckCollisions();

    Entity* player;
    Entity* boss_projectile;
    glm::vec2 currDir = glm::vec2(0., 1.);
    bool spawned = false;

};