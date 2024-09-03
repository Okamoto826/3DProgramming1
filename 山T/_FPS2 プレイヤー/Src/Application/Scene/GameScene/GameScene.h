#pragma once

#include"../BaseScene/BaseScene.h"

class CameraBase;

class GameScene : public BaseScene
{
public :

	GameScene() { Init(); }
	~GameScene() {}

	void ImGuiProcess() override;

private:

	void Event() override;
	void Init() override;

	std::weak_ptr<CameraBase> m_wpCamera;
};