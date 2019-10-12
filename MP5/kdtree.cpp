/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

/**
*This function should take in two templatized Points
*and a dimension and return a boolean value representing whether or not
*the first Point has a smaller value than the second in the dimension specified.
*That is, if the dimension passed in is kk, then this should be true if the coordinate of the first points
*at kk is less than the coordinate of the second points at kk.
*If there is a tie, break it using Point’s operator<. For example:
**/
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
  if(curDim > Dim || curDim < 0){
      return false;
   }

  if(first[curDim]!=second[curDim]){
       return first[curDim] < second[curDim];
   }
     return first < second;
}

/**
*calculate the distance between two point in the given dim.
**/
template<int Dim>
double KDTree<Dim>::getDistance(const Point<Dim> & point1, const Point<Dim> & point2) const
{
    double distance = 0;
	  for(int i = 0; i < Dim; i++){
      distance += (point1[i]-point2[i])*(point1[i]-point2[i]);
    }
	 return distance;
}
/**
*This function should take three templated Points: target, currentBest,
*and potential. This should return true if potential is closer (i.e., has a smaller distance)
*to target than currentBest (with a tie being broken by the operator< in the Point class: potential < currentBest).
**/
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
          double currentD = getDistance(target, currentBest);
          double potentialD = getDistance(target, potential);
          if(currentD != potentialD){
            return potentialD < currentD;
          }
            return potential < currentBest;
}


/**
* This function devides the vector into two parts from the pivot.
**/
template <int Dim>
int KDTree<Dim>::partition(int start, int end, int pivot, int dimension)
{
    Point<Dim> pivotValue = points[pivot];
    swap(points[pivot], points[end]);
    int pivot_index = start;
    int i = start;
    while(i < end){
        if(smallerDimVal(points[i], pivotValue, dimension)){
            swap(points[pivot_index], points[i]);
            pivot_index++;
        }
        i++;
    }
    swap(points[end], points[pivot_index]);
    return pivot_index;
}


/**
* THis function uses the quicksort algorithm and returns the pivot.
**/
template <int Dim>
int KDTree<Dim>::quickSelect(int start, int end, int pre_mid, int dimension){
  int mid = (start+end)/2;
  int result = partition( start, end, mid, dimension);
  if(result == pre_mid){
    return result;
  }
  if(result < pre_mid){
    return quickSelect(result+1, end, pre_mid, dimension);
  }
  if(result > pre_mid){
    return quickSelect(start, result-1, pre_mid, dimension);
  }
  return 0;
}

/**
* This function is a helper function to recursively build nodes around root and return root.
**/
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::build(int start, int end, int dimension){
  if(start > end){
    return NULL;
  }
  int first_mid = (start+end)/2;
  int mid = quickSelect(start, end, first_mid, dimension);

  KDTreeNode* root_ = new KDTreeNode(points[mid]);
  root_->left = build(start, mid-1, (dimension+1) % Dim);
  root_->right = build(mid+1, end, (dimension+1) % Dim);
  return root_;

}

/**
*This constructor function constructs a KDTree from a vector of Points, each having dimension Dim.
**/
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     points = newPoints;
     if(points.size() == 0){
       root = NULL;
       size = 0;
     }
     root = build(0, points.size()-1, 0);
     size = points.size();
}

/**
*This constructor function constructs a copy of another KDTree.
**/
template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
   root = other.root;
   size = other.size;
   points = other.points;
}
/*
*This function assigns another KDTree's private varibles to this tree.
*/
template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */
   root = rhs.root;
   size = rhs.size;
   points=rhs.points;
   return *this;
}

/**
* This function helps to delete every node in a KDTree.
**/
template <int Dim>
void KDTree<Dim>::Destroy(KDTreeNode* root_) {
  if (root_) {
      Destroy(root_->left);
      Destroy(root_->right);
      delete root_;
  }
}

/**
* This function is the destructor of the KDTree class.
**/
template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */

   Destroy(root);
   root = NULL;
   size = 0;
   points.clear();
}


/**
*This function  search to find the smallest hyperrectangle that contains the target element,
*and then a back traversal to see if any other hyperrectangle could contain a closer point,
*which may be a point with smaller distance or a point with equal distance, but a “smaller” point
**/
template <int Dim>
void KDTree<Dim>::findNearestNeighborHelper(const Point<Dim>& query,
                          Point<Dim>& result,
                          int start, int end, int dimension, double& distance, bool& exists) const
{
  if(start> end){
    return;
  }
  if(start == end){
    if(exists){
      result = points[start];
      distance = getDistance(query, result);
      exists = false;
    } else {
        if (shouldReplace(query, result, points[start])){
          result = points[start];
          distance = getDistance(query, result);
        }
      }
    return;
  }

  int mid = (start+end)/2;
  if(!smallerDimVal(query, points[mid], dimension)){
    findNearestNeighborHelper(query, result, mid+1, end, (dimension+1) % Dim, distance, exists);
    if(shouldReplace(query, result, points[mid])){
      result = points[mid];
      distance = getDistance(result, query);
      exists = false;
    }
    if((points[mid][dimension]- query[dimension])*(points[mid][dimension]- query[dimension])<= distance){
      findNearestNeighborHelper(query, result, start, mid - 1, (dimension+1) % Dim, distance, exists);
    }
  }

  if(smallerDimVal(query, points[mid], dimension)){
    findNearestNeighborHelper(query, result, start, mid-1, (dimension+1) % Dim, distance, exists);
    if(shouldReplace(query, result, points[mid])){
      result = points[mid];
      distance = getDistance(result, query);
      exists = false;
    }
    if((points[mid][dimension]- query[dimension])*(points[mid][dimension]- query[dimension])<= distance){
      findNearestNeighborHelper(query, result, mid+1, end, (dimension+1) % Dim, distance, exists);
    }
  }
}

/**
* This function calls the helper function and find the closest Point.
**/
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> result;
    double minDis = 0;
    bool existed = true;
    findNearestNeighborHelper(query, result, 0, points.size()-1, 0, minDis, existed);
    return result;

}
