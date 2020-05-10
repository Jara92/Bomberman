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

double CCoord::CalcDistnance(const CCoord &other) const
{
    return sqrt(((this->m_X - other.m_X) * (this->m_X - other.m_X)) + ((this->m_Y - other.m_Y) * (this->m_Y - other.m_Y)));
}
