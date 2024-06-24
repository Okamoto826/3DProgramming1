#pragma once

#include"../BaseScene/BaseScene.h"

class TitleScene : public BaseScene
{
public :

	TitleScene() { Init(); }
	~TitleScene() {}
	void DrawSprite();

private :

	void Event() override;
	void Init() override;

	KdTexture m_titleTex;

	Math::Vector3 cameraPos;
};
