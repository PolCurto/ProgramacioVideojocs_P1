#pragma once

#include "Script.h"

using namespace std;

class BlockScript : public Script
{

    using Script::Script;

public:

    void setParameters(Entity* onj, int secs);

    void moveToTarget();

    void spawn();

    void tickScript(float deltaTime) override;

    void Break();

private:

    Entity* target;
    glm::vec2 currDir;
    bool notSpawned = true;
    int delay;
    int hp = 2;
    bool destroyed = false;

};