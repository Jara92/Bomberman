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
template<class T = double>
class CCoord
{
public:
    /**
     * CCoord constructor
     * @param x
     * @param y
     */
    CCoord(T x = 0, T y = 0)
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

    CCoord operator*(const T x) const
    { return CCoord(x * this->m_X, x * this->m_Y); }

    friend CCoord operator*(const T x, const CCoord &coord)
    { return CCoord(x * coord.m_X, x * coord.m_Y); }

    CCoord operator/(const T x) const
    {
        if (x == 0) throw std::invalid_argument("Dividing by zero is forbidden!");
        return CCoord(this->m_X / x, this->m_Y / x);
    }

    CCoord operator/=(const T x)
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

    bool operator!=(const CCoord &other) const
    { return !(*this == other); }

    bool AlmostEqual(const CCoord &other) const;


    /**
     * Calculates distance between this and the other point
     * @param a
     * @param b
     * @return Distance between two points.
     */
    double CalcDistnance(const CCoord &other) const;

   /* int GetFlooredX() const
    { return static_cast<int>(this->m_X); }

    int GetFlooredY() const
    { return static_cast<int>(this->m_Y); }*/

    /**
     * Convert Coord to CCoord<double>
     * @return Converted coord.
     */
    CCoord<double> ToDouble() const
    { return CCoord<double>(static_cast<double>(this->m_X), static_cast<double>(this->m_Y)); }

    /**
    * Convert Coord to CCoord<int>
    * @return Converted coord.
    */
    CCoord<int> ToInt() const
    { return CCoord<int>(static_cast< int>(std::floor(this->m_X)), static_cast<int>(std::floor(this->m_Y))); }

    /**
    * Convert Coord to CCoord<unsigned int>
    * @return Converted coord.
    */
    CCoord<unsigned int> ToUnsignedInt() const
    {
        return CCoord<unsigned int>(static_cast< unsigned int>(std::abs(std::floor(this->m_X))),
                                    static_cast<unsigned int>(std::abs(std::floor(this->m_Y))));
    }

    /** Coordinates */
    T m_X;
    T m_Y;
};

template<class T>
bool CCoord<T>::operator<(const CCoord &other) const
{
    if (this->m_X < other.m_X)
    {
        return true;
    } else if (this->m_X == other.m_X && this->m_Y < other.m_Y)
    {
        return true;
    }

    return false;
}

template<class T>
bool CCoord<T>::operator==(const CCoord &other) const
{
    if (this->m_X == other.m_X && this->m_Y == other.m_Y)
    {
        return true;
    }

    return false;
}

template<class T>
bool CCoord<T>::AlmostEqual(const CCoord &other) const
{
    CCoord thisCoord = CCoord(floor(this->m_X), floor(this->m_Y));
    CCoord otherCoord = CCoord(floor(other.m_X), floor(other.m_Y));

    return (thisCoord == otherCoord);
}

template<class T>
double CCoord<T>::CalcDistnance(const CCoord &other) const
{
    return sqrt(
            ((this->m_X - other.m_X) * (this->m_X - other.m_X)) + ((this->m_Y - other.m_Y) * (this->m_Y - other.m_Y)));
}

