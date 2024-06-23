#include "EnemyManager.h"

#include"../../Scene/SceneManager.h"
#include"MushRoom/MushRoom.h"
#include"Goblin/Goblin.h"

void EnemyManager::Init()
{

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
	else if (GetAsyncKeyState('N') & 0x8000)
	{
		
		keyFlg = true;
	}
	else if (GetAsyncKeyState('B') & 0x8000)
	{
		if (keyFlg == false)
		{
			
		}
		keyFlg = true;
	}
	else
	{
		keyFlg = false;
	}

	m_mushRoom++;
	m_goblin++;
	if (m_mushRoom > 300)
	{
		std::shared_ptr<MushRoom> moshRoom;
		moshRoom = std::make_shared<MushRoom>();
		SceneManager::Instance().AddObject(moshRoom);
		m_mushRoom = 0;
	}
	if (m_goblin > 420)
	{
		std::shared_ptr<Goblin> goblin;
		goblin = std::make_shared<Goblin>();
		SceneManager::Instance().AddObject(goblin);
		m_goblin = 0;
	}
}
