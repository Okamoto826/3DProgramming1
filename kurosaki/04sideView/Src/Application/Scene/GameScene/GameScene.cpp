#include "GameScene.h"

#include"../SceneManager.h"
#include"../../Object/Stage/Stage.h"
#include"../../Object/Player/Player.h"
#include"../../Object/Back/Back.h"
#include"../../Object/Stage/ship.h"
#include"../../Object/Cannon/Cannon.h"
#include"../../Object/Enemy/Enemy.h"
#include"../../Object/UI/UI.h"

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

	// 被写界深度
	//m_camera->SetFocus(5.f, 2.f, 8.f);

	// ブルーム
	//KdShaderManager::Instance().m_postProcessShader.SetBrightThreshold(0.7f);

}

void GameScene::Init()
{
	//カメラ
	m_camera = std::make_unique<KdCamera>();

	// 環境設定=================================
	//①平行光（ディレクションライト）
	KdShaderManager::Instance().WorkAmbientController().SetDirLight({ 0,-1,0.1 }, { 3,3,3 });

	//②フォグ（霧）												距離　　高さ
	KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, false);
	//																		色		濃さ
	KdShaderManager::Instance().WorkAmbientController().SetDistanceFog({ 0.3,0,0.6 }, 0.1);
	//																	色　	上	下	距離	
	KdShaderManager::Instance().WorkAmbientController().SetheightFog({ 1,1,1 }, 0, -2, 0);

	//③環境光（アンビエントライト）
	//画面が暗すぎるときに調整する（デフォルト0.3）
	//KdShaderManager::Instance().WorkAmbientController().SetAmbientLight({ 1, 1, 1, 1 });


	// ①ポインタを作成(このポインタ何も入っていない)
	std::shared_ptr<Stage> stage;

	// ②領域を確保し、アドレスを①に代入
	// 実体化
	stage = std::make_shared<Stage>();

	// ③実体化した②をオブジェクトリストに格納
	m_objList.push_back(stage);

	for (int i = 0; i < 10; i++)
	{
	
		stage = std::make_shared<Stage>();
		stage->SetPos({ 0,-2,3 + float(3 * i) });
		m_objList.push_back(stage);
	}

	for (int i = 0; i < 5; i++)
	{

		stage = std::make_shared<Stage>();
		stage->SetPos({ 0,-2.0f + 5.0f * i,0 });
		m_objList.push_back(stage);
	}
	// プレイヤー＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();
	m_objList.push_back(player);
	m_player = player;

	std::shared_ptr<Enemy> enemy;
	enemy = std::make_shared<Enemy>();
	for (int i = 0; i < 5; i++)
	{
		enemy = std::make_shared<Enemy>();
		enemy->SetPos({-25.f + (1.f * i), 0, 0});
		m_objList.push_back(enemy);
	}
	

	std::shared_ptr<Back> back;
	back = std::make_shared<Back>();
	m_objList.push_back(back);

	/*std::shared_ptr<Ship> ship;
	ship = std::make_shared<Ship>();
	m_objList.push_back(ship);*/

	std::shared_ptr<Cannon> cannon;
	cannon = std::make_shared<Cannon>();
	m_objList.push_back(cannon);

	std::shared_ptr<UI> ui;
	ui = std::make_shared<UI>();
	m_objList.push_back(ui);
}
