#include "../../Scene/GameScene.h"
#include "Player.h"
#include "../../Object/Bullet/Bullet.h"

void Player::Update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)	m_pos.x -= 5.0f;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)m_pos.x += 5.0f;
	if (GetAsyncKeyState(VK_UP) & 0x8000)	m_pos.y += 5.0f;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)	m_pos.y -= 5.0f;

	

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (m_nowMode==NowMode::idle)
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
			Math::Vector3 setPos = { float(m_pos.x + 150 * m_scale),float (m_pos.y - 85 * m_scale), m_pos.z };
			bullet->Init(setPos);
			bullet->SetOwner(m_pOwner);
			bullet->SetScale(m_scale*2);
			m_pOwner->AddObject(bullet);
		}
		
	}
	
	// 当たり判定は移動の後、行列作成の前にする！！
	// プレイヤーと敵の当たり判定　・・・　敵の情報が必要
	// オブジェクトリストをすべて見ていく
	for (auto& obj : m_pOwner->GetObjList())
	{
		//if (obj->GetObjType() == ObjectType::Bullet) continue;
		//if (obj->GetObjType() == ObjectType::Enemy) continue;

		if (obj->GetObjType() == ObjectType::Enemy)
		{	
			// 当たり判定を行う		
			
			// 対象座標 - 自分座標 = 対象へのベクトル
			Math::Vector3 v;
			v = obj->GetPos() - m_pos;
			
			// 球判定　・・・　ベクトルの長さで判定する
			if (v.Length() < 64.0f)
			{
				obj->OnHit();
			}
			
			break;
		}
	}
	m_drawCount++;
	if (m_drawCount > 47)
	{
		if (m_nowMode==NowMode::skill)
		{
			m_nowMode = NowMode::idle;
		}
		m_drawCount = 0;
	}


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
}

void Player::Init()
{
	//SetOwner();
	m_drawCount = 0;
	m_nowMode = NowMode::idle;
	m_scale = 0.5;

	m_tex.Load("Asset/Textures/Wyvern/WyvernMove.png");
	m_skillTex.Load("Asset/Textures/Wyvern/WyvernSkill.png");

	m_pos = {-500,0,0};			// 0, 0, 0 で初期化
	m_rad = { 32, 32 };
	m_bAlive = true;					// 
	m_mat = Math::Matrix::Identity;		// 単位行列で初期化

	m_objType = ObjectType::Player;		// 種類は「プレイヤー」
	// 単位行列　・・・　拡大率全て 1.0　他の値は全て 0
}

void Player::Release()
{
	// KdTexture型のデストラクタで
	// 自動リリースされるのでReleaseを呼ぶ必要はない。
}
