#pragma once

class EventManager
{
public:

	void SetPlayerMoveAmount(float a_amount) { m_playerMoveAmount = a_amount; }
	float GetPlayerMoveAmount() { return m_playerMoveAmount; }

	void SetPlayerPos(Math::Vector3 a_pos) { m_playerPos = a_pos; }
	Math::Vector3 GetPlayerPos() { return m_playerPos; }

	void SetScore(int a_score) { m_score = a_score; }
	void AddScore() { m_score += 100; }
	void SubScore();
	int GetScore() { return m_score; }

	void SetClubCoolTime(int a_coolTime) { m_clubCoolTime = a_coolTime; }
	int GetClubCoolTime() { return m_clubCoolTime; }

	void SetRestTime(int a_coolTime) { m_restTime = a_coolTime; }
	int GetRestTime() { return m_restTime; }

	void SetPlayerMoveFlg(bool a_flg) { m_bPlayerMove = a_flg; }
	bool GetPlayerMoveFlg() { return m_bPlayerMove; }

	void SetItemBreak(bool a_flg) { m_bBreak = a_flg; }
	bool GetItemBreak() { return m_bBreak; }

	void SetMake(bool a_flg) { m_bMake = a_flg; }
	bool GetMake() { return m_bMake; }

	//void SetCombo(int a_num) { m_combo = a_num; }
	void AddCombo() { m_combo += 1; }
	void ResetCombo() { m_combo = 0; }
	int GetCombo() { return m_combo; }

	void SetMaxCombo(int a_num) { m_maxCombo = a_num; }
	int GetMaxCombo() { return m_maxCombo; }

	void Init();

private:

	float m_playerMoveAmount = 0.f;
	Math::Vector3 m_playerPos = {};
	int m_score = 0;
	int m_clubCoolTime = 0;
	int m_restTime = 0;
	bool m_bPlayerMove = false;
	bool m_bBreak = false;
	bool m_bMake = false;
	int m_combo = 0;
	int m_maxCombo = 0;

private:

	EventManager() {}
	~EventManager() {}

public:

	static EventManager& Instance()
	{
		static EventManager instance;
		return instance;
	}

};