#pragma once
#include"../BaseChara.h"

class GroundMonk :public BaseChara
{
public:
	GroundMonk() { Init(); }
	~GroundMonk() override {}

	void Update() override;

	void Init() override;

	void ChangeAnimation();

	void Atack() override;

	void OnHit(float _dmg)override;
private:
};