#pragma once

// 基本的にヘッダーファイルの中で
// 別のヘッダーファイルをインクルードするのはNG
// 継承元クラスのヘッダーのみインクルードが必須なので可
#include "../BaseObject.h"

class GameScene;

class Enemy :public BaseObject
{
public:
	Enemy() {};
	~Enemy() { Release(); };
	enum NowMode
	{
		idle,
		skill,
		down,
	};

	void Update() override;
	void Draw() override;
	void Init() override;

	void OnHit() override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
	void SetPos(float _x, float _y) { m_pos = { _x, _y, 0.0f }; }	// SetPosをオーバーロード
	/*void SetMovePow(Math::Vector3 _move) { m_movePow = _move; }
	void SetMovePow(float _x, float _y) { m_movePow = { _x, _y, 0.0f }; }*/

	void SetOwner(GameScene* _pOwner) { m_pOwner = _pOwner; }

private:
	NowMode m_nowMode;
	KdTexture m_skillTex;
	KdTexture m_downTex;
	GameScene* m_pOwner = nullptr;
	float m_MiniX;
	int m_drawCount;
	int m_moveCount;
	Math::Vector3 m_movePow;

	void Release() override;
};