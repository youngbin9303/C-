#include "scene.h"
#include "png.h"
#include "image.h"
#include "rgbapixel.h"
#include <iostream>

using namespace std;


//Create an new image called _scene along with x-coordinates and y-coordinates. Initialize them by null or zero by for looping. 
//parameter max is used as number of layers in image.

Scene::Scene(int max){

this->max = max;

_scene = new Image*[max];
for(int i= 0; i<max; i++)
{
 _scene[i]=nullptr;
} 
 x_coordi = new int[max];
 y_coordi = new int[max];
for(int j = 0; j<max; j++)
{
 x_coordi[j]=0;
 y_coordi[j]=0;
}
}

//Call clear function in destructor

Scene::~Scene(){

clear();
}

//This clear function is a helper function of destructor. It deletes new scene, new x-coorindates and new y-coordinates and point them to null or zero.

void Scene::clear(){
for(int i = 0; i<max ;i++)
{
   delete _scene[i];
   _scene[i]=nullptr;
}
delete [] _scene;
_scene = nullptr;

delete [] x_coordi;
x_coordi = 0;
delete [] y_coordi;
y_coordi = 0;
}

//Call copy function in copy constructor

Scene::Scene(const Scene & source){
copy(source);
}


//This copy function is a helper function of copy constructor. It creates new scene along with x-coordinates and y-coordinates.
//We initialize new scene and check whether source scene is null or not. If it is not null, copy the source scene to destination scene 
//along with x-coordinates and y-coordinates

void Scene::copy(const Scene &source){

max = source.max;
x_coordi = new int[max];
y_coordi = new int[max];
_scene = new Image*[max];

for(int i = 0; i<max ; i++)
{
     _scene[i] = NULL;
  if (source._scene[i] != NULL)
  {
      _scene[i] = new Image; 
      *(_scene[i])=*(source._scene[i]);
      x_coordi[i]=source.x_coordi[i];
      y_coordi[i]=source.y_coordi[i];
  }
}
}


//This is overloading function for copy constructor
const Scene & Scene::operator= (const Scene &source){

if(this != &source)
{
clear();
copy(source);
}
return *this;
}

//This function checks the number of layers that are not null. If this number of layers are bigger than newmax or lower than 0, it prints error msg.
//Else, make a new layers which will copy the original layers which are not null. If the non null layers are all copied, it copies the null layer to new one 
void Scene::changemaxlayers(int newmax)
{
if(newmax<max)
{
int count=0;
for(int i=0; i<max; i++)
{
 if(_scene[i]!=nullptr)
   count++;

}
if(count<0||count>newmax-1)
{
 cout<<"invalid newmax"<<endl;
return ;
}
}


Image**_newscene = new Image*[newmax];
int* new_x_coordi = new int[newmax];
int* new_y_coordi = new int[newmax]; 
int p = max;

for(int j=0; j<newmax; j++)
{
 if(p>0) 
 {
 *(_newscene[j])=*(_scene[j]);
  new_x_coordi[j] = x_coordi[j];
  new_y_coordi[j] = y_coordi[j];
 }
 else
 {
 _newscene[j] = nullptr;
 new_x_coordi[j] = 0;
 new_y_coordi[j] = 0;
  }
 p--;
}

}


//This image add the input image to the scene. If the destination scene is not null, delete it.
void Scene::addpicture(const char* FileName, int index,int x,int y){
 		
if(index<0||index>max-1)
{
cout<<"index out of bounds"<<endl;
return;
}


Image* getimage = new Image();
getimage -> readFromFile(FileName);

if(_scene[index] != nullptr)
{ 
 delete _scene[index];
}

_scene[index] = getimage;
x_coordi[index] = x;
y_coordi[index] = y;
}

//This image copies source layer and coordinates to destination layer and coordinates
void Scene::changelayer(int index, int newindex){
if(index<0||newindex<0||index>max-1||newindex>max-1)
{
cout<<"invalid index"<<endl;
return;
}
if(index == newindex)
  return; 
      

 if(_scene[newindex]!=nullptr)
{
   delete _scene[newindex];
 _scene[newindex]=nullptr;
}

_scene[newindex] = _scene[index];
 _scene[index] = nullptr;
 x_coordi[newindex] = x_coordi[index];
 y_coordi[newindex] = y_coordi[index];
 x_coordi[index]= 0 ;
 y_coordi[index] = 0 ;
 }

//This function takes xcoord and ycoord to our x and y coordinates in index.
void Scene::translate(int index,int xcoord, int ycoord){
if(index<0||index>max-1||_scene[index] == nullptr)
{
 cout<<"invalid index"<<endl;
 return;
}
x_coordi[index] = xcoord;
y_coordi[index] = ycoord;
}


//This function frees layer and x,y coordinates.
void Scene::deletepicture(int index){
if(index<0||index>max-1||_scene[index] == nullptr)
{
 cout<<"invalid index"<<endl;
 return;
}

delete _scene[index];
_scene[index] = nullptr;
x_coordi[index] = 0;
y_coordi[index] = 0;
}	


//This function returns the specific index of image.
Image* Scene::getpicture(int index)const{
if(index<0||index>max-1)
{
 cout<<"invalid index"<<endl;
 return nullptr;
}
return _scene[index];

}

//This function figure outs the last coordinates of x and y of layers and set a new image with the last coordinates number.
//After that, it sets up the layers into one image.
Image Scene::drawscene()const{

int origin_height = 0;
int origin_width = 0;
int locationheight = 0;
int locationwidth = 0;
for(int i = 0; i < max; i++)
{
  if(_scene[i] != NULL)
  {
	locationwidth = _scene[i]->width()+x_coordi[i];	
	locationheight = _scene[i]->height()+y_coordi[i];
		if(origin_width < locationwidth)
		origin_width = locationwidth;
		if(origin_height < locationheight)
		origin_height = locationheight;
  }
}

	Image image;
	image.resize(origin_width,origin_height);
      
	for(int index = 0; index < max;index++)
	{
		if (_scene[index] != NULL)
		{
	for(int x = 0; x < (int)_scene[index]->width(); x++)
	{
		for(int y = 0; y< (int)_scene[index]->height();y++)
		{
		   //By using rgba operator() bring the content of rgb.
                    *image(x_coordi[index]+x,y_coordi[index]+y) = *(*_scene[index])(x,y); 
                }
            }
        }
    }
    
    return image;

}




