#pragma once
#ifndef __OBJ_H__
#define __OBJ_H__
class CObj
{
protected:
	INFO m_tInfo;
	RECT m_tRect;
	RECT m_tHitBox;
	CObj* m_pCollisionTarget;
	float m_fSpeed;
	float m_fAngle;
	bool m_bNotDestroy;//씬 전환 후에도 삭제되지 않음
	bool m_bPollingCheck;//풀링 체크 변수
	bool m_bDead;
	CObj* m_pTarget;
	SCENE::TAG m_eScene;
	POSLIST m_PosList;
	POINT* m_PolygonList;
	DISINFO* m_iPosDisArr;

	int m_iMaxHp;
	int m_iCurrentHp;
	int m_iAtk;
public:
	CObj();
	virtual ~CObj();
public:
	virtual void Initialize() PURE;
	virtual void LateInit() PURE;
	virtual int Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render(HDC _hDC) PURE;
	virtual void Release() PURE;
protected:
	void RectUpdate();
	void LoadPoint(const TCHAR* _str);
	void SetGraphicPos();
	void SetPivot();
	void PosUpdate();
	void setDis();
public:
	inline void setScene(SCENE::TAG _eTag) { m_eScene = _eTag; }
	inline void setPos(float _x, float _y) { m_tInfo.fX = _x, m_tInfo.fY = _y; }
	inline void setAngle(float _Angle) { m_fAngle = _Angle; }
	inline void setNotDestory() {	m_bNotDestroy = true; }
	inline void setDead(bool _bDead) { m_bDead = _bDead; }
	inline void setPollingCheck(bool _bPoolingCheck) { m_bPollingCheck = _bPoolingCheck; }
	inline void setCollisionTarget(CObj* _pTarget) { m_pCollisionTarget = _pTarget; }
	inline void setTarget(CObj* _pTarget) { m_pTarget = _pTarget; }
	
public:
	inline SCENE::TAG getScene() { return m_eScene; }
	inline bool getNotDestory() { return m_bNotDestroy; }
	inline bool getDead() { return m_bDead; }
	inline bool getPoolingCheck() { return m_bPollingCheck; }
	inline CObj* getTarget() { return m_pTarget; }
	inline const INFO getInfo()const { return m_tInfo; }
	inline float getAngle() { return m_fAngle; }
	inline int getAtk() { return m_iAtk; }
	inline int getHp() { return m_iCurrentHp; }
	inline RECT& GetHitBox() { return m_tHitBox; }
};
#endif

