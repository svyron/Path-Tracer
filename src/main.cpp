#include "vec3.h"
#include "colour.h"

#include <iostream> 

int main() 
{
    // describing the image dimensions

    int iwidth = 600; // image width 
    int iheight = 600; // image height 

    // computer should know what the code is about so the below line is for the reason 

    std::cout << "P3\n" << iwidth << " " << iheight << "\n255\n"; 
    
    for (int j = 0 ; j < iheight ; j++) 
    {   
        std::clog << "\rScanlines remaining: " << iheight - j << " " << std::flush; // to show the number of scanlines remaining to be processed in the image, \r is used to return the cursor to the beginning of the line and std::flush is used to flush the output buffer so that the output is displayed immediately
        
        for (int i = 0 ; i < iwidth ; i++) 
        {
            auto pixel_colour = colour(double(i) / (iwidth - 1), double(j) / (iheight - 1), 0); // to create a colour object with the RGB values of the pixel, the RGB values are calculated by dividing the pixel's x and y coordinates by the image width and height respectively, and the blue value is set to 0
        write_colour(std::cout, pixel_colour); // to write the RGB values of the pixel to the output stream in the PPM format, the write_colour() function is called with the output stream and the colour object as arguments
        }
        
    } 
    std::clog << "\rDone                                \n";
    return 0;
} 