#include "Score.h"
#include "../../../Scene/SceneManager.h"
#include "Application/Scene/GameScene/EventManager.h"

void Score::DrawSprite()
{
	Math::Rectangle _rect = { 0,0,long(m_scoreTex->GetWidth()),long(m_scoreTex->GetHeight()) };

	KdShaderManager::Instance().m_spriteShader.DrawTex
	(
		m_scoreTex,
		m_scorePos.x,
		m_scorePos.y,
		_rect.width * m_scoreScale.x,
		_rect.height * m_scoreScale.y,
		&_rect
	);

	_rect = { 0,0,100,100 };

	for (unsigned i = 0; i < m_numberList.size(); i++)
	{
		_rect.x = _rect.width * m_numberList[i];
		KdShaderManager::Instance().m_spriteShader.DrawTex
		(
			m_spTex,
			m_pos.x + ((_rect.width * m_scale.x*0.7f) * i),
			m_pos.y,
			_rect.width * m_scale.x,
			_rect.height * m_scale.y,
			&_rect
		);
	}
}

void Score::PostUpdate()
{
	//if (m_score == SceneManager::Instance().GetScore())return;
	m_score = EventManager::Instance().GetScore();

	m_numberList.clear();
	std::string _str = std::to_string(m_score);
	for (unsigned i = 0; i < _str.size(); i++)
	{
		char _ch = _str[i];
		m_numberList.push_back(std::stoi(&_ch));
	}
}

void Score::Init()
{
	m_scoreTex = KdAssets::Instance().m_textures.GetData("Asset/Textures/Score/score.png");
	m_scorePos = { -500,300,0 };
	m_scoreScale = { 0.5f,0.5f,0.5f };

	m_spTex = KdAssets::Instance().m_textures.GetData("Asset/Textures/Score/number.png");
	m_pos = { -350,300,0 };
	m_scale = { 0.5f,0.5f,0.5f };
}