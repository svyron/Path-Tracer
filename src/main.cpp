#include "vec3.h"
#include "colour.h"
#include "ray.h" 

#include <iostream> 

colour ray_colour(const ray& r) 
{
    vec3 unit_direction = unit_vector(r.direction()); 
    auto a = 0.5 * (unit_direction.y() + 1.0); 
    return (1.0-a)*colour(1.0, 1.0, 1.0) + a*colour(0.5, 0.7, 1.0);
} 

int main() 
{
    auto aspect_ratio = 16.0/9.0; 
    int image_width = 400; 

    int image_height = int(image_width / aspect_ratio); // w/h = aspect ratio 
    image_height = image_height < 1 ? 1 : image_height; // to ensure image height is atleast 1 pixel 

    // Defining the camera parameters 
    auto focal_length = 1.0; 
    auto viewport_height = 2.0; 
    auto viewport_width = viewport_height * aspect_ratio; 
    auto camera_center = point3(0, 0, 0); 
    
    auto viewport_u = vec3(viewport_width, 0, 0); 
    // defines the direction of the viewport. This doesn't mean that the vp_v is under the camera. We have to add it to a point to get the actual position of pixel we want to render. 
    auto viewport_v = vec3(0, -viewport_height, 0); 

    auto pixel_delta_u = viewport_u / image_width; 
    auto pixel_delta_v = viewport_v / image_height; 

    // Now to calculate the upper left corner of the viewport. We can do this by taking the camera center and moving it half the width to the left and half the height up. 
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2 ; 
     // the location of the center of the pixel at (0, 0) in the viewport. We can get this by moving half a pixel down and half a pixel to the right from the upper left corner of the viewport. 
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Rendering the image 
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n"; // PPM header 
    for (int j = 0; j < image_height; j++) 
    {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush; // print the number of scanlines remaining to render 
        for (int i = 0; i < image_width; i++) 
        {   
            // i s the column number and j is the row number. We can use these to calculate the location of the pixel in the viewport. 
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v); 
            auto ray_direction = pixel_center - camera_center; 
            ray r(camera_center, ray_direction); 

            colour pixel_colour = ray_colour(r); 
            write_colour(std::cout, pixel_colour); 
        }
    }

}