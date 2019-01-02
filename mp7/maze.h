#ifndef MAZE_H
#define MAZE_H
#include <vector>

#include "png.h"
#include "rgbapixel.h"
#include "dsets.h"

using namespace std;

class SquareMaze{

public:
 	SquareMaze ();
	void makeMaze (int width, int height);
	bool canTravel (int x, int y, int dir) const;
	void setWall (int x, int y, int dir, bool exists);
	vector< int > solveMaze ();
	PNG* drawMaze () const;
	PNG* drawMazeWithSolution ();

private:
	int maze_width;
	int maze_height;
	int size;

	DisjointSets s;
	vector< bool > rightWall;
	vector< bool > downWall;

};

#endif
