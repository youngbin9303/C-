/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include "math.h"
using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim] == second[curDim])
      return (first < second);
 
    else
      return (first[curDim] < second[curDim]);
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double curr_dist = 0;
     double poten_dist = 0;
    for(int i = 0; i < Dim; i++)
    {
     curr_dist += ((currentBest[i] - target[i])*(currentBest[i] - target[i]));
     poten_dist += ((potential[i] - target[i])*(potential[i] - target[i]));
    }
     if(curr_dist == poten_dist)
       return(potential < currentBest);
     else
       return(curr_dist > poten_dist);
}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     points = newPoints;
     buildTree(0, int(points.size()-1), 0);
}

template <int Dim>
void KDTree<Dim>::buildTree(int left, int right, int dimension)
{
    int mid = (left + right)/2;
 
    quickSelect(left, right, mid, dimension);
    if (left < mid - 1)
        buildTree(left, mid-1, (dimension+1)%Dim);
    if (right > mid + 1)
        buildTree(mid+1, right, (dimension+1)%Dim);

}

template <int Dim>
void KDTree<Dim>::quickSelect(int left, int right, int mid, int dimension)
{
     if(left >= right)        
         return;
     int pivotIndex = partition(left, right, mid, dimension);
     
     if(mid == pivotIndex)
       return;
     else if (mid < pivotIndex)
         return quickSelect(left, pivotIndex - 1, mid, dimension);
     else
         return quickSelect(pivotIndex + 1, right, mid, dimension);
}

template <int Dim>
int KDTree<Dim>::partition(int left, int right, int pivotIndex, int dimension)
{
     Point<Dim> pivotValue = points[pivotIndex];
     swap (points[pivotIndex], points[right]);  
     int storeIndex = left;
     for(int i = left; i< right; i++)
     {
         if(smallerDimVal(points[i], pivotValue, dimension))
           {
             swap(points[storeIndex], points[i]);
             storeIndex++;
           }
      }
     swap(points[right], points[storeIndex]);  
     return storeIndex;
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    int left = 0;
    int right = points.size() - 1;
    int closest = 0;
    bool first_trial = true;
    Point<Dim> currentBest;
    findNearestNeighbor_helper(query, currentBest, left, right, closest, 0, first_trial);
    
    return currentBest;
}

template <int Dim>
void KDTree<Dim>::findNearestNeighbor_helper(const Point<Dim>& query, Point<Dim>& currentBest, int left, int right, int closest, int dimension, bool& first_trial) const
{
	
    if (left >= right){
        if (first_trial){
            first_trial = false;
            currentBest = points[right];
        }
        else{
            if (shouldReplace(query, currentBest, points[left]))
                currentBest = points[left];
        }
        return;
    }

	double a = 0;
    if (smallerDimVal(query, points[(left+right)/2], dimension) != 0){
        findNearestNeighbor_helper(query, currentBest, left, ((left+right)/2)-1, closest, (dimension+1)%Dim, first_trial);
        if (shouldReplace(query, currentBest, points[((left+right)/2)]) != 0)
            currentBest = points[((left+right)/2)];

		for (int i=0; i<Dim; i++){
			a = a + (query[i] - currentBest[i])*(query[i] - currentBest[i]); 
		}
        closest = a;
        if (pow((query[dimension] - points[((left+right)/2)][dimension]), 2) <= closest)
            findNearestNeighbor_helper(query, currentBest, ((left+right)/2)+1, right, closest, (dimension+1)%Dim, first_trial);
    }
    else
    {
        findNearestNeighbor_helper(query, currentBest, ((left+right)/2)+1, right, closest, (dimension+1)%Dim, first_trial);
        if (shouldReplace(query, currentBest, points[((left+right)/2)]) != 0)
            currentBest = points[((left+right)/2)];
		for (int i=0; i<Dim; i++){
			a = a + (query[i] - currentBest[i])*(query[i] - currentBest[i]); 
		}
        closest = a;
        if (pow((query[dimension] - points[((left+right)/2)][dimension]), 2) <= closest)
            findNearestNeighbor_helper(query, currentBest, left, ((left+right)/2)-1, closest, (dimension+1)%Dim, first_trial);
    }
}


