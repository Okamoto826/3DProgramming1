#pragma once

class Player;

class Enemy :public KdGameObject
{
public:

	enum DirType
	{
		Up = 1 << 0,	// 上
		Down = 1 << 1,	// 下
		Left = 1 << 2,	// 左
		Right = 1 << 3,	// 右
	};

	// アニメーション情報
	struct AnimationInfo
	{
		int Run[4] = { 3,4,3,5 };
		float count;	// 現在のコマ数カウント
		float speed;	// アニメーションの速度
	};

	Enemy() {}
	~Enemy() override {}

	void Update() override;
	void PostUpdate() override;

	void GenerateDepthMapFromLight() override;
	void DrawLit() override;

	void Init() override;

	void SetPos(const Math::Vector3& pos) override{ m_pos = pos; };
	void SetPlayer(std::weak_ptr<Player> _player);

private:

	void ChangeAnimation();

	// 板ポリゴン
	std::shared_ptr<KdSquarePolygon> m_polygon = nullptr;

	// アニメーション情報
	AnimationInfo m_animationInfo;

	// キャラが向いてる方向種類 ビット管理
	UINT m_dirType;

	Math::Vector3 m_pos;
	Math::Vector3 m_move;
	bool m_chaseFlg = false;
	float m_searchArea = 3.0f;

	float m_speed;

	float m_gravity;

	std::weak_ptr<Player> m_player;
};
