#pragma once

class Player :public KdGameObject
{
public:

	enum DirType
	{
		Up		=1<<0,	// 上
		Down	=1<<1,	// 下
		Left	=1<<2,	// 左
		Right	=1<<3,	// 右
	};

	// アニメーション情報
	struct AnimationInfo
	{
		int start;		// 開始コマ
		int end;		// 終了コマ
		float count;	// 現在のコマ数カウント
		float speed;	// アニメーションの速度
	};

	Player() {}
	~Player() override {}

	void Update() override;
	void PostUpdate() override;

	void GenerateDepthMapFromLight() override;
	void DrawLit() override;

	void Init() override;

private:

	void ChangeAnimation();

	// 板ポリゴン
	KdSquarePolygon m_polygon;

	// アニメーション情報
	AnimationInfo m_animationInfo;

	// キャラが向いてる方向種類 ビット管理
	UINT m_dirType;

	Math::Vector3 m_pos;
	Math::Vector3 m_move;

	float m_speed;

	// 攻撃方向
	Math::Vector3 m_attackDir;

	bool m_keyFlg = false;

	float m_gravity;
};