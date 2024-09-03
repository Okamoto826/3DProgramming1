#include "ResultCombo.h"

void ResultCombo::Init()
{
	m_sp_tex->Load(ComboPng);

	ResultBase::Init();

	CreateNumbers(m_combo, m_posX + BaseNumbersWhile, m_posY);
}

void ResultCombo::Update()
{
}

