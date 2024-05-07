#include "BaseObject.h"

void BaseObject::Update()
{
	
}

void BaseObject::Draw()
{

}

void BaseObject::Init()
{
	m_pos = { 0.0f, 0.0f };
}

void BaseObject::SetTexture(std::string _fileName)
{
	m_tex.Load(_fileName);
}

void BaseObject::OnHit()
{

}

void BaseObject::Release()
{

}