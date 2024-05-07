#pragma once

// 基本的にヘッダーファイルの中で
// 別のヘッダーファイルをインクルードするのはNG
// 継承元クラスのヘッダーのみインクルードが必須なので可
#include "../BaseObject.h"

class GameScene;

class Player :public BaseObject
{
public:

	
	Player() {};
	~Player() { Release(); };

	enum NowMode
	{
		idle,
		skill,
		down,
	};

	// 基底クラスの仮想関数をオーバーライド
	// override指定子はなくてもオーバーライドはされるが
	// override可能かどうかを判別する目的で付けるべき（可読性の問題もある）
	// overrideを書いて損はない。
	void Update() override;
	void Draw() override;
	void Init() override;
	
	void Test() { return; }

	void SetOwner(GameScene* _pOwner) { m_pOwner = _pOwner; }

private:
	NowMode m_nowMode;
	KdTexture m_skillTex;
	KdTexture m_downTex;
	
	Math::Matrix  m_scaleMat;

	int m_drawCount;

	GameScene* m_pOwner = nullptr;

	

	void Release() override;

};