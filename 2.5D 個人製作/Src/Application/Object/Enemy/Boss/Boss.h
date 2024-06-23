#pragma once
#include"../EnemyBase.h"

class Boss :public EnemyBase
{
public:
	Boss() { Init(); }
	~Boss() override {}

	void Update() override;
	void PostUpdate() override;

	void Init() override;

	void ChangeAnimation() override;

	void Atack() override;

	void OnHit(float _dmg) override;
private:
};