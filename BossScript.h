#pragma once

#include "Script.h"

using namespace std;

class BossScript : public Script
{

    using Script::Script;

public:

    void setParameters(Entity* obj, int delay);

    void moveToTarget(float deltaTime);

    void spawn();

    void endGame();

    void tickScript(float deltaTime) override;

    void checkCollisions();

    void Break();

private:

    Entity* target;
    glm::vec2 currDir;
    bool notSpawned = true;
    int hp = 15;
    bool destroyed = false;
    int delay;
    float stage = 1;

};