#include "framework.h"
#include "Boss.h"

CBoss::CBoss() : m_iMaxHp(0), m_iCurrentHp(0), m_dwPatternTime(0),
m_ePattern(BOSS::PATTENR_END), m_eType(BOSS::STAGE_END)
{
}

CBoss::~CBoss()
{
}
