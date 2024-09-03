#include "GameFloor.h"
#include "Application/GameObject/WaterMelon/WaterMelon.h"
#include "Application/Scene/SceneManager.h"
#include "Application/Scene/GameScene/EventManager.h"
#include "Application/GameObject/Bomb/Bomb.h"

void GameFloor::Init()
{
	//ポリゴン生成
	m_spPoly = std::make_shared<KdSquarePolygon>();

	//読み込み
	m_spPoly->SetMaterial("Asset/Textures/Game/Floor/SandyBeach.png");
	m_spPoly->SetScale({50.f,10.f});

	//座標
	m_pos = { 0.f,m_initialPosY,10.f };

	//座標2
	m_secPos = { 50.f,m_initialPosY,10.f };

	//スイカの間隔
	int mellonDist = EventManager::Instance().GetPlayerMoveAmount();

	//スイカの数
	int mellonNum = 5;

	//スイカ
	for (int i = 0; i < mellonNum; i++)
	{
		std::shared_ptr<WaterMelon> mellon = std::make_shared<WaterMelon>();
		mellon->Init();
		mellon->SetPos({ m_pos.x + (mellonDist * i),m_pos.y + 1.f,m_pos.z+2 });
		mellon->SetTarget(m_wpTarget);
		SceneManager::Instance().AddObject(mellon);
	}
}

void GameFloor::Update()
{
	//ターゲット(プレイヤー)
	std::shared_ptr<KdGameObject> spTarget = m_wpTarget.lock();

	//プレイヤーがある時
	if (spTarget)
	{
		//補正用変数
		const float revision = 45.f;

		//1枚目とプレイヤーの間隔
		float dist = m_pos.x - spTarget->GetMatrix().Translation().x;

		//一定以上なら
		if (abs(dist) > revision)
		{
			//補正
			m_pos = spTarget->GetMatrix().Translation();
			m_pos += { revision, m_initialPosY, 10.f };
		}

		//2枚目
		dist = m_secPos.x - spTarget->GetMatrix().Translation().x;

		//一定以上なら
		if (abs(dist) > revision)
		{
			//補正
			m_secPos = spTarget->GetMatrix().Translation();
			m_secPos += { revision, m_initialPosY, 10.f };
		}

		float x = spTarget->GetMatrix().Translation().x;
		int mellonDist = EventManager::Instance().GetPlayerMoveAmount();

		if (EventManager::Instance().GetMake() == true)
		{
			if (m_makeItem == false)
			{
				if (rand() % 2 == 0)
				{
					m_makeItem = true;
					EventManager::Instance().SetMake(false);
					std::shared_ptr<Bomb> bomb = std::make_shared<Bomb>();
					bomb->Init();
					bomb->SetPos({ x + mellonDist * 5,m_pos.y + 1.f,m_pos.z + 2 });
					SceneManager::Instance().AddObject(bomb);
				}
				else
				{
					m_makeItem = true;
					EventManager::Instance().SetMake(false);
					std::shared_ptr<WaterMelon> mellon = std::make_shared<WaterMelon>();
					mellon->Init();
					mellon->SetPos({ x + mellonDist * 5,m_pos.y + 1.f,m_pos.z + 2 });
					mellon->SetTarget(m_wpTarget);
					SceneManager::Instance().AddObject(mellon);
				}
			}
		}
		else
		{
			m_makeItem = false;
		}
	}

	Math::Matrix rotateMat, transMat;

	//行列作成
	rotateMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90));
	transMat = Math::Matrix::CreateTranslation(m_pos);

	//2枚目
	Math::Matrix secondTrans;
	secondTrans = Math::Matrix::CreateTranslation(m_secPos);

	m_mWorld = rotateMat * transMat;
	m_secondMat = rotateMat * secondTrans;
}

void GameFloor::DrawLit()
{
	//描画
	m_spPoly->SetScale({ 50.f,20.f });
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);

	//2枚目
	m_spPoly->SetScale({ -50.f,20.f });
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_secondMat);
}
