#pragma once
#include "Player.h"

class RestDialog
{
	bool m_hasRested;
	Player* m_playerPt;
	void PrintPlayerInfo();
	void DrawOptions();
	void Rest();
public :
	RestDialog(Player* playerPt);
	~RestDialog();
	bool Run();
};
