#include "Player.h"
#include "Application/main.h"
#include "Application/Scene/GameScene/EventManager.h"

void Player::Init()
{
	//変数初期化
	m_pos = {};
	m_bMove = false;
	m_speed = 0.3f;
	m_success = 0;
	m_moveDelay = 0;

	//移動量の受け渡し
	EventManager::Instance().SetPlayerMoveAmount(m_moveAmount);
}

void Player::Update()
{
	EventManager::Instance().SetPlayerPos(m_pos);

	if (EventManager::Instance().GetMaxCombo() < EventManager::Instance().GetCombo())
	{
		EventManager::Instance().SetMaxCombo(EventManager::Instance().GetCombo());
	}

	//デバッグ
	Math::Vector3 debug = m_pos;

	//合ってた時にカウント加算する用
	int addSuccess = 1;

	//カウントに応じたスピードの変更
	SuccessCountFunction();

	//プレイヤーの移動
	PlayerMoving();

	//デバッグ
	Application::Instance().m_log.AddLog("combo : %d\n", EventManager::Instance().GetMaxCombo());

	//右押したとき
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000 || GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (m_bRight == false)
		{
			//キー
			m_bRight = true;

			if (m_bMove == false)
			{
				//加算
				m_success += addSuccess;

				//移動フラグオン
				m_bMove = true;
			}
		}
	}
	else
	{
		//キー
		m_bRight = false;
	}

	//行列作成
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);

	EventManager::Instance().SetPlayerMoveFlg(m_bMove);

}

void Player::SuccessCountFunction()
{
	//ポイントごとの判定
	const int firstPoint = 10;
	const int secondPoint = 20;
	const int thirdPoint = 30;
	const int forthPoint = 50;

	//ポイントごとのスピード処理
	if (m_success > forthPoint)
	{
		m_speed = 1.5f;
		EventManager::Instance().SetClubCoolTime(5);
	}
	else if (m_success > thirdPoint)
	{
		m_speed = 1.0f;
		EventManager::Instance().SetClubCoolTime(10);
	}
	else if (m_success > secondPoint)
	{
		m_speed = 0.75f;
		EventManager::Instance().SetClubCoolTime(15);
	}
	else if (m_success > firstPoint)
	{
		m_speed = 0.5f;
		EventManager::Instance().SetClubCoolTime(25);
	}
	else
	{
		EventManager::Instance().SetClubCoolTime(35);
	}
}

void Player::PlayerMoving()
{
	//移動
	if (m_bMove == true)
	{
		if (m_moveDelay > 3)
		{
			m_moveCounter += m_speed;
			m_pos.x += m_speed;
			m_bSwing = true;
		}

		m_moveDelay++;
	}

	//既定の距離進んだら補正+移動終了
	if (m_moveCounter >= m_moveAmount)
	{
		const float reset = 0.f;
		float revisionAmount = m_moveAmount - m_moveCounter;

		m_pos.x += revisionAmount;
		m_bMove = false;
		m_moveCounter = reset;
		m_moveDelay = 0;
		m_bSwing = false;
		EventManager::Instance().SetItemBreak(false);
	}
}
