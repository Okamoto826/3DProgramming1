#pragma once

class Number :public KdGameObject
{
public:
	Number() { Init(); }
	~Number() {}

	void DrawSprite()	override;
	
	void Close() { m_isExpired = true; }
	void SetNumber(int num, int digit, Math::Vector3 pos,ObjType obj);		//表示したい数字、何桁目か、基準座標、値の種類
private:
	void Init()			override;

	//画像の元の矩形
	//(切り取り開始X,Y,切り取る枠X,Y)
	Math::Rectangle			m_rectAngle;
	int						m_texHeight;	//表示したい画像のYの大きさ
	int						m_texWide;		//表示したい画像のXの大きさ
	KdTexture				m_tex;			//画像
	Math::Vector3			m_pos;			//座標
	Math::Color				m_color;		//色
	

	Math::Matrix			m_sMat = Math::Matrix::Identity;//拡縮
	Math::Matrix			m_rMat = Math::Matrix::Identity;//回転
	Math::Matrix			m_tMat = Math::Matrix::Identity;//移動

};