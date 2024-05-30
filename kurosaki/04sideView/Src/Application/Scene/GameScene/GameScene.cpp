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
	// ここでプレイヤーの座標が取得できれば勝ち
	// ①オブジェクトリストからプレイヤー情報を取得
	// リストからプレイヤーを探す手間がかかる
	// ②プレイヤー情報は個別で持つ
	// メモリ食います
	// 今回は②を使う
	Math::Vector3 playerPos;
	if (m_player.expired() == false)
	{
		playerPos = m_player.lock()->GetPos();
	}


	Math::Matrix transMat;
	Math::Vector3 cameraPos = { 3.0f,1.5f,-5.0f };
	transMat = Math::Matrix::CreateTranslation(cameraPos + playerPos);
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
	m_player = player;
}
