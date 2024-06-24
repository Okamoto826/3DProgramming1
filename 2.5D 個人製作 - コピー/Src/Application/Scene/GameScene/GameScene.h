#pragma once

#include"../BaseScene/BaseScene.h"
class CharaManager;
class GameScene : public BaseScene
{
public :

	GameScene() { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init() override;

	Math::Vector3 cameraPos;
};
