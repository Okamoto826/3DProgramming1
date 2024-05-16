#include "../../Scene/GameScene.h"
#include "Player.h"
#include"../Enemy/Enemy.h"
#include "../../Object/Bullet/Bullet.h"

void Player::Update()
{
	m_drawCount++;
	if (m_nowMode != NowMode::down)
	{




		if (GetAsyncKeyState(VK_LEFT) & 0x8000)	m_pos.x -= 5.0f;
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)m_pos.x += 5.0f;
		if (GetAsyncKeyState(VK_UP) & 0x8000)	m_pos.y += 5.0f;
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)	m_pos.y -= 5.0f;



		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (m_nowMode == NowMode::idle)
			{
				m_drawCount = 0;
				m_nowMode = NowMode::skill;
			}
		}


		if (m_nowMode == NowMode::skill)
		{
			if (m_drawCount == 24)
			{
				std::shared_ptr<Bullet> bullet;
				bullet = std::make_shared<Bullet>();
				Math::Vector3 setPos = { float(m_pos.x + 150 * m_scale),float(m_pos.y - 85 * m_scale), m_pos.z };
				bullet->Init(setPos);
				bullet->SetOwner(m_pOwner);
				bullet->SetScale(m_scale * 2);
				m_pOwner->AddObject(bullet);
				if (m_scale > 1.0)
				{
					for (int i = 0; i < 2; i++)
					{
						std::shared_ptr<Bullet> bullet;
						bullet = std::make_shared<Bullet>();
						Math::Vector3 setPos = { float(m_pos.x + 150 * m_scale),float(m_pos.y - 85 * m_scale), m_pos.z };
						bullet->Init(setPos);
						bullet->SetOwner(m_pOwner);
						bullet->SetScale(m_scale * 2);
						bullet->SetMovePow({ 5.0,float(3.0 - 6.0 * i),0 });
						m_pOwner->AddObject(bullet);
					}
				}
			}

		}



		if (m_drawCount > 47)
		{
			if (m_nowMode == NowMode::skill)
			{
				m_nowMode = NowMode::idle;
			}
			m_drawCount = 0;
		}
		m_lifeGurd--;
	}
	if (m_nowMode == NowMode::down)
	{
		if (m_drawCount > 47)
		{
			m_drawCount == 47;
			{
				m_pOwner->Death();
			}
		}
	}
	if (GetAsyncKeyState('D') & 0x8000)m_scale = 0.9;
	if (GetAsyncKeyState('G') & 0x8000)m_scale = 1.2;
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_scaleMat = Math::Matrix::CreateScale(-m_scale,m_scale,1);
	m_mat = m_scaleMat*transMat;
}

void Player::Draw()
{
	Math::Rectangle rc;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);

	rc = { 0 + 360 * (m_drawCount / 6), 0, 360, 340 };
	if(m_nowMode==NowMode::idle)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, 360, 340, &rc);
	}
	if (m_nowMode == NowMode::skill)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_skillTex, 0, 0, 360, 340, &rc);
	}
	if (m_nowMode == NowMode::down)
	{
		rc = { 0 + 300 * (m_drawCount / 6), 0, 300, 340 };
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_downTex, 0, 0, 300, 340, &rc);
	}
}

void Player::Init()
{
	//SetOwner();
	m_drawCount = 0;
	m_nowMode = NowMode::idle;
	m_scale = 0.5;
	m_breakCount = 0;

	m_tex.Load("Asset/Textures/Wyvern/WyvernMove.png");
	m_skillTex.Load("Asset/Textures/Wyvern/WyvernSkill.png");
	m_downTex.Load("Asset/Textures/Wyvern/WyvernHit.png");

	m_pos = {-500,0,0};			// 0, 0, 0 で初期化
	m_rad = { 32, 32 };
	m_bAlive = true;					// 
	m_mat = Math::Matrix::Identity;		// 単位行列で初期化

	// 種類は「プレイヤー」
	// 単位行列　・・・　拡大率全て 1.0　他の値は全て 0
}

void Player::BreakEnemy()
{
	m_breakCount++;
	switch (int(m_scale * 10))
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		if (m_breakCount > 2)
		{
			m_scale += 0.1;
			m_breakCount = 0;
		}
		break;
	case 6:
	case 7:
	case 8:
		if (m_breakCount > 5)
		{
			m_scale += 0.1;
			m_breakCount = 0;
		}
		break;
	case 9:
		if (m_breakCount > 12)
		{
			m_scale += 0.1;
			m_breakCount = 0;
		
		}
		break;
	case 10:
		if (m_breakCount > 15)
		{
			m_scale += 0.1;
			m_breakCount = 0;
		}
		break;
	case 11:
		if (m_breakCount > 30)
		{
			m_scale += 0.1;
			m_breakCount = 0;
		}
		break;
	case 12:
		if (m_breakCount > 30)
		{
			m_pOwner->Clear();
		}
		break;
	}
	if (m_scale > 1.2)m_scale = 1.2;
}

void Player::OnHit()
{
	if (m_lifeGurd < 0)
	{
		m_scale -= 0.1;
		if (m_scale < 0.5)
		{
			//m_nowMode = NowMode::down;
			
			//デバッグモード
			m_scale = 0.5;
		}
		m_lifeGurd = 30;
	}
}

void Player::Release()
{
	// KdTexture型のデストラクタで
	// 自動リリースされるのでReleaseを呼ぶ必要はない。
}
