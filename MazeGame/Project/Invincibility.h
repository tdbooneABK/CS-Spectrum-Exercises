#pragma once
#include "PlacableActor.h"

class Invincibility :
    public PlacableActor
{
public:
    Invincibility(int x, int y);
    ActorType GetType();
    void Draw();
};
