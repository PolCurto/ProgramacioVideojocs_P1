#pragma once

#include "Script.h"

using namespace std;

class PaddleScript : public Script
{

    using Script::Script;

public:

    void startScript() override;

    void tickScript(float deltaTime) override;

    void checkHits();

    bool isAlive();

private:

    int hp = 3;
    bool alive = true;
    float stage = 1;
};