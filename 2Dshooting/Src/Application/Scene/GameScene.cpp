	#include "GameScene.h"
#include "../Object/Player/Player.h"
#include "../Object/Enemy/Enemy.h"
#include "../Object/Bullet/Bullet.h"
#include "../Object/Bullet/EnemyBullet.h"

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
	//if (rand() % 2 == 0)
	if (Timer > 2100)
	{
		if (rand() % 100 < 2)
		{
			std::shared_ptr<Enemy> enemy;
			enemy = std::make_shared<Enemy>();
			enemy->Init();
			enemy->SetPos(float(720 + 20 * rand() % 20), float(rand() % 600 - 300));
			enemy->SetOwner(this);
			m_objList.push_back(enemy);
		}
	}
	if (Timer > 1800)
	{
		if (rand() % 100 < 1)
		{
			std::shared_ptr<Enemy> enemy;
			enemy = std::make_shared<Enemy>();
			enemy->Init();
			enemy->SetPos(float(720 + 20 * rand() % 20), float(rand() % 600 - 300));
			enemy->SetOwner(this);
			m_objList.push_back(enemy);
		}
	}

	else if(Timer>900)
	{
		if (rand() % 150 < 1)
		{
			std::shared_ptr<Enemy> enemy;
			enemy = std::make_shared<Enemy>();
			enemy->Init();
			enemy->SetPos(float(720 + 20 * rand() % 20), float(rand() % 600 - 300));
			enemy->SetOwner(this);
			m_objList.push_back(enemy);
		}
	}
	
	
	else 
	{
		if (rand() % 200 < 1)
		{
			std::shared_ptr<Enemy> enemy;
			enemy = std::make_shared<Enemy>();
			enemy->Init();
			enemy->SetPos(float(720 + 20 * rand() % 20), float(rand() % 600 - 300));
			enemy->SetOwner(this);
			m_objList.push_back(enemy);
		}
	}

	m_player->Update();
	if (GetAsyncKeyState('T'))clearFlg = true;
	
	if (clearFlg == false&&DeathFlg==false)
	{
		// 全オブジェクトの更新関数を一括で呼ぶ
		for (int i = 0; i < m_objList.size(); i++)
		{
			m_objList[i]->Update();
		}

	}
	if (clearFlg == true||DeathFlg==true)
	{
		m_mat = Math::Matrix::CreateTranslation(m_pos);
	}
	Timer++;

	for (int i = 0; i < 2; i++)
	{
		m_back[i].m_pos.x -= 4;
		if(m_back[i].m_pos.x < -1276)m_back[i].m_pos.x = 1280;
		m_back[i].m_mat = Math::Matrix::CreateTranslation(m_back[i].m_pos);
	}
}

void GameScene::Draw()
{
	for (int i = 0; i < 2; i++)
	{
		Math::Rectangle rc;
		KdShaderManager::Instance().m_spriteShader.SetMatrix(m_back[i].m_mat);

		rc = { 0, 0, 1280, 720 };
		
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_back[i].m_tex, 0, 0, 1280, 720, &rc);
		
	}
	if(clearFlg==false&&DeathFlg==false)
	{
		for (int i = 0; i < m_objList.size(); i++)
		{
			m_objList[i]->Draw();
		}
	}
	m_player->Draw();
	if (clearFlg == true) 
	{
		Math::Rectangle rc;
		KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);

		rc = { 0, 0, 875, 122 };

		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, 875, 122, &rc);
	}
	if (DeathFlg == true)
	{
		Math::Rectangle rc;
		KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);

		rc = { 0, 0, 754, 145 };

		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, 754, 145, &rc);
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
	
	m_player = std::make_shared<Player>();
	m_player->Init();
	m_player->SetOwner(this);
	

	// == エネミー ============
	std::shared_ptr<Enemy> enemy;
	for (int i = 0; i < 10; i++)
	{
		
		enemy = std::make_shared<Enemy>();
		enemy->Init();
		enemy->SetPos(1000 + i*200.0f, float(rand() % 600 - 300));
		enemy->SetOwner(this);
		m_objList.push_back(enemy);
	}
	for (int i = 0; i < 2; i++)
	{
		m_back[i].m_tex.Load("Asset/Textures/Back.png");
		m_back[i].m_pos = { float(0 + 1280 * i), 0, 0 };
	}
	m_tex.Load("Asset/Textures/clear.png");
	m_pos = { 0,0,0 };
	m_Dtex.Load("Asset/Textures/Death.png");
	m_Dpos = { 0,0,0 };
	clearFlg = false;
	DeathFlg = false;

	Timer = 0;
	srand(timeGetTime());
}

void GameScene::Release()
{
	//delete m_player;	// 生ポ　インスタンス破棄 スマポのインスタンス破棄はない
}
