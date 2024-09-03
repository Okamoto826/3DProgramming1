#pragma once

#include"../BaseScene/BaseScene.h"

class Time;

class GameScene : public BaseScene
{
public :

	GameScene() {}
	~GameScene() {}

	void Init() override;

private:

	void Event() override;

	std::shared_ptr<Time> m_time;
};
