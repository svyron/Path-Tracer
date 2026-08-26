#ifndef VEC3_H
#define VEC3_H 

#include <cmath> 
#include <iostream> 

// defining a class called vec3 to represent a 3D vector with x, y, z components and various operations that can be performed on it.
class vec3 
{
    public:
        double e[3]; // create an array of 3 doubles to store the x, y, z values of the vector 

        vec3() : e{0, 0, 0} {} // default constructor to initialize the vector to (0, 0, 0)
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {} // constructor to initialize the vector to (e0, e1, e2) 

        double x() const { return e[0]; } // getter for the x value of the vector
        double y() const { return e[1]; } // getter for the y value of the vector
        double z() const { return e[2]; } // getter for the z value of the vector 

        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); } // teaching the existing operator (-) to the vec3 class to negate the vector 

        // teaching the exisitng operator ([]) to the vec3 class to access the elements of the vector // "Give me a COPY of the double."
        double operator[](int i) const { return e[i]; } 

        // teaching the existing operator ([]) to the vec3 class to access the elements of the vetor and MODIFY them 
        // "Give me the ORIGINAL double itself, by reference."
        double& operator[](int i) { return e[i]; } 

        // teaching the existing operator (+=) to the vec3 class to add another vector 'v' to the vector and modify the vector
        vec3& operator+=(const vec3& v)  
        {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this; // return the modified vector // 'this' shows the address of the current object while '*this' dereferences the pointer to get the object itself.
        }
    
        // teaching the existing operator (*=) to the vec3 class to multiply the vector by a scalar 't' and modify the vector 
        vec3& operator*=(const double t) 
        {
            e[0] *= t; 
            e[1] *= t; 
            e[2] *= t; 
            return *this; // return the modified vector 
        } 
        
        // teaching the existing operator (/=) to the vec3 class to divide the vector by a scalar 't' and modify the vector 
        vec3& operator /=(const double t) 
        {
            return *this *= 1/t; // return the modified vector 
        } 

        double length() const // to calculate the length of the vector 
        {
            return std::sqrt(length_squared()); // length_squared() is defined below and std::sqrt() is used to calculate the square root of the length_squared()
        } 
        
        double length_squared() const 
        {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; // return the sum of squares of the x, y, z values of the vector
        }
}; 

// point3 is an alias of vec3, it represents a point in the 3D space // used an alias cause both use the same data structure but have different meanings, so to avoid confusion, we use an alias 
using point3 = vec3;

// teaching the existing operator (<<) to the vec3 class to print the vector to the console 
// left side of comma is the output stream, right side is the vector to be printed 
inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2]; // print the x, y, z values of the vector to the console 
} 

// teaching the existing operator (+) to the vec3 class to add two vectors and return the result as a new vector 
inline vec3 operator+(const vec3& u, const vec3& v) 
{
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]); // return a new vector with the sum of the x, y, z values of the two vectors 
}

inline vec3 operator-(const vec3& u, const vec3& v) 
{
    return vec3(v.e[0] - u.e[0], v.e[1] - u.e[1], v.e[2] - u.e[2]); // return a new vector with the difference of the x, y, z values of the two vectors 
}

inline vec3 operator*(const vec3& u, const vec3& v) 
{
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]); 
}

inline vec3 operator*(double t, const vec3& v) 
{
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]); 
}

inline vec3 operator*(const vec3& v, double t) 
{
    return t * v; 
}

inline vec3 operator/(const vec3& v, double t) 
{
    return v * (1/t);  
}

inline double dot(const vec3& u, const vec3& v) 
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2]; 
}

inline vec3 cross(const vec3& u, const vec3& v) 
{
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]); 
}

inline vec3 unit_vector(const vec3& v) 
{
    return v / v.length(); 
}

#endif 