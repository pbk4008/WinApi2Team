#pragma once
#ifndef __STAGESCENE_H__
#define __STAGESCENE_H__
#include "Scene.h"
class CStageScene :
    public CScene
{
private:
    int m_iBackPattern;
    DWORD m_dwBackTime;
public:
    CStageScene();
    virtual ~CStageScene();

public:
    virtual void Initialize() override;
    virtual void LateInit() override;
    virtual int Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;

public: void MonPattern(ENEMY::PATTERN _pattern);
public: void PlayTime();
public: CObj* CreateMonster();
public: CObj* CreateMonster(float _x, float _y);

private: int m_iPlayTime;
private: int m_iControlTime;
private: DWORD m_dwPlayTime;
private: int m_iPattern;
private: DWORD m_dwCheckPatternTime;


       // CScene을(를) 통해 상속됨
       virtual void CreateBackGround(HDC _hDC) override;

};
#endif

