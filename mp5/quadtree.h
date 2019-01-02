/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
  public:
   
	Quadtree();
	Quadtree(PNG const & source, int resolution);
	Quadtree(Quadtree const & other);
	~Quadtree();
	Quadtree const & operator=(Quadtree const & other);
	void buildTree(PNG const & source, int resolution);
	RGBAPixel getPixel(int x, int y) const;
	PNG decompress() const;
	void clockwiseRotate();
	void prune(int tolerance);
	int pruneSize(int tolerance) const;
	int idealPrune(int numLeaves) const;
        void clear();
	void copy(Quadtree const & other);
	int idealPrune(int numLeaves, int min_tolerance, int max_tolerance) const;
 private:
    /**
     * A simple class representing a single node of a Quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */
    class QuadtreeNode
    {
      public:
        QuadtreeNode* nwChild; /**< pointer to northwest child */
        QuadtreeNode* neChild; /**< pointer to northeast child */
        QuadtreeNode* swChild; /**< pointer to southwest child */
        QuadtreeNode* seChild; /**< pointer to southeast child */

        RGBAPixel element; /**< the pixel stored as this node's "data" */
    };

    QuadtreeNode* root; /**< pointer to root of quadtree */
    int hori_high;
    int hori_low;
    int vert_left;
    int vert_right;

    void clear(QuadtreeNode* croot);
    QuadtreeNode* build(PNG const & source, int hori_high, int hori_low, int vert_left, int vert_right);
    void clockwiseRotate(QuadtreeNode* new_root);
    QuadtreeNode* getPixel(int x, int y, int left, int right, int up, int down, QuadtreeNode* output) const;
    void prune(QuadtreeNode* subRoot, int tolerance);
    bool prune_tree(QuadtreeNode* node1, QuadtreeNode* node2, int tolerance) const;
    QuadtreeNode* copy(QuadtreeNode* const & other);
    int pruneSize(QuadtreeNode* subRoot, int tolerance) const;
    int difference(QuadtreeNode* node1, QuadtreeNode* node2) const;

    
   

    

 
/**** Functions for testing/grading                      ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif

