#include "GameScene.h"
#include"../SceneManager.h"
// FPSカメラ
#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../GameObject/Club/Club.h"
#include"../../GameObject/Ground/Ground.h"
#include"../../GameObject/WaterMelon/WaterMelon.h"

void GameScene::Event()
{
}

void GameScene::Init()
{
	// カメラ
	std::shared_ptr<FPSCamera> _camera = std::make_shared<FPSCamera>();
	_camera->Init();
	m_objList.push_back(_camera);

	// こん棒
	std::shared_ptr<Club> _club = std::make_shared<Club>();
	m_objList.push_back(_club);

	// スイカ
	/*std::shared_ptr<WaterMelon> _watermelon = std::make_shared<WaterMelon>();
	_watermelon->Init();
	m_objList.push_back(_watermelon);*/

	// 地面
	std::shared_ptr<Ground> ground;
	ground = std::make_shared<Ground>();	// 1 メモリ確保
	ground->Init();							// 2 初期化
	m_objList.push_back(ground);			// 3 リストへ追加


	Math::Viewport _viewPort;
	KdDirect3D::Instance().CopyViewportInfo(_viewPort);
	const int _width = _viewPort.width;
	const int _height = _viewPort.height;
	KdEffekseerManager::GetInstance().Create(_width, _height);
	KdEffekseerManager::GetInstance().SetCamera(_camera->GetCamera());
}
