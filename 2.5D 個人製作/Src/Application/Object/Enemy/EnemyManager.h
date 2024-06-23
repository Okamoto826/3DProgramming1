#pragma once

class EnemyManager :public KdGameObject
{
public:
	EnemyManager() { Init(); };
	~EnemyManager() {};
	void Init()override;
	void Update()override;
private:

	int m_mushRoom = 0;
	int m_goblin = 0;

	bool keyFlg = false;
};
