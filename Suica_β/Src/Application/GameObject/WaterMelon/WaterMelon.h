#pragma once

class WaterMelon :public KdGameObject
{
public:

	WaterMelon() {}
	~WaterMelon()override {}

	void Update()override;
	void PostUpdate()override;
	void Init()override;
	void DrawLit()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

	void SetTarget(std::weak_ptr<KdGameObject> a_spTarget) { m_wpTarget = a_spTarget; }

private:

	enum Turn
	{
		turn01 = 1 << 0,
		turn02 = 1 << 1,
		turn03 = 1 << 2,
		turn04 = 1 << 3,
	};

	void TurnAnimation(WaterMelon::Turn _turn, WaterMelon::Turn _turnNext, float _maxAng, bool _dir);

	Math::Vector3 m_pos = Math::Vector3::Zero;

	Math::Vector3 m_dist = Math::Vector3::Zero;

	//スイカ半分のデータ
	struct Data
	{
		std::shared_ptr<KdModelWork> spModel = nullptr;

		Math::Matrix mat = Math::Matrix::Identity;

		Math::Matrix ScaleMat = Math::Matrix::Identity;

		Math::Matrix LocalPos = Math::Matrix::Identity;

		Math::Matrix Rotation = Math::Matrix::Identity;

		Math::Vector3 pos = Math::Vector3::Zero;

		float deg = 0;
	};

	Data m_left;
	Data m_right;

	//プレイヤー情報
	std::weak_ptr<KdGameObject> m_wpTarget;

	// モデルサイズ
	float m_modelSize = 2.0f;

	// エフェクトサイズ
	float m_effSize = 1.0f;

	// 回転スピード
	float angSpeed = 10.0f;
	// 転がって移動するスピード
	float posSpeed = 0.15f;

	UINT m_turnFlg = 0;
	// アニメーションフラグ
	bool m_animation01 = false;
	bool m_animation02 = false;

	// エフェクトフラグ
	bool m_effFlg = false;

	// キーフラグ
	bool m_lKeyFlg = false;
	bool m_rKeyFlg = false;

	// フレーム
	int m_frame;
};