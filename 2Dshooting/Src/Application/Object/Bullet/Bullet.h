#pragma once

#include "../BaseObject.h"

class GameScene;

class Bullet :public BaseObject
{
	enum NowMode
	{
		idle,
		Exp,
	};
public:
	Bullet() {};
	~Bullet() { Release(); }

	void Update() override;
	void Draw() override;
	void Init(Math::Vector3 _pos);

	void SetOwner(GameScene* _pOwner) { m_pOwner = _pOwner; }
	void SetScale(float _scale) { m_scale = _scale+0.5f; }

	void OnHit();

private:

	KdTexture m_expTex;
	GameScene* m_pOwner = nullptr;
	Math::Matrix m_scaleMat;
	Math::Vector3	m_movePow;
	NowMode m_nowMode = idle;
	int m_drawCount = 0;
	int m_lifeCount;

	void Release() override;
};