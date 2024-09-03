#pragma once

class Bomb :public KdGameObject
{
public:

	Bomb() {}
	~Bomb()override {}

	void Update()override;
	void PostUpdate()override;
	void Init()override;
	void DrawLit()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

private:

	std::shared_ptr<KdModelWork> m_spModel = nullptr;

	Math::Vector3 m_pos = Math::Vector3::Zero;

	Math::Vector3 m_dist = Math::Vector3::Zero;

	// モデルサイズ
	float m_modelSize = 2.0f;

	// エフェクトサイズ
	float m_effSize = 2.0f;

	int m_frame = 0;

	bool m_animation01 = false;
	bool m_animation02 = false;

	bool m_rKeyFlg = false;
	bool m_lKeyFlg = false;

	// エフェクト用フラグ
	bool m_effect = false;


	//デバッグ用=================================
	bool flg = false;
};