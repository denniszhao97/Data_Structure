#ifndef MAZE_H
#define MAZE_H
#include <vector>
#include "dsets.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace std;

class SquareMaze{
	public:
		SquareMaze();
		void makeMaze(int width, int height);
		bool canTravel(int x, int y, int dir) const;
		void setWall(int x, int y, int dir, bool exists);
		vector<int> solveMaze();
    vector<int> solveMazeHelper(vector<int> a, vector<int> b, vector<int> c);
		cs225::PNG * drawMaze() const;
		cs225::PNG * drawMazeWithSolution();
		cs225::PNG * drawMazeWithSolutionCreative();
	private:
		vector<int> downWalls;
    vector<int> rightWalls;
		int width_;
		int height_;
    int size_;
};
#endif
