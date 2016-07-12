/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include "collect.h"
#include <game/mapitems.h>
#include <game/server/entities/food.h>
#include <game/server/gamecontext.h>

CGameControllerCOLLECT::CGameControllerCOLLECT(class CGameContext *pGameServer)
: IGameController(pGameServer)
{
	// Exchange this to a string that identifies your game mode.
	// DM, TDM and CTF are reserved for teeworlds original modes.
	m_pGameType = "AGAR";

	//m_GameFlags = GAMEFLAG_TEAMS; // GAMEFLAG_TEAMS makes it a two-team gamemode
}

void CGameControllerCOLLECT::Tick()
{
	// this is the main part of the gamemode, this function is run every tick
	IGameController::Tick();
}

bool CGameControllerCOLLECT::OnEntity(int Index, vec2 Pos)
{
	if(Index == ENTITY_ARMOR_1 || Index == ENTITY_HEALTH_1)
	{
		GenerateFood();
		return false;
	}
	return IGameController::OnEntity(Index, Pos);
}
void CGameControllerCOLLECT::GenerateFood()
{
	vec2 randPos((rand() % GameServer()->Collision()->GetWidth())*32 + 16.0,(rand() % GameServer()->Collision()->GetHeight())*32 + 16.0);
	while(GameServer()->Collision()->CheckPoint(randPos))
		randPos = vec2((rand() % GameServer()->Collision()->GetWidth())*32 + 16.0,(rand() % GameServer()->Collision()->GetHeight())*32 + 16.0);
	new CFood(&GameServer()->m_World, randPos);
}

