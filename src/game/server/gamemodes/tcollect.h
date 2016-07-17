/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_SERVER_GAMEMODES_TCOLLECT_H
#define GAME_SERVER_GAMEMODES_TCOLLECT_H
#include <game/server/gamecontroller.h>
#include <engine/shared/config.h>

// you can subclass GAMECONTROLLER_CTF, GAMECONTROLLER_TDM etc if you want
// todo a modification with their base as well.
class CGameControllerTCOLLECT : public IGameController
{
public:
	CGameControllerTCOLLECT(class CGameContext *pGameServer);
	virtual void Tick();
        virtual bool OnEntity(int Index, vec2 Pos);
	virtual void GenerateFood();
	// add more virtual functions here if you wish
private:
	int m_Airtiles;
	
};
#endif
