#include "GameScene.h"
#include"../SceneManager.h"

#include"../../GameObject/Ground/Ground.h"
#include"../../GameObject/Tank/Tank.h"
#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include"../../GameObject/Enemy/moto.h"
#include"../../GameObject/Enemy/yama.h"

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
	tank->SetCamera(camera);

	std::shared_ptr<Moto> moto;
	moto = std::make_shared<Moto>();
	moto->SetPos({ 10.f,0.f,10.f });
	moto->SetTarget(tank);
	m_objList.push_back(moto);

	std::shared_ptr<Yama> yama;
	yama = std::make_shared<Yama>();
	yama->SetPos({ -10.f,0.f,10.f });
	yama->SetTarget(tank);
	m_objList.push_back(yama);

	camera->SetTarget(tank);
}
