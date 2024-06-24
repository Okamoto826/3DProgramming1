#include "EnemyManager.h"

#include"../../Scene/SceneManager.h"
#include"MushRoom/MushRoom.h"
#include"Goblin/Goblin.h"
#include"Boss/Boss.h"

void EnemyManager::Init()
{
	m_polygon.SetMaterial("Asset/Textures/Bles.png");
	m_polygon.SetSplit(4, 1);
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Right_Middle);
	m_polygon.SetUVRect(0);
	m_pos = { 0,-2.5,0 };
	m_spl = 0;
}

void EnemyManager::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void EnemyManager::Update()
{
	if (GetAsyncKeyState('M') & 0x8000)
	{
		if (keyFlg == false)
		{
			std::shared_ptr<MushRoom> moshRoom;
			moshRoom = std::make_shared<MushRoom>();
			SceneManager::Instance().AddObject(moshRoom);
			keyFlg = true;
		}
	}
	else if (GetAsyncKeyState('Q') & 0x8000)
	{
		m_isExpired = true;
		keyFlg = true;
	}
	else if (GetAsyncKeyState('B') & 0x8000)
	{
		if (keyFlg == false)
		{
			std::shared_ptr<Boss> boss;
			boss = std::make_shared<Boss>();
			SceneManager::Instance().AddObject(boss);
			keyFlg = true;
			KdAudioManager::Instance().Play("Asset/Sound/boss.wav", false)->SetVolume(0.3);
		}
		keyFlg = true;
	}
	else
	{
		keyFlg = false;
	}

	m_mushRoom++;
	m_goblin++;
	if (m_mushRoom > 240)
	{
		std::shared_ptr<MushRoom> moshRoom;
		moshRoom = std::make_shared<MushRoom>();
		SceneManager::Instance().AddObject(moshRoom);
		m_mushRoom = 0;
	}
	if (m_goblin > 360)
	{
		std::shared_ptr<Goblin> goblin;
		goblin = std::make_shared<Goblin>();
		SceneManager::Instance().AddObject(goblin);
		m_goblin = 0;
	}


	m_spl += 0.1;
	if (m_spl >= 4)m_spl = 0;
	m_polygon.SetUVRect(m_spl);


	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix radMat;
	radMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(270));
	m_mWorld = radMat*transMat;
}
