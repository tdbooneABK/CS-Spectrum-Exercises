#include <iostream>
#include "PlayerInfoDialog.h"
#include "Player.h"
#include "Enemy.h"
#include "Encounter.h"

int main()
{
    srand(time(0));
    PlayerInfoDialog infoDialog = PlayerInfoDialog();
    Player player = infoDialog.GetPlayerInfo();
    Enemy enemy = Enemy();
    Encounter encounter = Encounter(player, enemy);
    encounter.Run();
}