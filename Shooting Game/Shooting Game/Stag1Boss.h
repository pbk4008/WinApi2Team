#pragma once
#ifndef __STAGE1BOSS_H__
#define __STAGE1BOSS_H__
#include "Boss.h"
class CStag1Boss :
    public CBoss
{
private:
    DWORD m_bulletDelayTime;
public:
    CStag1Boss();
    virtual ~CStag1Boss();
public:
    virtual void Initialize() override;
    virtual void LateInit() override;
    virtual int Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;
private:
    void setPattern();
    void RunPattern();
    CObj* CreateBossBullet();
};
#endif

