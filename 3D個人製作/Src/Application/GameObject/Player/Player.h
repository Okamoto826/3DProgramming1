#pragma once

class TPSCamera;
class Player :public KdGameObject
{
public:
	Player() { Init(); }
	~Player() {}

	void Init()override;
	void Update()override;
	void DrawLit()override;
	void SetCamera(std::shared_ptr<TPSCamera>_camera)
	{
		m_camera = _camera;
	}

private:
	std::shared_ptr<KdModelData> m_model = nullptr;
	std::weak_ptr<TPSCamera> m_camera;
	Math::Vector3 m_pos;
	float m_angle = 180;
};