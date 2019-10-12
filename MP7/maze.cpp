/* Your code here! */
#include <vector>
#include <queue>
#include "maze.h"
#include "dsets.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace std;

/*
*No-parameter constructor.
*/
SquareMaze::SquareMaze():width_(0), height_(0), size_(0){

}
/*
*Makes a new SquareMaze of the given height and width.
If this object already represents a maze it will clear
all the existing data before doing so. You will start with
a square grid (like graph paper) with the specified height and width.
You will select random walls to delete without creating a cycle, until
there are no more walls that could be deleted without creating a cycle.
Do not delete walls on the perimeter of the grid.
*/
void SquareMaze::makeMaze(int width, int height){
  width_ = width;
  height_ = height;
  size_ = width * height;
  downWalls = vector<int>(size_,1);
	rightWalls = vector<int>(size_,1);

  DisjointSets pointSets;
  pointSets.addelements(size_);
  srand(time(NULL) + rand()%100 );

  for(int removed = 0; removed < size_ - 1;){
    int counter = 0;
    while (counter < size_ - 1) {
      int random = rand()%2;
      if (random == 0 && (counter < size_ - width_)){
        if (pointSets.find(counter) != pointSets.find(counter + width_)){
          pointSets.setunion(counter, counter + width_);
          downWalls[counter] = 0;
          removed ++ ;
        }
      }

      if (random == 1 && (counter + 1) % width_ != 0){
        if (pointSets.find(counter) != pointSets.find(counter + 1)){
          pointSets.setunion(counter, counter + 1);
          rightWalls[counter] = 0;
          removed ++ ;
        }
      }

     counter++;
    }
  }
}

/*
*This uses your representation of the maze to determine whether it is
possible to travel in the given direction from the square at coordinates (x,y).
*/
bool SquareMaze::canTravel(int x, int y, int dir) const
{
  if(x < 0 || y < 0 || x >= width_ || y >= height_){
    return false;
  }
	int index = x + y * width_;
  if (dir == 0 ){
    if(x == width_ - 1){
      return false;
    } else {
      return rightWalls[index] == 0;
    }
  }
  else if (dir == 1 ){
    if( y == height_ - 1){
       return false;
    } else {
      return downWalls[index] == 0;
    }
  }
  else if (dir == 2 ){
    if(x == 0){
      return false;
    } else {
      return rightWalls[index-1] == 0;
    }
  }
  else if (dir == 3){
    if(y == 0){
      return false;
    } else {
      return downWalls[index - width_] == 0;
    }
  }

	return false;


}
/*
*Sets whether or not the specified wall exists.
*/
void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
	int index = x + y * width_;
	if(dir == 0){
    if(exists){
      rightWalls[index] = 1;
    } else {
      rightWalls[index] = 0;
    }
  }

  if(dir == 1){
      if(exists){
        downWalls[index] = 1;
      } else {
        downWalls[index] = 0;
      }
    }
}
/*
*solve helper to return the solution
*/
vector<int> SquareMaze::solveMazeHelper(vector<int> a, vector<int> b, vector<int> c){
  int end = 0;
  int temp = 0;
  for (int i = size_ - width_; i < size_; i++) {
    if (c[i] > temp) {
      temp = c[i];
      end = i;
    }
  }

  vector<int> result(temp + 1, -1);
  while (end > 0) {
    result[temp] = a[end];
    end = b[end];
    temp --;
  }
  return result;
}
/*
*Solves this SquareMaze.
For each square on the bottom row (maximum y coordinate),
there is a distance from the origin (i.e. the top-left cell),
which is defined as the length (measured as a number of steps)
of the only path through the maze from the origin to that square.

Select the square in the bottom row with the largest distance from the origin
 as the destination of the maze. solveMaze() returns the winning path from the
 origin to the destination as a vector of integers, where each integer represents
 the direction of a step, using the same encoding as in canTravel().

If multiple paths of maximum length exist, use the one with the destination cell that has the smallest x value.
Hint: this function should run in time linear in the number of cells in the maze.
*/
vector<int> SquareMaze::solveMaze(){
  vector<int> direction(size_, -1);
  vector<int> indexs(size_, -1);
  vector<int> visited(size_, -1);
  queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int first = q.front();
    if (canTravel(first % width_,first / width_,0) && visited[first + 1] == -1){
        indexs[first + 1] = first;
        direction[first + 1] = 0;
        visited[first + 1] = visited[first] + 1;
        q.push(first + 1);
    }
    if (canTravel(first % width_,first / width_,1) && visited[first + width_] == -1){
        indexs[first + width_] = first;
        direction[first + width_] = 1;
        visited[first + width_] = visited[first] + 1;
        q.push(first + width_);
    }
    if (canTravel(first % width_,first / width_,2) && visited[first - 1] == -1){
        indexs[first - 1] = first;
        direction[first - 1] = 2;
        visited[first - 1] = visited[first] + 1;
        q.push(first - 1);
    }
    if (canTravel(first % width_,first / width_,3) && visited[first - width_] == -1){
        indexs[first - width_] = first;
        direction[first - width_] = 3;
        visited[first - width_] = visited[first] + 1;
        q.push(first - width_);
    }
    q.pop();
  }

  vector<int> result = solveMazeHelper(direction, indexs, visited);
  direction.clear();
  indexs.clear();
  visited.clear();
  return result;
}

