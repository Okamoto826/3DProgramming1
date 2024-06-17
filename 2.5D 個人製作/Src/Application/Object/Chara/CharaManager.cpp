#include "CharaManager.h"

#include"../../Scene/SceneManager.h"
#include"LeafRanger/LeafRanger.h"

void CharaManager::Init()
{
	
}

void CharaManager::Update()
{
	if (GetAsyncKeyState('L') & 0x8000)
	{
		std::shared_ptr<LeafRanger> leafRanger;
		leafRanger = std::make_shared<LeafRanger>();
		SceneManager::Instance().AddObject(leafRanger);
	}
}
