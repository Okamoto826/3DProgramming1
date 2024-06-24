#pragma once
class EnemyBase :public KdGameObject
{
public:

	enum NowCharaSit
	{
		Idle = 1 << 0,
		Move = 1 << 1,
		Skill = 1 << 2,
		Skill2 = 1 << 3,
		Hit = 1 << 4,
		Down = 1 << 5
	};

	// アニメーション情報
	struct AnimationInfo
	{
		int start;		// 開始コマ
		int end;		// 終了コマ
		float count;	// 現在のコマ数カウント
		int oldCount;	// 1フレーム前のコマ
		float speed;	// アニメーションの速度
	};

	EnemyBase() { Init(); }
	~EnemyBase() override {}

	virtual void Update() override;
	virtual void PostUpdate() override;

	virtual void GenerateDepthMapFromLight() override;
	virtual void DrawLit() override;

	virtual void Init() override;
	virtual void ChangeAnimation();
	virtual void Atack();
	virtual void OnHit(float _dmg)override;
private:

protected:


	// 板ポリゴン
	KdSquarePolygon m_polygon;

	// アニメーション情報
	AnimationInfo m_animationInfo;

	// キャラの状態 ビット管理
	UINT m_nowSit;
	UINT m_oldSit;

	Math::Vector3 m_pos;
	Math::Vector3 m_dir;
	int m_hp;
	int m_hpMax;
	int m_atk;
	int m_SPatk;
	int m_MP;
	int m_atkCoolTime;
	float d;
	float m_gravity;
	float m_speed;
};