/*
 Draws the maze without the solution.
 First, create a new PNG.
 Set the dimensions of the PNG to (width*10+1,height*10+1).
 where height and width were the arguments to makeMaze.
 Blacken the entire topmost row and leftmost column of pixels, except the entrance (1,0) through (9,0).
 For each square in the maze, call its maze coordinates (x,y).
 If the right wall exists, then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10.
 If the bottom wall exists, then blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.
 The resulting PNG will look like the sample image,
 except there will be no exit from the maze and the red line will be missing.
 */
 cs225::PNG * SquareMaze::drawMaze () const{
   cs225::PNG * result = new cs225::PNG(width_*10+1,height_*10+1);
   for(int i = 0; i < height_ * 10; i++){
	    result->getPixel(0,i).h = 0;
		  result->getPixel(0,i).s = 0;
	    result->getPixel(0,i).l = 0;
      result->getPixel(0,i).a = 1;
	 }
   for(int j = 10; j < width_*10; j++){
     result->getPixel(j, 0).h = 0;
     result->getPixel(j, 0).s = 0;
     result->getPixel(j, 0).l = 0;
     result->getPixel(j, 0).a = 1;
	 }

   for(int m = 0; m < size_; m++){
		 int x = m % width_;
		 int y = m / width_;
  	 if(rightWalls[m]){
    	  for(int k = 0; k < 11; k++){
           result->getPixel(10*x + 10, 10*y + k).h = 0;
           result->getPixel(10*x + 10, 10*y + k).s = 0;
           result->getPixel(10*x + 10, 10*y + k).l = 0;
           result->getPixel(10*x + 10, 10*y + k).a = 1;
  	 	  }
  	 }
		 if(downWalls[m]){
			 for(int k = 0; k <= 10; k++){
         result->getPixel(10*x + k, 10*y + 10).h = 0;
         result->getPixel(10*x + k, 10*y + 10).s = 0;
         result->getPixel(10*x + k, 10*y + 10).l = 0;
         result->getPixel(10*x + k, 10*y + 10).a = 1;
			 }
		}
	}
  return result;
 }


 /**
 *This function calls drawMaze, then solveMaze;
 *it modifeis the PNG from drawMaze to show the solution vector and the exit.
 *Start at pixel (5,5).
 *Each direction in the solution vector corresponds to a trail of 11 red pixels in the given direction.
 *If the first step is downward, color pixels (5,5) through (5,15) red. (Red is 255,0,0 in RGB).
 *Then if the second step is right, color pixels (5,15) through (15,15) red.
 *Then if the third step is up, color pixels (15,15) through (15,5) red.
 *Continue in this manner until you get to the end of the solution vector,
 *so that your output looks analogous the above picture.
 *Make the exit by undoing the bottom wall of the destination square:
 *call the destination maze coordinates (x,y),
 *and whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
 *Returns
 *a PNG of the solved SquareMaze
 */
