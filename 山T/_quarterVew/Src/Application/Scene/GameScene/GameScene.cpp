#include "GameScene.h"
#include"../SceneManager.h"

#include"../../Object/BackGround/BackGround.h"
#include"../../Object/Ground/Ground.h"
#include"../../Object/Player/Player.h"
#include"../../Object/Enemy/Enemy.h"


void GameScene::Event()
{
	// プレーヤーの座標を取得する
	Math::Vector3 playerPos = {};
	// weak_ptrで所持している m_player が有効かどうかを調べる
	// expired() …期限切れならtrueを返す
	if (m_player.expired() == false)
	{
		playerPos = m_player.lock()->GetPos();
	}

	// カメラの座標行列を作成
	Math::Matrix transmat = Math::Matrix::CreateTranslation
	(playerPos.x + 0, playerPos.y + 3, playerPos.z + -3);

	// カメラの回転行列を作成
	Math::Matrix rotmat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(30.0f));

	// 行列を合成
	Math::Matrix mat = rotmat * transmat;
	
	// カメラに行列をセット
	// この時点では画面には反映されない
	m_camera->SetCameraMatrix(mat);
}

void GameScene::Init()
{
	// カメラ　生成＆視野角設定
	m_camera = std::make_unique<KdCamera>();	// 1 メモリ確保
	m_camera->SetProjectionMatrix(60);			// 2 視野角設定

	// 背景
	std::shared_ptr<BackGround> back;	
	back = std::make_shared<BackGround>();	// 1 メモリ確保
	back->Init();							// 2 初期化
	m_objList.push_back(back);				// 3 リストへ追加

	// 地面
	std::shared_ptr<Ground> ground;			
	ground = std::make_shared<Ground>();	// 1 メモリ確保
	ground->Init();							// 2 初期化
	m_objList.push_back(ground);			// 3 リストへ追加

	// プレイヤー
	std::shared_ptr<Player> player;			
	player = std::make_shared<Player>();	// 1 メモリ確保
	player->Init();							// 2 初期化
	m_objList.push_back(player);			// 3 リストへ追加

	// プレイヤーの状態を保持しておく
	m_player = player;

	// 敵
	std::shared_ptr<Enemy> enemy;
	for (int i = 0; i < 10; i++)
	{
		
		enemy = std::make_shared<Enemy>();	// 1 メモリ確保
		enemy->Init();						// 2 初期化
		enemy->SetPos({ -50.0f + 10.0f * i, 0.0f, 20.0f});
		enemy->SetPlayer(m_player);
		m_objList.push_back(enemy);			// 3 リストへ追加
	}

	
}	
		
