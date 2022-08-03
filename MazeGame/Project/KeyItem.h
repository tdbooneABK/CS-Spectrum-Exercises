#pragma once
#include "InventoryItem.h"
#include "Key.h"

class KeyItem : public InventoryItem
{
	ActorColor m_KeyColor;
public:
	KeyItem(ActorColor keyColor);
	~KeyItem();
	std::string GetName() override;
	ActorColor GetColor() { return m_KeyColor; }
	ItemType GetType() override { return ItemType::Key; }
};
