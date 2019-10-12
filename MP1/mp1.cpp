#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <cmath>
#include <iostream>

using namespace cs225;


void rotate(std::string inputFile, std::string outputFile) {
  // Part 2
  PNG* original = new PNG();
  original-> readFromFile(inputFile);
  int width  = original->width();
  int height = original->height();

  PNG* rotated = new PNG(width, height);

  for (int x = 0; x<width; x++) {
    for (int y = 0; y<height; y++) {
      HSLAPixel* prev = (*original).getPixel(width-x-1, height-y-1);
      HSLAPixel* currOutPixel = (*rotated).getPixel(x, y);
      *currOutPixel = *prev;
    }
  }
  rotated->writeToFile(outputFile);
  delete rotated;
  delete original;
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // Part 3
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel* pixel = png.getPixel(x, y);
        int d = sqrt((x-400)*(x-400) + (y-400)*(y-400));
        int randh = d % 60 + 155;
        (*pixel).h = randh;
        (*pixel).s = (double) (d % 50) / 100 + 0.2;
        (*pixel).l = (double) (d % 50) / 100 + 0.2;
        (*pixel).a = 1.0;

    }
  }
  return png;
}
