#pragma once

#include "Script.h"
#include "BlockScript.h"

using namespace std;

class BallScript : public Script
{

    using Script::Script;

public:

    void controlShoot();

    void startScript() override;

    void setTarget(Entity* player);

    void tickScript(float deltaTime) override;

private:
    void CheckCollisions();

    Entity* player;
    glm::vec2 currDir = glm::vec2(0., 1.);
    glm::vec2 limits = glm::vec2(1500., 700.);
    bool shot = false;

};