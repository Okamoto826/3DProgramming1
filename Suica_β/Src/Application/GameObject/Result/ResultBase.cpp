#include "ResultBase.h"
#include "ResultNumber/ResultNumber.h"

#include "../../Scene/SceneManager.h"

void ResultBase::Init()
{
	m_texWidth  = m_sp_tex->GetWidth();
	m_texHeight = m_sp_tex->GetHeight();
	m_rect = { ZERO, ZERO, m_texWidth, m_texHeight };
	m_color = kWhiteColor;
}

void ResultBase::DrawSprite()
{
	if (m_sp_tex)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex
			(m_sp_tex, m_posX, m_posY, 
			(int)(m_texWidth * m_scale.x), (int)(m_texHeight * m_scale.y),
			&m_rect, &m_color);
	}
}

void ResultBase::CreateNumber(const int number, const int posX, const int posY, const bool b_isNotNum)
{
	std::shared_ptr<ResultNumber>resultNumber = std::make_shared<ResultNumber>();
	resultNumber->SetNumber(number);
	resultNumber->SetPos(posX, posY);
	resultNumber->Init();
	if (b_isNotNum) { resultNumber->IsNotNum(); }
	SceneManager::Instance().AddObject(resultNumber);
}
void ResultBase::CreateNumbers(const int number, const int posX, const int posY)
{
	for (int i = ResetCount; i < BaseNumberDigit; i++)
	{
		if (i == ResetCount || number >= (int)pow(TEN_NUM, i))
		{
			CreateNumber(GetDigit(number, i + NEXT), posX - i * BaseNumberWhile, posY);
		}
		else 
		{
			CreateNumber(GetDigit(number, i + NEXT), posX - i * BaseNumberWhile, posY, true);
		}
	}
}
