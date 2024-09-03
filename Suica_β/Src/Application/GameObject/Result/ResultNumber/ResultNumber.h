#pragma once
#include "../ResultBase.h"

class ResultNumber : public ResultBase
{
public:
	ResultNumber() {}
	~ResultNumber() {}

	void Init()override;
	void Update()override;

	void SetNumber(const int number) { m_number = number; }
	void IsNotNum() { m_b_isNotNum = true; }



private:
	void RandamNumberSet();


	// 画像
	const std::string NumberPng = "Asset/Textures/number.png";
	const int NumberTexSize = 100;

	// 数
	int m_number{};
	int m_randamNumber{};

	bool m_b_randamTime = true;		// true ... ルーレット
	bool m_b_isNotNum	= false;	// true ... 消える

	// ランダム
	std::shared_ptr<KdRandomGenerator>m_randamGenerator = std::make_shared<KdRandomGenerator>();

	// 数字ルーレットタイム
	const int RandamNumberTime = 60;
	int m_randamNumberTimeCnt{};

	// 数字ルーレットの数字切り替え間隔
	const int RandamNumberChangeTime = 3;
	int m_randamNumberChangeTimeCnt{};






};