cs225::PNG * SquareMaze::drawMazeWithSolution(){
  cs225::PNG * result = drawMaze();
  vector<int> solution = solveMaze();
  int x = 5;
  int y = 5;

  for(size_t i = 0; i < solution.size(); i++){
		if(solution[i] == 0){
			for(int j = 0; j < 11; j++){
				result->getPixel(x + j, y).h = 0;
				result->getPixel(x + j, y).s = 1;
				result->getPixel(x + j, y).l = 0.5;
        result->getPixel(x + j, y).a = 1;
			}
			x += 10;
		}
		else if(solution[i] == 1){
			for(int j = 0; j < 11; j++){
        result->getPixel(x, y + j).h = 0;
				result->getPixel(x, y + j).s = 1;
				result->getPixel(x, y + j).l = 0.5;
        result->getPixel(x, y + j).a = 1;
			}
			y += 10;
		}
		else if(solution[i] == 2){
			for(int j = 0; j < 11; j++){
        result->getPixel(x - j, y).h = 0;
				result->getPixel(x - j, y).s = 1;
				result->getPixel(x - j, y).l = 0.5;
        result->getPixel(x - j, y).a = 1;
			}
			x -= 10;
		}
		else if(solution[i] == 3){
			for(int j = 0; j < 11; j++){
        result->getPixel(x, y - j).h = 0;
				result->getPixel(x, y - j).s = 1;
				result->getPixel(x, y - j).l = 0.5;
        result->getPixel(x, y - j).a = 1;
			}
			y -= 10;
		}
	}
	int exitX= x - 5;
	int exitY = height_ * 10;
	for(int i = 1; i < 10; i++){
    result->getPixel(exitX+ i, exitY).h = 0;
    result->getPixel(exitX+ i, exitY).s = 0;
    result->getPixel(exitX+ i, exitY).l = 1;
    result->getPixel(exitX+ i, exitY).a = 1;
	}

	return result;
}
/*
* make rainbow solution
*/

cs225::PNG * SquareMaze::drawMazeWithSolutionCreative(){
  cs225::PNG * rainbowResult = drawMaze();
  vector<int> rainbowSolution = solveMaze();
  int x = 5;            //initial pixel
  int y = 5;
  int rainbow = 0;
  for(size_t i = 0; i < rainbowSolution.size(); i++){
		if(rainbowSolution[i] == 0){
			for(int j = 0; j < 11; j++){
				rainbowResult->getPixel(x + j, y).h = rainbow % 360;
				rainbowResult->getPixel(x + j, y).s = 1;
				rainbowResult->getPixel(x + j, y).l = 0.5;
        rainbowResult->getPixel(x + j, y).a = 1;
        rainbow++;
			}
			x += 10;
		}
		else if(rainbowSolution[i] == 1){
			for(int j = 0; j < 11; j++){
        rainbowResult->getPixel(x, y + j).h = rainbow % 360;
				rainbowResult->getPixel(x, y + j).s = 1;
				rainbowResult->getPixel(x, y + j).l = 0.5;
        rainbowResult->getPixel(x, y + j).a = 1;
        rainbow++;
			}
			y += 10;
		}
		else if(rainbowSolution[i] == 2){
			for(int j = 0; j < 11; j++){
        rainbowResult->getPixel(x - j, y).h = rainbow % 360;
				rainbowResult->getPixel(x - j, y).s = 1;
				rainbowResult->getPixel(x - j, y).l = 0.5;
        rainbowResult->getPixel(x - j, y).a = 1;
        rainbow++;
			}
			x -= 10;
		}
		else if(rainbowSolution[i] == 3){
			for(int j = 0; j < 11; j++){
        rainbowResult->getPixel(x, y - j).h = rainbow % 360;
				rainbowResult->getPixel(x, y - j).s = 1;
				rainbowResult->getPixel(x, y - j).l = 0.5;
        rainbowResult->getPixel(x, y - j).a = 1;
        rainbow++;
			}
			y -= 10;
		}
	}
	int exit_x = x - 5;
	int exit_y = height_*10;
  //cout<<exit_y
	for(int i = 1; i < 10; i++){
    rainbowResult->getPixel(exit_x + i, exit_y).h = 0;
    rainbowResult->getPixel(exit_x + i, exit_y).s = 0;
    rainbowResult->getPixel(exit_x + i, exit_y).l = 1;
    rainbowResult->getPixel(exit_x + i, exit_y).a = 1;
	}

	return rainbowResult;
}
