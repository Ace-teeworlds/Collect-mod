/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_SERVER_ENTITIES_FOOD_H
#define GAME_SERVER_ENTITIES_FOOD_H

#include <game/server/entity.h>

class CFood : public CEntity
{
public:
	CFood(CGameWorld *pGameWorld, vec2 Pos);

	virtual void Reset();
	virtual void Tick();
	virtual void TickPaused();
	virtual void Snap(int SnappingClient);

protected:
	bool OnCharacter();

private:
	vec2 m_From;
	vec2 m_Dir;
	float m_Energy;
	int m_Bounces;
	int m_EvalTick;
	int m_Owner;
	int m_lifetime;
};

#endif