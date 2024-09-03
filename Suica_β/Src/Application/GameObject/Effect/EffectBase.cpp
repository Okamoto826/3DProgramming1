#include "EffectBase.h"

void EffectBase::PostUpdate()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_size);

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = scaleMat * transMat;
}

void EffectBase::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
	}
}

void EffectBase::DrawUnLit()
{
	if (!m_spPoly)return;

	if (m_anime != 0.0f)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld, m_color);
	}
}

void EffectBase::DrawBright()
{
	if (!m_spPoly && m_anime == 0.0f)return;

	if (m_anime != 0.0f)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld, m_color);
	}
}
