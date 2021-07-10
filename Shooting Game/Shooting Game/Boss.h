#pragma once
#ifndef __BOSS_H__
#define __BOSS_H__
#include "Obj.h"
class CBoss :
    public CObj
{
protected:
    BOSS::PATTERN m_eNextPattern;
    BOSS::PATTERN m_ePausePattern;
    BOSS::PATTERN m_eCurPattern;
    BOSS::STAGE m_eType;
    DWORD m_dwCurTime;
    DWORD m_dwPatternTime;
public:
    CBoss();
    virtual ~CBoss();
public:
    inline BOSS::STAGE getStage() { return m_eType; }
    inline BOSS::PATTERN getPattern() { return m_eCurPattern; }
    inline float getRatio() { return (float)m_iCurrentHp / (float)m_iMaxHp; }

};
#endif

