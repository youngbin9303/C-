/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */  
    int rows = theSource.getRows();
    int columns = theSource.getColumns();		
    MosaicCanvas * Final = new MosaicCanvas(rows, columns);
    vector <Point<3>> V_RGB; 
    map <Point<3>, int> V_map;
     for(size_t i = 0; i < theTiles.size(); i++)
     {
      RGBAPixel tempRGB = theTiles[i].getAverageColor();
      double RGBArray [3];
      RGBArray [0]= tempRGB.red;
      RGBArray [1]= tempRGB.green;
      RGBArray [2]= tempRGB.blue; 
      Point <3> tempArray(RGBArray);
      V_RGB.push_back(tempArray);
     }
     for(size_t i = 0; i < V_RGB.size(); i++)
     {
      V_map[V_RGB[i]] = i;
     }
     KDTree <3> sourceTree(V_RGB);

     for(int x = 0; x < rows; x++)
     {
      for(int y = 0; y < columns; y++)
      {
       RGBAPixel originalRGB = theSource.getRegionColor(x, y);
       double pixelArray [3];
       pixelArray [0]= originalRGB.red;
       pixelArray [1]= originalRGB.green;
       pixelArray [2]= originalRGB.blue;  
       Point <3> FinalPoint(pixelArray);
       Point <3> Final_image = sourceTree.findNearestNeighbor(FinalPoint);
       int findIndex = V_map[Final_image];
       TileImage findImage = theTiles[findIndex];			
       Final->setTile(x, y, findImage); 
      }
     }	
     return Final;
}
