#pragma once

class Player :public KdGameObject
{
public:

	Player(){}
	~Player(){}

	void Init()override;
	void Update()override;

private:

	//カウンターに応じたスピード変更用関数
	void SuccessCountFunction();

	//移動処理
	void PlayerMoving();



	//座標
	Math::Vector3 m_pos;

	//移動量
	const float m_moveAmount = 12.f;
	bool m_bMove = false;
	float m_moveCounter = 0.f;

	//スピード
	float m_speed = 0.f;

	//キーチェック
	bool m_bRight;

	//カウンター
	int m_moveDelay = 0;

	bool m_bSwing = false;

	int m_success = 0;
};