/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <game/generated/protocol.h>
#include <game/server/gamecontext.h>
#include <engine/shared/config.h>
#include "food.h"

CFood::CFood(CGameWorld *pGameWorld, vec2 Pos)
: CEntity(pGameWorld, CGameWorld::ENTTYPE_LASER)
{
	m_Pos = Pos;
	GameWorld()->InsertEntity(this);
	m_lifetime = Server()->TickSpeed()*g_Config.m_SvFoodExpiration;
}


bool CFood::OnCharacter()
{
	CCharacter *pHit = GameServer()->m_World.ClosestCharacter(m_Pos, 32.0, this);
	if(!pHit)
		return false;
	pHit->GetPlayer()->m_Score+= g_Config.m_SvFoodCalories;
	GameServer()->CreateSound(m_Pos, SOUND_PICKUP_HEALTH);
	return true;
}


void CFood::Reset()
{
	GameServer()->m_pController->m_Amount--;
	GameServer()->m_World.DestroyEntity(this);
}

void CFood::Tick()
{
	if(OnCharacter())
	{
		GameServer()->m_pController->m_Amount--;
		GameServer()->m_World.DestroyEntity(this);
	}
	if(m_lifetime == 0)
	{
		GameServer()->m_pController->GenerateFood();
		GameServer()->m_pController->m_Amount--;
		GameServer()->m_World.DestroyEntity(this);
	}
	else
		m_lifetime--;
}

void CFood::TickPaused()
{
	++m_EvalTick;
}

void CFood::Snap(int SnappingClient)
{
	if(NetworkClipped(SnappingClient))
		return;

	CNetObj_Laser *pObj = static_cast<CNetObj_Laser *>(Server()->SnapNewItem(NETOBJTYPE_LASER, m_ID, sizeof(CNetObj_Laser)));
	if(!pObj)
		return;

	pObj->m_X = (int)m_Pos.x;
	pObj->m_Y = (int)m_Pos.y;
	pObj->m_StartTick = m_EvalTick;
}