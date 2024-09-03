#pragma once

#include "../EffectBase.h"

class Explosion:public EffectBase
{
public:

	Explosion() {}
	~Explosion()override {}

	void Update()override;
	void Init()override;
};