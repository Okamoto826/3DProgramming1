#include "EventManager.h"

void EventManager::SubScore()
{
	m_score -= 200;

	if (m_score < 0)
	{
		m_score = 0;
	}
}

void EventManager::Init()
{
	m_playerMoveAmount = 0.f;
	m_playerPos = {};
	m_score = 0;
	m_clubCoolTime = 0;
	m_restTime = 0;
	m_bPlayerMove = false;
	m_bBreak = false;
	m_bMake = false;
	m_combo = 0;
	m_maxCombo = 0;
}
