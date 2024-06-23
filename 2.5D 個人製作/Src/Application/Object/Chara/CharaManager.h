#pragma once

class CharaManager:public KdGameObject
{
public:
	CharaManager() { Init(); };
	~CharaManager() {};
	void Init()override;
	void Update()override;
private:
	bool keyFlg = false;
};
