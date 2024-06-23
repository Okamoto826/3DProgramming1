#include "CharaManager.h"

#include"../../Scene/SceneManager.h"
#include"LeafRanger/LeafRanger.h"
#include"CrystalMauler/CrystalMauler.h"
#include"GroundMonk/GroundMonk.h"

void CharaManager::Init()
{
	
}

void CharaManager::Update()
{
	if (GetAsyncKeyState('L') & 0x8000)
	{
		if(keyFlg==false)
		{
			std::shared_ptr<LeafRanger> leafRanger;
			leafRanger = std::make_shared<LeafRanger>();
			SceneManager::Instance().AddObject(leafRanger);
		}
		keyFlg = true;
	}
	else if (GetAsyncKeyState('K') & 0x8000)
	{
		if (keyFlg == false)
		{
			std::shared_ptr<CrystalMauler> crystalMauler;
			crystalMauler = std::make_shared<CrystalMauler>();
			SceneManager::Instance().AddObject(crystalMauler);
		}
		keyFlg = true;
	}
	else if (GetAsyncKeyState('J') & 0x8000)
	{
		if (keyFlg == false)
		{
			std::shared_ptr<GroundMonk> groundMonk;
			groundMonk = std::make_shared<GroundMonk>();
			SceneManager::Instance().AddObject(groundMonk);
		}
		keyFlg = true;
	}
	else
	{
		keyFlg = false;
	}
}
