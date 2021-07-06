#pragma once
#ifndef __BOSSBULLET_H__
#define __BOSSBULLET_H__
#include "Obj.h"
class CBoss;
class CBossBullet :
    public CObj
{
private:
    CBoss* m_pTarget;
    BOSS::PATTERN m_ePattern;
public:
    CBossBullet();
    virtual ~CBossBullet();
public:
    virtual void Initialize() override;
    virtual void LateInit() override;
    virtual int Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;
};
#endif

