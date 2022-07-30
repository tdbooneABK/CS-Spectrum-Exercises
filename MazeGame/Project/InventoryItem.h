#pragma once
#include <string>
#include "PlacableActor.h"

class InventoryItem : public PlacableActor
{
public:
	InventoryItem(int x, int y, ActorColor color);
	InventoryItem();
	virtual ~InventoryItem();

	virtual ActorType GetType() { return ActorType::InventoryItem; };
	virtual void Draw() = 0;
	virtual std::string GetName() = 0;
};
