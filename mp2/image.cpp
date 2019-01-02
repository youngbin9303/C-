#include "image.h"


void Image::flipleft()
{

int width = this->width();
int height = this->height();

// Only went through half of width since it will bring the original file if we go through end of width

for(int y=0; y<height; y++){
   for(int x=0; x<width/2; x++){
       

	//temp = *a
	//*a = *b
	//*b = temp
          
          int tempR = (*this)(width-1-x,y)->red;
          (*this)(width-1-x,y)->red = (*this)(x,y)->red;
          (*this)(x,y)->red = tempR;
          
          int tempG = (*this)(width-1-x,y)->green;
          (*this)(width-1-x,y)->green = (*this)(x,y)->green;
          (*this)(x,y)->green = tempG;
          
          int tempB = (*this)(width-1-x,y)->blue;
          (*this)(width-1-x,y)->blue = (*this)(x,y)->blue;
          (*this)(x,y)->blue = tempB;
   
   }
  }
}

void Image::adjustbrightness(int r, int g, int b){

int width = this->width();
int height = this->height();

// If addition of rgb component is over 255, store it as 255. If addition of rgb component is below 0, store it as 0
// Otherwise stored the result of addition
for(int y=0; y<height; y++){
   for(int x=0; x<width; x++){
           if((*this)(x,y)->red + r>=255)
            (*this)(x,y)->red=255;
           else if((*this)(x,y)->red + r<=0)
             (*this)(x,y)->red=0;
           else
           (*this)(x,y)->red = (*this)(x,y)->red + r;
    
           if((*this)(x,y)->green + g>=255)
            (*this)(x,y)->green=255;
           else if((*this)(x,y)->green + g<=0)
             (*this)(x,y)->green=0;
           else
           (*this)(x,y)->green = (*this)(x,y)->green + g;

           if((*this)(x,y)->blue + b>=255)
            (*this)(x,y)->blue=255;
           else if((*this)(x,y)->blue + b<=0)
             (*this)(x,y)->blue=0;
           else
           (*this)(x,y)->blue = (*this)(x,y)->blue + b;

       } 
   }
}

void Image::invertcolors(){

int width = this->width();
int height = this->height();

//Deduct each rgb component from 255. It will not be less than zero since the maximum value of rgb component is 255

for(int y=0; y<height; y++){
   for(int x=0; x<width; x++){
    (*this)(x,y)->red = 255- (*this)(x,y)->red;
    (*this)(x,y)->green = 255- (*this)(x,y)->green;
    (*this)(x,y)->blue = 255- (*this)(x,y)->blue;
       } 
   }
}
