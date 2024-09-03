#pragma once

class Club :public KdGameObject
{
public:
	enum NowSit
	{
		Idle,
		LAtack,
		RAtack,
	};

	Club() { Init(); }
	~Club() override {}
	void Init()override;
	void Update() override;
	void DrawLit()override;
	void ResetPos();

private:
	// モデル情報
	std::shared_ptr<KdModelWork> m_spModel = nullptr;

	Math::Vector3 m_parentPos;
	Math::Vector3 m_basePos;
	Math::Vector3 m_clubPos;
	float m_baseXRot;
	float m_baseYRot;
	float m_XRot;
	float m_YRot;
	int m_coolTimer;
	bool LKeyFlg = false;
	bool RKeyFlg = false;
	bool m_XFlg = false;
	NowSit m_nowSit;
};