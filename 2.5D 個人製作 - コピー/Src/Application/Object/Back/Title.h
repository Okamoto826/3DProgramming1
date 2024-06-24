#pragma once
class Title :public KdGameObject
{
public:
	Title() { Init(); }
	~Title() {}

	void Init()override;
	void DrawSprite()override;

private:

	KdTexture m_titleTex;
	KdTexture m_enterTex;
	int alfa = 0;;
};