#include "DrawNumbers.h"
#include "Number.h"
#include"../../../Scene/SceneManager.h"
#include<string>

void DrawNumbers::SetNumbers(float numbers, Math::Vector3 pos, ObjType obj)
{
	std::string sNumbers = std::to_string(numbers);
	
	m_digit = sNumbers.size();
	
	std::shared_ptr<Number>number;

	//すでにあるタイプの値消す
	for (auto& Obj : SceneManager::Instance().GetObjList())
	{
		//自分自身と判定しない
		if (Obj->GetObjType() == obj)
		{
			Obj->Quit();
		}

	}


	for (int i = 0; i < m_digit; i++)
	{
		if (sNumbers.at(i) >= '0' && sNumbers.at(i) <= '9')
		{
			char cnum = sNumbers.at(i);
			int num = std::atoi(&cnum);

			number = std::make_shared<Number>();
			number->SetNumber(num,i,pos,obj);
			SceneManager::Instance().AddObject(number);
		}
	}
	
}



void DrawNumbers::Init()
{
	
	m_pos = {};			//座標
	
}




