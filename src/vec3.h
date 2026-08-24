#ifndef VEC3_H
#define VEC3_H 

#include <cmath> 
#include <iostream> 

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

        double operator[](int i) const { return e[i]; } // teaching the exisitng operator ([]) to the vec3 class to access the elements of the vector // "Give me a COPY of the double."

        double& operator[](int i) { return e[i]; } // teaching the existing operator ([]) to the vec3 class to access the elements of the vetor and MODIFY them // "Give me the ORIGINAL double itself, by reference."

    vec3& operator+=(const vec3& v) // teaching the existing operator (+=) to the vec3 class to add another vector 'v' to the vector and modify the vector 
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this; // return the modified vector // 'this' shows the address of the current object while '*this' dereferences the pointer to get the object itself.
    }
    
}; 