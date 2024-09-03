#include "ResultNumber.h"

void ResultNumber::Init()
{
	m_sp_tex->Load(NumberPng);

	ResultBase::Init();

	m_randamNumberTimeCnt = RandamNumberTime;
	m_randamNumberChangeTimeCnt = RandamNumberChangeTime;

	RandamNumberSet();

	m_scale.x /= TEN_NUM;
}

void ResultNumber::Update()
{
	if (m_b_randamTime)
	{
		m_randamNumberTimeCnt--;
		m_randamNumberChangeTimeCnt--;

		if (m_randamNumberTimeCnt <= ResetCount) 
		{
			m_b_randamTime = false;
			if (m_b_isNotNum)	{ m_isExpired = true; }
			else				{ m_rect = { m_number * NumberTexSize, ZERO, NumberTexSize, NumberTexSize }; }
		}
		else if (m_randamNumberChangeTimeCnt <= ResetCount) 
		{
			m_randamNumberChangeTimeCnt = RandamNumberChangeTime;
			RandamNumberSet();
		}
	}
}

void ResultNumber::RandamNumberSet()
{
	m_randamNumber  = m_randamGenerator->GetInt(ZERO, TEN_NUM + BACK);
	m_rect			= { m_randamNumber * NumberTexSize, ZERO, NumberTexSize, NumberTexSize };
}
