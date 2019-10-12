#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
   cs225::PNG out(600,600);
   SquareMaze maze1;
   maze1.makeMaze(20, 60);
   cs225::PNG *p = maze1.drawMazeWithSolutionCreative();

   SquareMaze maze2;
   maze2.makeMaze(20, 20);
   cs225::PNG *q = maze2.drawMaze();

   SquareMaze maze3;
   maze3.makeMaze(20, 20);
   cs225::PNG *z = maze3.drawMaze();


   for(int i = 0; i<int(q->width()); i++){
     for(int j = 0; j < int(q->height()); j++){
       out.getPixel(i,j+200).h = q->getPixel(i,j).h;
       out.getPixel(i,j+200).s = q->getPixel(i,j).s;
       out.getPixel(i,j+200).l = q->getPixel(i,j).l;
       out.getPixel(i,j+200).a = q->getPixel(i,j).a;
     }
   }
   for(int i = 0; i<int(p->width()); i++){
     for(int j = 0; j < int(p->height())-1; j++){
       out.getPixel(i + 200,j).h = p->getPixel(i,j).h;
       out.getPixel(i + 200,j).s = p->getPixel(i,j).s;
       out.getPixel(i + 200,j).l = p->getPixel(i,j).l;
       out.getPixel(i + 200,j).a = p->getPixel(i,j).a;
     }
   }
   for(int i = 0; i<int(z->width())-1; i++){
     for(int j = 0; j < int(z->height()); j++){
       out.getPixel(i+400,j+200).h = z->getPixel(z->width()-1 - i,j).h;
       out.getPixel(i+400,j+200).s = z->getPixel(z->width()-1 - i,j).s;
       out.getPixel(i+400,j+200).l = z->getPixel(z->width()-1 - i,j).l;
       out.getPixel(i+400,j+200).a = z->getPixel(z->width()-1 - i,j).a;
     }
   }

     for(int j = 199; j < 400; j += 20){
       for(int k = 0; k<11; k++){
         out.getPixel(400 ,j+k).h = 0;
         out.getPixel(400 ,j+k).s = 0;
         out.getPixel(400 ,j+k).l = 1;
         out.getPixel(400 ,j+k).a = 1;
       }
     }

     for(int j = 199; j < 400; j += 20){
       for(int k = 0; k<11; k++){
         out.getPixel(200 ,j+k).h = 0;
         out.getPixel(200 ,j+k).s = 0;
         out.getPixel(200 ,j+k).l = 1;
         out.getPixel(200 ,j+k).a = 1;
       }
     }
   out.writeToFile("Creative"+ string(".png"));
   return 0;
}
