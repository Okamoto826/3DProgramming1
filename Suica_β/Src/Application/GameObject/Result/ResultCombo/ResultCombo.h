#pragma once
#include "../ResultBase.h"

class ResultCombo : public ResultBase
{
public:
	ResultCombo() {}
	~ResultCombo() {}

	void Init()override;
	void Update()override;

	void SetCombo(const int combo) { m_combo = combo; }


private:
	int m_combo{};

	const std::string ComboPng = "Asset/Textures/Result/combo.png";

};





