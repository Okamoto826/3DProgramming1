#include "GameScene.h"
#include"../SceneManager.h"
#include"../../main.h"
#include"../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../GameObject/Terrains/Terrain/Terrain.h"
#include"../../GameObject/Character/Player/Player.h"

void GameScene::Event()
{
}

void GameScene::Init()
{
	// カーソルを非表示
	ShowCursor(false);

	//===================================================================
	// ステージ初期化
	//===================================================================
	std::shared_ptr<Terrain> _terrain = std::make_shared<Terrain>();
	_terrain->Init();
	m_objList.push_back(_terrain);

	//===================================================================
	// キャラクター初期化
	//===================================================================
	std::shared_ptr<Player> _player = std::make_shared<Player>();
	_player->Init();
	m_objList.push_back(_player);

	//===================================================================
	// カメラ初期化
	//===================================================================
	std::shared_ptr<FPSCamera>_camera = std::make_shared<FPSCamera>();
	_camera->Init();
	_camera->SetTarget(_player);
	_player->SetCamera(_camera);
	m_objList.push_back(_camera);
}
