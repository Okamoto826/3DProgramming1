#pragma once
#include "../ResultBase.h"

class ResultBack : public ResultBase
{
public:
	ResultBack() {}
	~ResultBack()override {}

	void Init()override;
	void Update()override;

private:

	const std::string BackPng = "Asset/Textures/Result/back.png";

	bool m_b_titleBackKey = true;
	

	bool m_b_backAlphaStart = true;
	const float StartBackAlphaTrans = 0.02f;

	const float BackMinAlpha = 0.4f;
	const float BackAlphaDegRange = 3.f / 10.f;
	const float BackAlphaDegTrans = 3.f;
	float m_backAlphaDeg = MinDeg;

};



