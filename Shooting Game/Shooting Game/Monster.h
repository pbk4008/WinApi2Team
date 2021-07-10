#pragma once

#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Obj.h"

class CMonster :
    public CObj
{
public: explicit CMonster();
public:	virtual ~CMonster();

public:	virtual void Initialize() override;
public: virtual void LateInit() override;
public: virtual int Update() override;
public: virtual void LateUpdate() override;
public: virtual void Render(HDC _hDC) override;
public: virtual void Release() override;

public: inline bool GetIsSpawn() { return m_bIsSpawn; }

public: inline void SetEnemy(ENEMY::TYPE _type) { m_eType = _type; }
public: inline void SetSpawn() { m_bIsSpawn = !m_bIsSpawn; }

public: void RendPosin(HDC _hDC);
public: void CreateMonBullet();

private: ENEMY::TYPE m_eType;
private: bool m_bIsSpawn;

private: POINT	m_tPosin;
private: float	m_fPosinDis;

};


#endif // !__MONSTER_H__



