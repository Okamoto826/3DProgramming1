#pragma once

class TPSCamera;
class Tank :public KdGameObject
{
public:
	Tank() { Init(); }
	~Tank(){}

	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void SetCamera(std::shared_ptr<TPSCamera>_camera)
	{
		m_camera = _camera;
	}

private:
	std::shared_ptr<KdModelData> m_model = nullptr;
	std::weak_ptr<TPSCamera> m_camera;
	float m_angle = 0;
	Math::Vector3 m_pos;
	bool m_atkFlg = false;
};