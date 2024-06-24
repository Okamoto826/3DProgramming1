#include "TitleScene.h"
#include "../SceneManager.h"
#include"../../Object/Stage/Stage.h"
#include"../../Object/Chara/CharaManager.h"
#include"../../Object/Back/Back.h"
#include"../../Object/Back/BackGrass.h"
#include"../../Object/Back/BackTree.h"
#include"../../Object/Enemy/EnemyManager.h"
#include"../../Object/Back/Title.h"

void TitleScene::DrawSprite()
{

}

void TitleScene::Event()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		cameraPos.x -= 0.1;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		cameraPos.z += 0.1;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		cameraPos.z -= 0.1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		cameraPos.x += 0.1;
	}
	Math::Matrix transmat = Math::Matrix::CreateTranslation(cameraPos);

	// 行列を合成
	Math::Matrix mat = transmat;

	// カメラに行列をセット
	// この時点では画面には反映されない
	m_camera->SetCameraMatrix(mat);
	

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Game
		);
	}

	}

void TitleScene::Init()
{
	// カメラ　生成＆視野角設定
	m_camera = std::make_unique<KdCamera>();	// 1 メモリ確保
	cameraPos = { -20.f,0.f,-7.0f };
	

	std::shared_ptr<Stage> stage;
	stage = std::make_shared<Stage>();
	m_objList.push_back(stage);

	std::shared_ptr<Back> back;
	back = std::make_shared<Back>();
	m_objList.push_back(back);

	std::shared_ptr<BackGrass> backgrass;
	backgrass = std::make_shared<BackGrass>();
	m_objList.push_back(backgrass);

	std::shared_ptr<BackTree> backtree;
	backtree = std::make_shared<BackTree>();
	m_objList.push_back(backtree);

	std::shared_ptr<Title> title;
	title = std::make_shared<Title>();
	m_objList.push_back(title);
}
