/**
 * @file ImageTraversal.h
 */
#ifndef IMAGETRAVERSAL_H
#define IMAGETRAVERSAL_H

#include <iterator>
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

using namespace cs225;

/**
 * A base class for traversal algorithms on images.
 *
 * BFS and DFS will inherit from this class
 *
 * Each derived class must maintain an ordering of points on an image,
 * through calls to the virtual member functions `add` and `pop`.
 *
 * A derived class provides a traversal by returning instances of
 * ImageTraversal::Iterator.
 */
class ImageTraversal {
public:
  /**
   * A forward iterator through an ImageTraversal.
   */
  class Iterator : std::iterator<std::forward_iterator_tag, Point> {
  public:
    Iterator();
    Iterator(PNG png, Point start, double tolerance, ImageTraversal* traversal);
    Iterator & operator++();
    Point operator*();
    bool operator!=(const Iterator &other);
    bool visitable(Point Q);
    void addable();
    void setEnd(bool end);
    void setpng(PNG png){
      png_ = png;
    }
    void setstart(Point Q){
      start_ = Q;
    }
    void setcur(Point Q){
      cur_ = Q;
    }
    void settol(double tolerance){
      tolerance_ = tolerance;
    }
    void setTra(ImageTraversal* t){
      traversal_ = t;
    }
    void begin(PNG png);

  private:
    PNG png_;
    Point start_;
    Point cur_;
    double tolerance_;
    ImageTraversal* traversal_;
    bool EndorNot;
    vector <Point> PointV;
    vector <bool> visited;
    /** @todo [Part 1] */
    /** add private members here if neccesary*/

  };

  /**
   * The begining of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator begin() = 0;

  /**
   * The end of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator end() = 0;

  /**
   * Add new point to the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual void add(const Point & t) = 0;
  /**
   * Remove and return the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point pop() = 0;
  /**
   * Return but not remove the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point peek() const = 0;
  /**
   * To see if the traversal has no points left
   * Virtual function. Derived class need to implement this
   */
  virtual bool empty() const = 0;

private:
  static double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);
};




#endif
