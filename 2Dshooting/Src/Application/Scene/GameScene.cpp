	#include "GameScene.h"
#include "../Object/Player/Player.h"
#include "../Object/Enemy/Enemy.h"
#include "../Object/Bullet/Bullet.h"

void GameScene::PreUpdate()
{
	// Updateの前の更新処理
	// オブジェクトリストの整理をしておく
	
	// イテレータとは　…　コンテナクラス用のポインタ（のようなモノ）
	// コンテナを先頭から末尾までたどる際に使用

	// イテレーター作成　べた書き
	//std::vector<std::shared_ptr<BaseObject>>::iterator it;
	//it = m_objList.begin();	// 先頭の要素を返す

	// イテレーター作成 auto版 
	auto it = m_objList.begin();

	while (it != m_objList.end())	// 末尾の要素だったらループを抜ける
	{								// end()は最後の要素の１個後ろ（次）を返す。
		// オブジェクトの有効チェック
		if (!(*it)->GetAliveFlg())	// (*it)→コンテナの中の番地が取れる。ダブポ。
		{
			// 無効なオブジェクトをリストから削除
			it = m_objList.erase(it);	// 戻り値に次の番地を返してくれる。
		}
		else
		{
			it++;	// 次の要素へイテレータを進める
		}
	}
	// ↑の後には有効なオブジェクトだけのリストになっている
}

void GameScene::Update()
{
	//m_player->Update();

	//m_enemy->Test();
	//m_enemy->Update();
	//if (rand() % 100 == 3)
	////if (rand() % 2 == 0)
	//{
	//	std::shared_ptr<Enemy> enemy;
	//	enemy = std::make_shared<Enemy>();
	//	enemy->Init();
	//	//enemy->SetPos(rand() % (1280-32) - (640+32), rand() % (720-32) - (360+32));
	//	enemy->SetPos(640-32, 360-32);
	//	enemy->SetMovePow(-2.0f, -2.0f);
	//	//enemy->SetMovePow({ 0.0f, -1.0f, 0.0f });
	//	enemy->SetOwner(this);
	//	m_objList.push_back(enemy);
	//}

	// 全オブジェクトの更新関数を一括で呼ぶ
	for (int i = 0; i < m_objList.size(); i++)
	{
		m_objList[i]->Update();
	}
}

void GameScene::Draw()
{
	//m_player->Draw();

	//m_enemy->Draw();

	// 全オブジェクトの更新関数を一括で呼ぶ
	// 範囲ベースfor
	/*for (auto& obj : m_objList)
	{
		obj->Draw();
	}*/
	for (int i = 0; i < m_objList.size(); i++)
	{
		m_objList[i]->Draw();
	}
}

void GameScene::Init()
{
	// プレイヤー
	//m_player = new Player;				// 生ポ　　インスタンス生成
	//m_player = std::make_shared<Player>();	// スマポ　インスタンス生成
	//m_player->Init();
	//m_player->SetOwner(this);

	// エネミー
	//m_enemy = std::make_shared<Enemy>();	// BaseObject→Enemyの順でコンストラクタが呼ばれる。
	//m_enemy->Init();

	// ローカル変数として作成してからpush_back！！
	// == プレイヤー ============
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();
	player->Init();
	player->SetOwner(this);
	m_objList.push_back(player);

	// == エネミー ============
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<Enemy> enemy;
		enemy = std::make_shared<Enemy>();
		enemy->Init();
		enemy->SetPos(1000 + i*200.0f, 0.0f);
		//enemy->SetMovePow({ 0.0f, -1.0f, 0.0f });
		enemy->SetOwner(this);
		m_objList.push_back(enemy);
	}
}

void GameScene::Release()
{
	//delete m_player;	// 生ポ　インスタンス破棄 スマポのインスタンス破棄はない
}
