#pragma once

class DrawNumbers :public KdGameObject
{
public:
	DrawNumbers() { Init(); }
	~DrawNumbers() override { Close(); }

	void Close()		{ m_isExpired = true; }
	
	//表示したい数字をセット
	//float:表示したい数字
	//vector3:座標
	//セットした値のタイプ
	void SetNumbers(float numbers,Math::Vector3 pos,ObjType obj);

private:
	void Init()			override;

	Math::Vector3			m_pos;			//座標
	int						m_digit;			//桁
public:
	// シングルトンパターン
	// 常に存在する && 必ず1つしか存在しない(1つしか存在出来ない)
	// どこからでもアクセスが可能で便利だが
	// 何でもかんでもシングルトンという思考はNG
	static DrawNumbers& Instance()
	{
		static DrawNumbers instance;
		return instance;
	}
};