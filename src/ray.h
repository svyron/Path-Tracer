#ifndef RAY_H 
#define RAY_H 

#include "vec3.h" 

class ray 
{
    public: 
        ray() {} // default constructor to initialize the ray with no origin or direction 
   
        // constructor to initialize the ray with an origin and direction 
        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {} 

        const point3& origin() const {return orig;} // getter for the origin of the ray 
        const vec3& direction() const {return dir;} // getter for the direction of the ray 

        point3 at(double t) const{return orig + t*dir;} // return the point along the ray at a distance 't' from the origin in the direction of the ray
        
        private: 
            point3 orig; 
            vec3 dir; 


};

#endif