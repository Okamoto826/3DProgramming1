#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Stage/Stage.h"
#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Player/Player.h"

void GameScene::Event()
{
}

void GameScene::Init()
{
	//===================================================================
	// ステージ初期化
	//===================================================================
	std::shared_ptr<Stage> _stage = std::make_shared<Stage>();
	_stage->Init();
	AddObject(_stage);

	//===================================================================
	// プレイヤー初期化
	//===================================================================
	std::shared_ptr<Player> _player = std::make_shared<Player>();
	_player->Init();
	AddObject(_player);

	//===================================================================
	// カメラ初期化
	//===================================================================
//	std::shared_ptr<FPSCamera>		_camera = std::make_shared<FPSCamera>();
	std::shared_ptr<TPSCamera>		_camera = std::make_shared<TPSCamera>();
	//	std::shared_ptr<CCTVCamera>		_camera = std::make_shared<CCTVCamera>();
	_camera->Init();
	AddObject(_camera);
}
