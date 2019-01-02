#include "maze.h"
#include <queue>
#include <map>
#include <stack>
using namespace std;
SquareMaze::SquareMaze(){}

void SquareMaze::makeMaze (int width, int height){
	maze_width = width;
	maze_height = height;
	size = width * height;
	s.addelements(size);

	for(int i = 0; i < size; i++){
		rightWall.push_back(true);
		downWall.push_back(true);
	}

		int size = maze_width * maze_height;
		int i = 0;
		//for(int i = 0; i<size; i++){
		while(size > 1){

		int direction = rand() % 2;

		if(direction == 0 && i % maze_width < maze_width - 1 && s.find(i) != s.find(i+1)){
			setWall(i%maze_width, i/maze_width, 0, false);
			s.setunion(i, i+1);
			size--;
		}

		else if(direction == 1 && i/maze_width < maze_height - 1 && s.find(i) != s.find(i+maze_width)){
			setWall(i%maze_width, i/maze_width, 1, false);
			s.setunion(i, i+maze_width);
			size--;			
		}
		i++;
		if (i>=maze_width*maze_height){i = 0;}
	}
}

bool SquareMaze::canTravel (int x, int y, int dir) const
{
	bool flag = false;

	if(dir == 0 && x + 1 < maze_width)
		return (rightWall[y * maze_width + x] == flag);

	if(dir == 1 && y + 1 < maze_height)
		return (downWall[y * maze_width + x] == flag);

	if(dir == 2 && x > 0)
		return (rightWall[y * maze_width + x - 1] == flag);

	if(dir == 3 && y > 0)
		return (downWall[(y - 1) * maze_width + x] == flag);	
	return flag;
}
 	
void SquareMaze::setWall (int x, int y, int dir, bool exists)
{

	if(dir == 0 && x + 1 < maze_width)
			rightWall[y * maze_width + x] = exists;

	if(dir == 1 && y + 1 < maze_height)
			downWall[y * maze_width + x] = exists;
}

vector< int > SquareMaze::solveMaze ()
{
	queue<int> q;
	map<int, int> distance;
	map<int, int> parent;
	vector<bool> processed;
	vector<int> sol;
	vector<int> path;
	distance[0]=0;
	int destination = 0;
	q.push(0);
	int pos, route;

	for (int i=0; i<size; i++){processed.push_back(false);}

	while (!q.empty()) {
		pos = q.front();
		q.pop();
		processed[pos] = true;
		int x_pos = pos%maze_width;
		int y_pos = pos/maze_width;

		if (canTravel(x_pos,y_pos,0) && !processed[pos+1]) {
			distance[pos+1] = distance[pos] + 1;
			parent[pos+1] = pos;
			q.push(pos+1);
		}
		if (canTravel(x_pos,y_pos,1) && !processed[pos+maze_width]) {
			distance[pos+maze_width] = distance[pos] + 1;
			parent[pos+maze_width] = pos;
			q.push(pos+maze_width);
		}
		if (canTravel(x_pos,y_pos,2) && !processed[pos-1]) {
			distance[pos-1] = distance[pos] + 1;
			parent[pos-1] = pos;
			q.push(pos-1);
		}
		if (canTravel(x_pos,y_pos,3) && !processed[pos-maze_width]) {
			distance[pos-maze_width] = distance[pos] + 1;
			parent[pos-maze_width] = pos;
			q.push(pos-maze_width);
		}
	}



	for (map<int, int>::iterator it=distance.begin(); it!=distance.end(); it++) {
		if (it->first >= maze_width*(maze_width-1) && distance[destination] < it->second) 
			destination = it->first;
	}

	while (destination!=0) {
		route = parent[destination];

		if (destination==route+1){path.push_back(0);}
		if (destination==route+maze_width){path.push_back(1);}
		if (destination==route-1){path.push_back(2);}
		if (destination==route-maze_width){path.push_back(3);}
		destination = route;
	}

	while (!path.empty()) {
		sol.push_back(path.back());
		path.pop_back();
	}
	return sol;
}



PNG * SquareMaze::drawMaze () const
{
	PNG * output = new PNG(maze_width*10+1, maze_height*10+1);

	for(int column = 10; column < maze_width*10; column++)
	{
		(*output)(column, 0)->red = 0;	
		(*output)(column, 0)->green = 0;	
		(*output)(column, 0)->blue = 0;	
	}

	for(int row = 0; row < maze_height*10; row++){
		(*output)(0, row)->red = 0;	
		(*output)(0, row)->green = 0;	
		(*output)(0, row)->blue = 0;	
	}


	for(int pos = 0; pos < size; pos++){

		int x_point = pos%maze_width;
		int y_point = pos/maze_width;

		if(rightWall[pos]==true)
		{
			for(int k = 0; k <= 10; k++)
			{
				(*output)((x_point + 1) * 10, y_point * 10 + k)->red = 0;
				(*output)((x_point + 1) * 10, y_point * 10 + k)->green = 0;
				(*output)((x_point + 1) * 10, y_point * 10 + k)->blue = 0;
			}
		}
		if(downWall[pos]==true)
		{
			for(int k = 0; k <= 10; k++)
			{
				(*output)(x_point * 10 + k, (y_point + 1) * 10)->red = 0;
				(*output)(x_point * 10 + k, (y_point + 1) * 10)->green = 0;
				(*output)(x_point * 10 + k, (y_point + 1) * 10)->blue = 0;
			}
		}
		
	}
	return output;
}

PNG * SquareMaze::drawMazeWithSolution ()
{
	PNG * output = drawMaze();
	vector< int > dir = solveMaze();
	int x_start = 5;
	int y_start = 5;
	for(size_t i = 0; i < dir.size(); i++)
	{
		
		if(dir[i] == 0)
		{
			for(int steps = 0; steps < 11; steps++)
			{
				(*output)(x_start + steps, y_start)->red = 255;
				(*output)(x_start + steps, y_start)->green = 0;
				(*output)(x_start + steps, y_start)->blue = 0;
			}
			x_start += 10;
		}
		
		if(dir[i] == 1)
		{
			for(int steps = 0; steps < 11; steps++)
			{
				(*output)(x_start, y_start + steps)->red = 255;
				(*output)(x_start, y_start + steps)->green = 0;
				(*output)(x_start, y_start + steps)->blue = 0;
			}			
			y_start += 10;
		}
		
		if(dir[i] == 2)
		{
			for(int steps = 0; steps < 11; steps++)
			{
				(*output)(x_start - steps, y_start)->red = 255;
				(*output)(x_start - steps, y_start)->green = 0;
				(*output)(x_start - steps, y_start)->blue = 0;				
			}
			x_start -= 10;
		}
		
		if(dir[i] == 3)
		{
			for(int steps = 0; steps < 11; steps++)
			{
				(*output)(x_start, y_start - steps)->red = 255;
				(*output)(x_start, y_start - steps)->green = 0;
				(*output)(x_start, y_start - steps)->blue = 0;	
			}		
			y_start -= 10;
		}
	}


	int x_pos = x_start /10;
	int y_pos = maze_height - 1;
	for(int k = 1; k <= 9; k++)
	{
		(*output)(x_pos * 10 + k, (y_pos + 1) * 10)->red = 255;
		(*output)(x_pos * 10 + k, (y_pos + 1) * 10)->green = 255;
		(*output)(x_pos * 10 + k, (y_pos + 1) * 10)->blue = 255;
	}

	return output;

}


