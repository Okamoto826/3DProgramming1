#pragma once
#include"../EnemyBase.h"

class Goblin :public EnemyBase
{
public:
	Goblin() { Init(); }
	~Goblin() override {}

	void Update() override;
	void PostUpdate() override;

	void Init() override;

	void ChangeAnimation() override;

	void Atack() override;

	void OnHit(float _dmg) override;
private:
};