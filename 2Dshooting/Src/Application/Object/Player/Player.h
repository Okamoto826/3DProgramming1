#pragma once

// 基本的にヘッダーファイルの中で
// 別のヘッダーファイルをインクルードするのはNG
// 継承元クラスのヘッダーのみインクルードが必須なので可
class GameScene;

class Player 
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
	void Update();
	void Draw();
	void Init();
	void BreakEnemy();

	void OnHit();
	float GetScale() { return m_scale; };
	void Test() { return; }
	Math::Vector3 GetPos() { return m_pos; }
	void SetOwner(GameScene* _pOwner) { m_pOwner = _pOwner; }

private:
	NowMode m_nowMode;
	KdTexture m_skillTex;
	KdTexture m_downTex;
	int m_breakCount;
	int m_lifeGurd;
	Math::Matrix  m_scaleMat;

	int m_drawCount;

	GameScene* m_pOwner = nullptr;

	KdTexture		m_tex;

	Math::Vector3	m_pos;
	Math::Vector3	m_rad;
	Math::Matrix	m_mat;
	float m_scale;

	bool			m_bAlive = true;

	void Release() ;

};