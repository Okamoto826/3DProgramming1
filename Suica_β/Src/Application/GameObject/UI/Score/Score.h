#pragma once

class GameScene;

class Score
	:public KdGameObject
{
public:

	Score() {}
	~Score()override {}

	void DrawSprite()override;
	void PostUpdate()override;
	void Init()override;

private:

	Math::Vector3				m_scorePos;
	Math::Vector3				m_scoreScale;
	std::shared_ptr<KdTexture>	m_scoreTex = nullptr;

	int							m_score = 100;
	std::vector<int>			m_numberList;
	std::shared_ptr<KdTexture>	m_spTex = nullptr;
	Math::Vector3				m_pos;
	Math::Vector3				m_scale;
};