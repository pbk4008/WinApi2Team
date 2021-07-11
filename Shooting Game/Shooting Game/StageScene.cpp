#include "framework.h"
#include "StageScene.h"
#include "Stag1Boss.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "Monster.h"

CStageScene::CStageScene() : m_iPlayTime(0), m_iControlTime(0), m_dwPlayTime(0), m_iPattern(1)
{	
}

CStageScene::~CStageScene()
{
	Release();
}

void CStageScene::Initialize()
{
	m_ObjMgr = CObjMgr::getInstance();
	//m_ObjMgr->AddObject(OBJ::BOSS, CAbstractFactory<CStag1Boss>::CreateObj(100, 200));
	m_ObjMgr->AddObject(OBJ::PLAYER, CAbstractFactory<CPlayer>::CreateObj((float)WINCX/2, 500.f));
}

void CStageScene::LateInit()
{
	m_ObjMgr->LateInit();
}

int CStageScene::Update()
{
	int iEvent=m_ObjMgr->Update();	

	PlayTime();

	if (m_iPlayTime % 5 == 4 && m_iPattern == 1)
	{
		MonPattern(ENEMY::PATTERN_1);
		++m_iPattern;
	}


	return SCENE_STATE::NO;

}

void CStageScene::LateUpdate()
{
	m_ObjMgr->LateUpdate();

	//CCollisionMgr::CollisionSphere(CObjMgr::getInstance()->getList(OBJ::PLAYER), CObjMgr::getInstance()->getList(OBJ::BOSSBULLET));
	CCollisionMgr::CollisionSphere(CObjMgr::getInstance()->getList(OBJ::MONSTER), CObjMgr::getInstance()->getList(OBJ::HOMINGBULLET));

	CCollisionMgr::CollisionSphere(CObjMgr::getInstance()->getList(OBJ::SHIELD), CObjMgr::getInstance()->getList(OBJ::BOSSBULLET));
	CCollisionMgr::CollisionSphere(CObjMgr::getInstance()->getList(OBJ::BULLET),
		CObjMgr::getInstance()->getList(OBJ::BOSS));
	CCollisionMgr::CollisionSphere(CObjMgr::getInstance()->getList(OBJ::BULLET),
		CObjMgr::getInstance()->getList(OBJ::BOSSBULLET));
}

void CStageScene::Render(HDC _hDC)
{
	/*HBRUSH hBrush = CreateSolidBrush(RGB)*/
	Rectangle(_hDC, 0, 0, WINCX, WINCY);
	m_ObjMgr->Render(_hDC);
	TCHAR szText[32] = {};

	
	swprintf_s(szText, L"Boss Bullet : %d", CObjMgr::getInstance()->getList(OBJ::BOSSBULLET).size());
	TextOut(_hDC, 10, 10, szText, lstrlen(szText));
	// Monster Bullet

	TCHAR szText2[32] = {};
	swprintf_s(szText2, L"MonBullet : %d", CObjMgr::getInstance()->getList(OBJ::MONBULLET).size());
	TextOut(_hDC, 10, 70, szText2, lstrlen(szText2));

	TCHAR PlayerBulletText[32] = {};
	swprintf_s(PlayerBulletText, L"Player Bullet : %d", CObjMgr::getInstance()->getList(OBJ::BULLET).size());
	TextOut(_hDC, 10, 30, PlayerBulletText, lstrlen(PlayerBulletText));

	TCHAR PlayerHp[32] = {};
	swprintf_s(PlayerHp, L"Player Hp : %d", CObjMgr::getInstance()->getPlayer()->getHp());
	TextOut(_hDC, 10, 50, PlayerHp, lstrlen(PlayerHp));

	TCHAR	szPlayTime[32] = L"";
	swprintf_s(szPlayTime, L"PlayTime: %d", m_iPlayTime);
	TextOut(_hDC, 460, 10, szPlayTime, lstrlen(szPlayTime));

}

void CStageScene::Release()
{
	m_ObjMgr->SceneObjectRemove(SCENE::STAGE1);
}

void CStageScene::MonPattern(ENEMY::PATTERN _pattern)
{	
	list<CObj*> monlist;
	int iRandArr[12] = {};
	int k = 0;
	int Cnt = 0;

	for (int i = 0; i < 5; ++i)
	{
		
		CObj* obj = m_ObjMgr->getInstance()->ObjPooling(OBJ::MONSTER);
		if (obj == nullptr)
		{
			obj = CreateMonster(50.f, 50.f);
			monlist.emplace_back(obj);
		}
		else
		{
			monlist.emplace_back(obj);
		}
		
	}

	/// X좌표 랜덤처리
	// 중복처리 해야함
	if (_pattern == ENEMY::PATTERN_1)
	{
		for (int i = 0; i < (sizeof(iRandArr) / 4); ++i)
		{
			iRandArr[i] = i + 1;
		}

		for (int i = 0; i < 100; ++i)
		{
			int iRandPos = rand() % 10 + 1;
			int temp = iRandArr[iRandPos];
			iRandArr[iRandPos] = iRandArr[iRandPos + 1];
			iRandArr[iRandPos + 1] = temp;
		}		
	///

		for (auto obj : monlist)
		{								
			if (!static_cast<CMonster*>(obj)->GetIsSpawn())
			{
				static_cast<CMonster*>(obj)->SetSpawn();
				obj->setPos((70.f * iRandArr[k]), 50.f);
			}
			++k;
			if (k >= monlist.size())
				break;
		}		
	}
	//CObj* pBullet = CObjMgr::getInstance()->ObjPooling(OBJ::MONSTER, CObjMgr::getInstance()->getPlayer());
	//pBullet->setPos(iRandPos * 50.f, 50.f);
}

void CStageScene::PlayTime()
{
	if (m_dwPlayTime + 10 < GetTickCount())
	{
		++m_iControlTime;
		if (m_iControlTime > 60)
		{
			++m_iPlayTime;
			m_iControlTime = 0;
		}

		m_dwPlayTime = GetTickCount();
	}
}

CObj* CStageScene::CreateMonster()
{
	CObj* pObj = nullptr;
	pObj = CObjMgr::getInstance()->ObjPooling(OBJ::MONSTER);
	if (!pObj)
	{
		pObj = CAbstractFactory<CMonster>::CreateObj(50.f, 50.f);	
		pObj->Initialize();
		pObj->LateInit();
		CObjMgr::getInstance()->getList(OBJ::MONSTER).emplace_back(pObj);
	}

	return pObj;
}

CObj* CStageScene::CreateMonster(float _x, float _y)
{
	CObj* pObj = nullptr;
	pObj = CObjMgr::getInstance()->ObjPooling(OBJ::MONSTER);
	if (!pObj)
	{
		pObj = CAbstractFactory<CMonster>::CreateObj(_x, _y);
		pObj->Initialize();
		pObj->LateInit();		
		CObjMgr::getInstance()->getList(OBJ::MONSTER).emplace_back(pObj);
	}
	return pObj;
}

void CStageScene::CreateBackGround(HDC _hDC)
{
}
