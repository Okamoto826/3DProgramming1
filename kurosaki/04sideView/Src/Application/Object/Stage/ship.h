#pragma once

class Ship :public KdGameObject
{
public:
	Ship() { Init(); }
	~Ship() {}

	void Init()override;
	void DrawLit()override;
private:

	std::shared_ptr<KdModelData> m_model;

};