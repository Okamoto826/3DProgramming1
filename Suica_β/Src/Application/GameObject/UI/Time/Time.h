#pragma once

class Time
	:public KdGameObject
{
public:

	Time() {}
	~Time()override {}

	void PostUpdate()override;
	void DrawSprite()override;
	void Init()override;

	void Start()
	{
		m_startFlg = true;
	}

	bool GameEnd()
	{
		if (m_second == 0)return true;
		else return false;
	}

private:

	std::shared_ptr<KdTexture>	m_colonTex;


	std::shared_ptr<KdTexture>	m_spTex = nullptr;
	Math::Vector3				m_pos;
	Math::Vector3				m_scale = Math::Vector3::One;

	bool						m_startFlg = false;
	std::vector<UINT>			m_numberList;

	int							m_frame = 60;
	int							m_second = 60;
};