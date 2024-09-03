#include "Time.h"

void Time::PostUpdate()
{
	m_frame--;
	if (m_frame == 0)
	{
		m_frame = 60;
		m_second--;
	}

	m_numberList.clear();
	m_numberList.push_back(m_second / 60);
	m_numberList.push_back((m_second % 60) / 10);
	m_numberList.push_back((m_second % 60) % 10);
}

void Time::DrawSprite()
{
	Math::Rectangle _rect = { 0,0,long(m_colonTex->GetWidth()),long(m_colonTex->GetHeight()) };
	KdShaderManager::Instance().m_spriteShader.DrawTex
	(
		m_colonTex,
		m_pos.x + m_colonTex->GetWidth() / 2,
		m_pos.y,
		_rect.width * m_scale.x,
		_rect.height * m_scale.y,
		&_rect
	);

	_rect = { 0,0,100,100 };
	for (int i = 0; i < m_numberList.size(); i++)
	{
		_rect.x = _rect.width * m_numberList[i];
		if (i != 2)
		{
			KdShaderManager::Instance().m_spriteShader.DrawTex
			(
				m_spTex,
				m_pos.x + ((_rect.width * m_scale.x) * i),
				m_pos.y,
				_rect.width * m_scale.x,
				_rect.height * m_scale.y,
				&_rect
			);
		}
		else
		{
			KdShaderManager::Instance().m_spriteShader.DrawTex
			(
				m_spTex,
				m_pos.x + ((_rect.width * m_scale.x * 0.85f) * i),
				m_pos.y,
				_rect.width * m_scale.x,
				_rect.height * m_scale.y,
				&_rect
			);
		}
	}
}

void Time::Init()
{
	m_colonTex = KdAssets::Instance().m_textures.GetData("Asset/Textures/Time/colon.png");
	m_spTex = KdAssets::Instance().m_textures.GetData("Asset/Textures/Time/number.png");
	m_pos = { 300,300,0 };
}
