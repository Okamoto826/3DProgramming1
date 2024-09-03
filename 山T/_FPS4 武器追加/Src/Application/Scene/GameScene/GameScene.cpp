#include "GameScene.h"
#include"../SceneManager.h"
#include "../../main.h"

// FPSカメラ
#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"

// 地形
#include "../../GameObject/Terrains/Terrain/Terrain.h"
#include"../../GameObject/Terrains/WoodenBox/WoodenBox.h"

// プレイヤー
#include "../../GameObject/Character/Player/Player.h"

// 武器
#include"../../GameObject/Wapon/Pistol/Pistol.h"
#include"../../GameObject/UI/Reticle/Reticle.h"

void GameScene::ImGuiProcess()
{
	// デバッグウィンドウ
	ImGui::SetNextWindowPos(ImVec2(1280 - 360, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(100, 30), ImGuiCond_FirstUseEver);

	if (ImGui::Begin("Debug Window"))
	{
		POINT mousePos = {};
		GetCursorPos(&mousePos);
		ImGui::Text("mousePos(Screen) : %d, %d", mousePos.x, mousePos.y);
		ScreenToClient(Application::Instance().GetWindowHandle(), &mousePos);
		ImGui::Text("mousePos(Client) : %d, %d", mousePos.x, mousePos.y);
	}
	ImGui::End();
}

void GameScene::Event()
{
	
}

void GameScene::Init()
{
	// カーソルを非表示
	//ShowCursor(false);

	// 地形
	std::shared_ptr<Terrain> _terrain = std::make_shared<Terrain>();
	_terrain->Init();
	m_objList.push_back(_terrain);


	std::shared_ptr<WoodenBox> _woodenbox;
	// 木箱
	for (int i = 0; i < 5; i++)
	{
		_woodenbox = std::make_shared<WoodenBox>();
		_woodenbox->Init();
		_woodenbox->SetPos({ -60.0f + 30.0f * i, 0.f, 50.0f });
		m_objList.push_back(_woodenbox);
	}
	
	// カメラ
	std::shared_ptr<FPSCamera> _camera = std::make_shared<FPSCamera>();
	_camera->Init();
	m_objList.push_back(_camera);

	m_wpCamera = _camera;

	// プレイヤー
	std::shared_ptr<Player> _player = std::make_shared<Player>();
	_player->Init();
	_player->SetCamera(_camera);
	m_objList.push_back(_player);

	// ピストル
	std::shared_ptr<Pistol> _pistol = std::make_shared<Pistol>();
	_pistol->Init();
	_pistol->SetParent(_player);
	m_objList.push_back(_pistol);

	//レティクル
	std::shared_ptr<Reticle> _reticle = std::make_shared<Reticle>();
	_reticle->Init();
	m_objList.push_back(_reticle);

	_camera->SetTarget(_player);
}
