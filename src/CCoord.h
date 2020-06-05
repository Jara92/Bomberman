/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <math.h>
#include <iostream>

/**
 * Represents point in 2D space
 */

class CCoord
{
public:
    /**
     * CCoord constructor
     * @param x
     * @param y
     */
    CCoord(double x = 0, double y = 0)
            : m_X(x), m_Y(y)
    {}

    CCoord(const CCoord &other) = default;

    CCoord &operator=(const CCoord &other) = default;

    ~CCoord() = default;

    /** Operators +, -, * and / */
    CCoord operator+(const CCoord &other) const
    { return CCoord(this->m_X + other.m_X, this->m_Y + other.m_Y); }

    CCoord operator+=(const CCoord &other)
    {
        this->m_X += other.m_X;
        this->m_Y += other.m_Y;
        return *this;
    }

    CCoord operator-(const CCoord &other) const
    { return CCoord(this->m_X - other.m_X, this->m_Y - other.m_Y); }

    CCoord operator-=(const CCoord &other)
    {
        this->m_X -= other.m_X;
        this->m_Y -= other.m_Y;
        return *this;
    }

    CCoord operator*(const double x) const
    { return CCoord(x * this->m_X, x * this->m_Y); }

    friend CCoord operator*(const double x, const CCoord &coord)
    { return CCoord(x * coord.m_X, x * coord.m_Y); }

    CCoord operator/(const double x) const
    {
        if (x == 0) throw std::invalid_argument("Dividing by zero is forbidden!");
        return CCoord(this->m_X / x, this->m_Y / x);
    }

    CCoord operator /= (const double x)
    {
        CCoord y = (*this) / x;

        this->m_X = y.m_X;
        this->m_Y = y.m_Y;

        return *this;
    }

    friend std::ostream &operator<<(std::ostream &ostream, const CCoord &coord)
    {
        ostream << "(" << coord.m_X << ", " << coord.m_Y << ")";
        return ostream;
    }

    /**
     * Compares two points.
     * @param other
     * @return True if the first vector is closer to zero vector than the second one.
     */
    bool operator<(const CCoord &other) const;

    bool operator==(const CCoord &other) const;

    bool operator != (const CCoord & other) const
    {return !(*this == other);}

    bool AlmostEqual(const CCoord &other) const;


    /**
     * Calculates distance between this and the other point
     * @param a
     * @param b
     * @return Distance between two points.
     */
    double CalcDistnance(const CCoord &other) const;

    int GetFlooredX() const
    {return static_cast<int>(this->m_X);}

    int GetFlooredY() const
    {return static_cast<int>(this->m_Y);}

    /** Coordinates */
    double m_X;
    double m_Y;
};

