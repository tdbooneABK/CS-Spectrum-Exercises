#pragma once
#include "InventoryItem.h"

class Key : public InventoryItem
{
public:
	Key(int x, int y, ActorColor color)
		: InventoryItem(x, y, color)
	{

	}

	virtual ActorType GetType() override { return ActorType::Key; }
	virtual void Draw() override;
	virtual std::string GetName() override;
};

