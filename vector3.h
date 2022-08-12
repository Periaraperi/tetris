#pragma once

#include <math.h>

template<class T>
struct Vector3 {
    T x;
    T y;
    T z;

    Vector3() :x(0.0f),y(0.0f),z(0.0f)           {                                                             }
    Vector3(T xx, T yy, T zz) :x(xx),y(yy),z(zz) {                                                             }
    ~Vector3()                                   {                                                             }
    Vector3  operator+(const Vector3&   rhs)     {return Vector3(x+rhs.x, y+rhs.y, z+rhs.z);                   }
    Vector3  operator-(const Vector3&   rhs)     {return Vector3(x-rhs.x, y-rhs.y, z-rhs.z);                   }
    Vector3  operator*(const T&         rhs)     {return Vector3(x*rhs, y*rhs, z*rhs);                         }
    Vector3& operator+=(const Vector3&  rhs)     {this->x+=rhs.x; this->y+=rhs.y; this->z+=rhs.z; return *this;}
    Vector3& operator-=(const Vector3&  rhs)     {this->x-=rhs.x; this->y-=rhs.y; this->z-=rhs.z; return *this;}
    Vector3& operator*=(const T&        rhs)     {this->x*=rhs;   this->y*=rhs;   this->z*=rhs;   return *this;}
    Vector3 norm()                               {T r = 1.0f/mag(); return Vector3(x*r,y*r,z*r);               }
    T mag()                                      {return sqrt(x*x+y*y+z*z);                                    }
    T dot(const Vector3& rhs)                    {return this->x*rhs.x+this->y*rhs.y;                          }
};