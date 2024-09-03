#pragma once

class Stage : public KdGameObject
{
public:
	Stage() {}
	virtual ~Stage()		override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;

private:
	std::shared_ptr<KdModelWork> m_spModel = nullptr;

};