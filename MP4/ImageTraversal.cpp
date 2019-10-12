#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
using namespace std;
/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */

double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  EndorNot = false;
}
void ImageTraversal::Iterator::begin(PNG png){
  for(unsigned i=0; i<png.width()*png_.height(); i++){
    visited.push_back(true);
  }

  if(cur_.x < png_.width()){
    if( cur_.y < png_.height()){
      visited[cur_.x*png_.height() + cur_.y] = false;
    }
    else{
      EndorNot = true;
    }
  } else{
    EndorNot = true;
  }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
void ImageTraversal::Iterator::addable(){
  if (!traversal_->empty()) {
    Point next = traversal_->pop();
    while (visited[next.x*png_.height()+next.y] == false) {
      if (traversal_->empty()) {
      setEnd(true);
      return;
      } else{
        next = traversal_->pop();
      }
    }
    cur_ = next;
    visited[cur_.x*png_.height() + cur_.y] = false;
    PointV.push_back(cur_);
    return;
  } else {
    setEnd(true);
    return;
  }
}

ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  int x = cur_.x;
  int y = cur_.y;

  if(visitable(Point(x+1, y))){
    traversal_->add(Point(x+1, y));
  }
  if(visitable(Point(x, y+1))){
    traversal_->add(Point(x, y+1));
  }

  if(visitable(Point(x-1, y))){
    traversal_->add(Point(x-1, y));
  }
  if(visitable(Point(x, y-1))){
    traversal_->add(Point(x, y-1));
  }
  addable();
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {

  return cur_;
  /*return cur_;*/
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  //cout<< "fifth"<<endl;
  bool result = (EndorNot != other.EndorNot);
  return result;
}


bool ImageTraversal::Iterator::visitable(Point Q){
  if(Q.x>=png_.width() || Q.y>=png_.height() || visited[Q.x*png_.height() + Q.y] == false){
    return false;
  }

  HSLAPixel & pixel1 = png_.getPixel(start_.x, start_.y);
  HSLAPixel & pixel2 = png_.getPixel(Q.x, Q.y);
  if(calculateDelta(pixel1, pixel2) < tolerance_){
    return true;
  }
  return false;
}



void ImageTraversal::Iterator::setEnd(bool end){
  EndorNot = end;
}
