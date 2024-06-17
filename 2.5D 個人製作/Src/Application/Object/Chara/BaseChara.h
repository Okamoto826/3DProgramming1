#pragma once
class BaseChara :public KdGameObject
{
public:

	enum NowCharaSit
	{
		Idle	=1<<0,
		Move	=1<<1,
		Skill	=1<<2,
		Skill2	=1<<3,
		Down	=1<<4
	};

	// アニメーション情報
	struct AnimationInfo
	{
		int start;		// 開始コマ
		int end;		// 終了コマ
		float count;	// 現在のコマ数カウント
		float speed;	// アニメーションの速度
	};

	BaseChara() { Init(); }
	~BaseChara() override {}

	void Update() override;
	void PostUpdate() override;

	void GenerateDepthMapFromLight() override;
	void DrawLit() override;

	void Init() override;

private:

protected:

	
	// 板ポリゴン
	KdSquarePolygon m_polygon;

	// アニメーション情報
	AnimationInfo m_animationInfo;

	// キャラの状態 ビット管理
	UINT m_nowSit;

	Math::Vector3 m_pos;
	Math::Vector3 m_dir;
	int m_hp;
	int m_hpMax;
	int m_atack;
	int m_atack2;

	float m_speed;
};