#include "GameScene.h"
#include"../SceneManager.h"

#include"../../GameObject/Ground/Ground.h"
#include"../../GameObject/Tank/Tank.h"
#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"

void GameScene::Event()
{
}

void GameScene::Init()
{
	std::shared_ptr<TPSCamera> camera;
	camera = std::make_shared<TPSCamera>();
	m_objList.push_back(camera);

	std::shared_ptr<Ground> ground;
	ground = std::make_shared<Ground>();
	m_objList.push_back(ground);

	std::shared_ptr<Tank> tank;
	tank = std::make_shared<Tank>();
	m_objList.push_back(tank);
}
