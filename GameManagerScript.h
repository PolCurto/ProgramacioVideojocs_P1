#pragma once

#include "Script.h"
#include "BlockScript.h"
#include "PaddleScript.h"
#include "BossScript.h"

using namespace std;

class GameManagerScript : public Script
{

    using Script::Script;

public:

    void tickScript(float deltaTime) override;

    void addPlayer(PaddleScript* player);

    void addEnemy(BlockScript* enemy);

    void addBoss(BossScript* boss);

    void spawnBoss();

private:

    std::vector <BlockScript*> enemies;
    PaddleScript* player;
    BossScript* boss;
};