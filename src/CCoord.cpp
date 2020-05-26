/**
 * @author Jaroslav Fikar
 * 
*/


#include "CCoord.h"

bool CCoord::operator<(const CCoord &other) const
{
    CCoord zeroPoint;

    return this->CalcDistnance(zeroPoint) < other.CalcDistnance(zeroPoint);

}

bool CCoord::operator==(const CCoord &other) const
{
    if(this->m_X == other.m_X && this->m_Y == other.m_Y)
    {
        return true;
    }

    return false;
}

bool CCoord::AlmostEqual(const CCoord &other) const
{
    CCoord thisCoord = CCoord(floor(this->m_X), floor(this->m_Y));
    CCoord otherCoord = CCoord(floor(other.m_X), floor(other.m_Y));

    return (thisCoord == otherCoord);
}

double CCoord::CalcDistnance(const CCoord &other) const
{
    return sqrt(((this->m_X - other.m_X) * (this->m_X - other.m_X)) + ((this->m_Y - other.m_Y) * (this->m_Y - other.m_Y)));
}


