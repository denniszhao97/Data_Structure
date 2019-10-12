#include <iterator>
#include <cmath>
#include <stack>
#include <list>
#include "../cs225/PNG.h"
#include "../Point.h"
#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  png_ = png;
  start_ = start;
  tolerance_ = tolerance;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  Iterator it = Iterator();
  it.setpng(this->png_);
  it.setcur(this->start_);
  it.setstart(this->start_);
  it.settol(this->tolerance_);
  it.setTra(this);
  it.setEnd(false);
  it.begin(this->png_);
  return it;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  Iterator it = Iterator();
  it.setpng(this->png_);
  it.setcur(this->start_);
  it.setstart(this->start_);
  it.settol(this->tolerance_);
  it.setTra(this);
  it.setEnd(false);
  it.begin(this->png_);
  it.setEnd(true);
  return it;
  //return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  PointS.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  Point result = PointS.top();
  PointS.pop();
  return result;
  //return Point(0, 0);
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return PointS.top();
  //return Point(0, 0);
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  return PointS.empty();
  //return true;
}
