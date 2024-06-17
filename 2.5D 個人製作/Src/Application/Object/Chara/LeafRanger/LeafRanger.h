#pragma once
#include"../BaseChara.h"

class LeafRanger :public BaseChara
{
public:
	LeafRanger() { Init(); }
	~LeafRanger() override {}

	void Update() override;

	void Init() override;

	void ChangeAnimation();

private:
};