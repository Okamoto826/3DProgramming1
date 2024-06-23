#include "CharaManager.h"

#include"../../Scene/SceneManager.h"
#include"LeafRanger/LeafRanger.h"
#include"CrystalMauler/CrystalMauler.h"
#include"GroundMonk/GroundMonk.h"

void CharaManager::Init()
{
	m_gageTex.Load("Asset/Textures/gage.png");
	m_barTex.Load("Asset/Textures/bar.png");
	m_paceeTex.Load("Asset/Textures/PACEE.png");
	m_numTex.Load("Asset/Textures/num.png");
	m_rangerTex.Load("Asset/Textures/Chara/Icon/leafranger.png");
	m_maulerTex.Load("Asset/Textures/Chara/Icon/crystalmauler.png");
	m_monkTex.Load("Asset/Textures/Chara/Icon/groundmonk.png");
}

void CharaManager::Update()
{
	m_count++;
	if (m_count > 100)
	{
		m_cost += 1;
		if (m_cost > 99)m_cost = 99;
		m_count = 0;
	}
	if (GetAsyncKeyState('L') & 0x8000)
	{
		if(keyFlg==false)
		{
			if(m_cost>5)
			{
				std::shared_ptr<LeafRanger> leafRanger;
				leafRanger = std::make_shared<LeafRanger>();
				SceneManager::Instance().AddObject(leafRanger);
				m_cost -= 5;
			}
		}
		keyFlg = true;
	}
	else if (GetAsyncKeyState('K') & 0x8000)
	{
		if (keyFlg == false)
		{
			if (m_cost > 5)
			{
				std::shared_ptr<CrystalMauler> crystalMauler;
				crystalMauler = std::make_shared<CrystalMauler>();
				SceneManager::Instance().AddObject(crystalMauler);
				m_cost -= 5;
			}
		}
		keyFlg = true;
	}
	else if (GetAsyncKeyState('J') & 0x8000)
	{
		if (keyFlg == false)
		{
			if (m_cost > 2)
			{
				std::shared_ptr<GroundMonk> groundMonk;
				groundMonk = std::make_shared<GroundMonk>();
				SceneManager::Instance().AddObject(groundMonk);
				m_cost -= 2;
			}
		}
		keyFlg = true;
	}
	else
	{
		keyFlg = false;
	}
}

void CharaManager::DrawSprite()
{
	// テクスチャの幅を取得
	
	int w = m_barTex.GetWidth();
	// HPが1のとき幅
	float singleW = w / 100.0f;

	Math::Rectangle rc = { 0,0,(long)m_gageTex.GetWidth(),(long)m_gageTex.GetHeight()};
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_gageTex, -600, 300, rc.width * 7, rc.height * 3, &rc, nullptr, { 0,0.5f });
	rc = { 0,0,long(singleW * m_count),(long)m_barTex.GetHeight() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_barTex, -600, 300, rc.width * 7, rc.height * 3, &rc, nullptr, { 0,0.5f });
	rc = { 0,0,(long)m_paceeTex.GetWidth(),(long)m_paceeTex.GetHeight() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_paceeTex, -600, 250, rc.width, rc.height, &rc, nullptr, { 0,0.5f });
	rc = { long(42 * (m_cost / 10)),0,42,(long)m_numTex.GetHeight() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_numTex, -450, 250, rc.width, rc.height, &rc, nullptr, { 0,0.5f });
	rc = { long(42 * (m_cost % 10)),0,42,(long)m_numTex.GetHeight() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_numTex, -408, 250, rc.width, rc.height, &rc, nullptr, { 0,0.5f });
	rc = { 0,0,64,64 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_rangerTex, -600, 170, rc.width*1.2, rc.height*1.2, &rc, nullptr, { 0,0.5f });
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_maulerTex, -500, 170, rc.width*1.2, rc.height*1.2, &rc, nullptr, { 0,0.5f });
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_monkTex, -400, 170, rc.width*1.2, rc.height*1.2, &rc, nullptr, { 0,0.5f });
	rc = { 42 * 5,0,42,(long)m_numTex.GetHeight() };
	Math::Color color = { 1.0,0,0,1.0 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_numTex, -600, 170, rc.width * 0.7, rc.height * 0.7, &rc, &color, { 0.f,1.f });
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_numTex, -500, 170, rc.width * 0.7, rc.height * 0.7, &rc, &color, { 0.f,1.f });
	rc = { 42 * 2,0,42,(long)m_numTex.GetHeight() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_numTex, -400, 170, rc.width * 0.7, rc.height * 0.7, &rc, &color, { 0.f,1.f });
}
