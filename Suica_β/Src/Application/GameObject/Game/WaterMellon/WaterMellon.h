#pragma once

class WaterMellon :public KdGameObject
{
public:

	WaterMellon(){}
	~WaterMellon(){}

	void Init()override;
	void Update()override;
	void DrawLit()override;
	void GenerateDepthMapFromLight()override;

	void Emit(Math::Vector3 a_pos) { m_pos = a_pos; }
private:

	std::shared_ptr<KdModelData> m_spModel;
	Math::Vector3 m_pos;
};