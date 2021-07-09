#include "framework.h"
#include "Boss.h"

CBoss::CBoss() : m_iMaxHp(0), m_iCurrentHp(0), m_dwPatternTime(0), m_dwCurTime(0),
m_eNextPattern(BOSS::PATTENR_END), m_ePausePattern(BOSS::PATTENR_END),m_eType(BOSS::STAGE_END)
, m_eCurPattern(BOSS::PATTENR_END)
{
}

CBoss::~CBoss()
{
}
