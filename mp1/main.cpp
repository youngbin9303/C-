/* For this mp, I used rgbapixel.h and rgbapixel.cpp files from lab_intro. For makefile I used the one from lab_intro and changed to
execution file name to mp1. 
*/
#include <iostream>

#include "png.h"
#include "rgbapixel.h"

using namespace std;


//PNG rotate(PNG inputImage, PNG outputImage){
PNG transform_xray(PNG original){
// It goes through every pixel of image 

 for (size_t yi = 0; yi < original.height(); yi++) 
	{
        for (size_t xi = 0; xi < original.width(); xi++) 
		{

// outputImage pixel deducts 1 for each coordinatet since for loop starts from zero.
//(0,0) pixel rgba of inputImage goes to last coordinate of outputImage
		//outputImage(inputImage.width()-xi-1,inputImage.height()-yi-1)->red = inputImage(xi,yi)->red;
		original(xi, yi)->red = original(xi,yi)->red;
		//outputImage(inputImage.width()-xi-1,inputImage.height()-yi-1)->green = inputImage(xi,yi)->green;
		original(xi, yi)->green = original(xi,yi)->green;
		//outputImage(inputImage.width()-xi-1,inputImage.height()-yi-1)->blue = inputImage(xi,yi)->blue;
		original(xi, yi)->blue = original(xi,yi)->blue;
		//outputImage(inputImage.width()-xi-1,inputImage.height()-yi-1)->alpha = inputImage(xi,yi)->alpha;
		original(xi, yi)->alpha = original(xi,yi)->alpha;
		}
	}
// Finally it returns out.png
	return original;
}

int main () {

// I followed the format from main.cpp file in lab_intro

	PNG image("in.png");
	PNG out("in.png");	// Borrow in.png for PNG out in order to set the height and width same as input image
// This function calls Rotate function to rotate the image by 180 degree.
	image = transform_xray(image); 

// Last line of main.cpp is from lab_intro to print output image
	image.writeToFile("out.png");
	return 0;
}
