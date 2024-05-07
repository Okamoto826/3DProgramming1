#pragma once

#include "../BaseObject.h"

class GameScene;

class EnemyBullet :public BaseObject
{
public:
	EnemyBullet() {};
	~EnemyBullet() { Release(); }

	void Update() override;
	void Draw() override;
	void Init(Math::Vector3 _pos);

	void SetMovePow(Math::Vector3 _movePow) { m_movePow = _movePow; }
	void SetOwner(GameScene* _pOwner) { m_pOwner = _pOwner; }

	void OnHit();

private:

	GameScene* m_pOwner = nullptr;

	Math::Vector3	m_movePow;

	void Release() override;
};