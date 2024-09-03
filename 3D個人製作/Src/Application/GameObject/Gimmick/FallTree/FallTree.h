#pragma once

class FallTree :public KdGameObject
{
public:
	FallTree() {}
	~FallTree()			override {}

	void Init()				override;
	void Update()			override;

	bool m_fallFlg = false;
};