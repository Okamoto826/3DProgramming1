#include "ResultScore.h"

void ResultScore::Init()
{
	m_sp_tex->Load(ScorePng);

	ResultBase::Init();

	CreateNumbers(m_score, m_posX + BaseNumbersWhile, m_posY);
}

void ResultScore::Update()
{

}



