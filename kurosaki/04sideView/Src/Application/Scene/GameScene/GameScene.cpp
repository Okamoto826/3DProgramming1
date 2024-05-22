#include "GameScene.h"

#include"../SceneManager.h"
#include"../../Object/Stage/Stage.h"
#include"../../Object/Player/Player.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	// カメラ処理
	static float x = 0;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		x -= 0.1f;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		x += 0.1f;
	}

	

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(x, 2, -5);
	m_camera->SetCameraMatrix(transMat);
}

void GameScene::Init()
{
	//カメラ
	m_camera = std::make_unique<KdCamera>();
	

	// ①ポインタを作成(このポインタ何も入っていない)
	std::shared_ptr<Stage> stage;

	// ②領域を確保し、アドレスを①に代入
	// 実体化
	stage = std::make_shared<Stage>();

	// ③実体化した②をオブジェクトリストに格納
	m_objList.push_back(stage);

	// プレイヤー＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();
	m_objList.push_back(player);
}
