#pragma once
#include"../BaseChara.h"

class CrystalMauler :public BaseChara
{
public:
	CrystalMauler() { Init(); }
	~CrystalMauler() override {}

	void Update() override;

	void Init() override;

	void ChangeAnimation();

private:
};