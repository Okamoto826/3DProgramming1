#pragma once

class ResultBase : public KdGameObject
{
public:
	ResultBase() {}
	virtual ~ResultBase()override {}

	virtual void Init()override;
	virtual void Update()override {}
	void		 DrawSprite()override;

	virtual void SetPos(const int posX, const int posY) { m_posX = posX; m_posY = posY; }
	virtual void SetScale(const Math::Vector2 scale)	{ m_scale = scale; }

protected:
	void CreateNumber (const int number, const int posX, const int posY, const bool b_isNotNum = false);
	void CreateNumbers(const int number, const int minPosX, const int minPosY);

	// 画像
	std::shared_ptr<KdTexture>m_sp_tex = std::make_shared<KdTexture>();

	int m_texWidth{};
	int m_texHeight{};

	Math::Rectangle m_rect{};
	Math::Color		m_color{};

	// 座標
	int m_posX{};
	int m_posY{};
	
	// 拡大
	Math::Vector2 m_scale = ResetScale;
	
	const int BaseNumberDigit	= 5;
	const int BaseNumberWhile	= 100;
	const int BaseNumbersWhile	= 670;

};
