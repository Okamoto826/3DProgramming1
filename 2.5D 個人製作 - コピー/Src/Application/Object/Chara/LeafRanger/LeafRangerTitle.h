#pragma once
#include"../BaseChara.h"

class LeafRangerTitle :public BaseChara
{
public:
	LeafRangerTitle() { Init(); }
	~LeafRangerTitle() override {}

	void Update() override;

	void Init() override;

	void ChangeAnimation() override;

	
private:
};