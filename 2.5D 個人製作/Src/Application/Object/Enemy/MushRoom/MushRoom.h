#pragma once
#include"../EnemyBase.h"

class MushRoom :public EnemyBase
{
public:
	MushRoom() { Init(); }
	~MushRoom() override {}

	void Update() override;
	void PostUpdate() override;

	void Init() override;

	void ChangeAnimation() override;

	void Atack() override;

	void OnHit(float _dmg) override;
private:
};