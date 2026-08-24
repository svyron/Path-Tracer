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
            auto r = double(i) / (iwidth - 1); // normalised red value | (iwidth - 1) cause pixels start from 0 to (iwidth - 1) and also to normalize the value of a pixel to be between 0 and 1
            auto g = double(j) / (iheight - 1); // normalised green value
            auto b = 0.00; // normalised blue value (no blue in this image) 

            int ir = int(255.999 * r); // convert the normalized color value (0-1) to the PPM range (0-255)
            int ig = int(255.999 * g); 
            int ib = int(255.999 * b); 

            std::cout << ir << " " << ig << " " << ib << "\n"; // printing the pixel values to the console 
        } 
        
    } 
    std::clog << "\rDone                                \n";
    return 0;
} 