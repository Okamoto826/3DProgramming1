#pragma once
#include"../BaseChara.h"

class CrystalMauler :public BaseChara
{
public:
	CrystalMauler() { Init(); }
	~CrystalMauler() override {}

	void Update() override;

	void Init() override;

	void OnHit(float _dmg)override;

	void Atack() override;

	void ChangeAnimation();

private:
};