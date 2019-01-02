/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */
#include "quadtree.h"
#include "math.h"

Quadtree::Quadtree(){
	root = NULL;
}

Quadtree::Quadtree(PNG const & source, int resolution){
	if (resolution == 0){root = NULL;}
	else{
		hori_high = 0;
		hori_low = resolution;
		vert_left = 0;
		vert_right = resolution;
		root = build(source, hori_high, hori_low, vert_left, vert_right);
		}
}
void Quadtree::buildTree(PNG const & source, int resolution){
	clear();
	if (resolution == 0){root = NULL;}
	else{
	hori_high = 0;
	hori_low = resolution;
	vert_left = 0;
	vert_right = resolution;
	root = build(source, hori_high, hori_low, vert_left, vert_right);
	}
}
Quadtree::QuadtreeNode* Quadtree::build(PNG const & source, int hori_high, int hori_low, int vert_left, int vert_right)
{
	if (hori_high == hori_low - 1)
	{
		QuadtreeNode* output = new QuadtreeNode();
		output->nwChild = NULL;
        	output->neChild = NULL;
        	output->swChild = NULL;
        	output->seChild = NULL;
		output->element = *source(vert_left, hori_high);
		return output;
	}
	else
	{
		QuadtreeNode* output = new QuadtreeNode();
		int resolution = hori_low - hori_high;
		output->nwChild = build(source, hori_high, hori_high+(resolution/2), vert_left, vert_left+(resolution/2));
		output->neChild = build(source, hori_high, hori_high+(resolution/2), vert_left+(resolution/2), vert_right);
		output->swChild = build(source, hori_high+(resolution/2), hori_low, vert_left, vert_left+(resolution/2));
		output->seChild = build(source, hori_high+(resolution/2), hori_low, vert_left+(resolution/2), vert_right);

		output->element.red = (output->nwChild->element.red + output->neChild->element.red + output->swChild->element.red + output->seChild->element.red)/4;
		output->element.green = (output->nwChild->element.green + output->neChild->element.green + output->swChild->element.green + output->seChild->element.green)/4;
		output->element.blue = (output->nwChild->element.blue + output->neChild->element.blue + output->swChild->element.blue + output->seChild->element.blue)/4;
		output->element.alpha = (output->nwChild->element.alpha + output->neChild->element.alpha + output->swChild->element.alpha + output->seChild->element.alpha)/4;
		return output;
	}
}


Quadtree::Quadtree(Quadtree const & other){
	copy(other);
}

void Quadtree::copy(Quadtree const & other){
    hori_high = other.hori_high;
    hori_low = other.hori_low;
    vert_left = other.vert_left;
    vert_right = other.vert_right;
    root = copy(other.root);
}

Quadtree::QuadtreeNode * Quadtree::copy(QuadtreeNode* const & other){
	if(other == NULL){return NULL;}

	QuadtreeNode* output = new QuadtreeNode();
	output -> nwChild = copy(other -> nwChild);
	output -> neChild = copy(other -> neChild);
	output -> swChild = copy(other -> swChild);
	output -> seChild = copy(other -> seChild);
	output -> element = other -> element;
	return output;
}

Quadtree::~Quadtree(){
	clear();
}

void Quadtree::clear(){
	clear(root);
	root = NULL;
}

void Quadtree::clear(QuadtreeNode* node){
	if(node==NULL){return;}

	clear(node -> nwChild);
	clear(node -> neChild);
	clear(node -> swChild);
	clear(node -> seChild);

	node -> nwChild = NULL;
	node -> neChild = NULL;
	node -> swChild = NULL;
	node -> seChild = NULL;

	delete node;
	node = NULL;
}

Quadtree const & Quadtree::operator=(Quadtree const & other){
	if(this != &other){clear(); copy(other);}
	return *this;
}

RGBAPixel Quadtree::getPixel(int x, int y) const{
	if (x < 0 || x >= vert_right || y < 0 || y >= hori_low || root == NULL){
	RGBAPixel output;
	return output;
	}
	QuadtreeNode* output = getPixel(x, y, 0, vert_right, 0, hori_low, root);
	return output->element;
}

Quadtree::QuadtreeNode* Quadtree::getPixel(int x, int y, int vert_left, int vert_right, int hori_high, int hori_low, QuadtreeNode* output) const{
	if (output->nwChild == NULL){return output;}

	int resolution = hori_low - hori_high;

	if (x < vert_left + (resolution/2) && y < hori_high + (resolution/2)){
	return getPixel(x, y, vert_left, vert_left + (resolution/2), hori_high, hori_high + (resolution/2), output->nwChild);
	}
	if (x >= vert_left + (resolution/2) && y < hori_high + (resolution/2)){
	return getPixel(x, y, vert_left + (resolution/2), vert_right, hori_high, hori_high + (resolution/2), output->neChild);
	}
	if (x < vert_left + (resolution/2) && y >= hori_high + (resolution/2)){
	return getPixel(x, y, vert_left, vert_left + (resolution/2), hori_high + (resolution/2), hori_low, output->swChild);
	}
	if (x >= vert_left + (resolution/2) && y >= hori_high + (resolution/2)){
	return getPixel(x, y, vert_left + (resolution/2), vert_right, hori_high + (resolution/2), hori_low, output->seChild);
	}
	return 0;
}

PNG Quadtree::decompress() const{
if (root == NULL){PNG image; return image;}

PNG::PNG image(vert_right, hori_low);
	for (int x = 0; x<vert_right; x++)
	{
		 for (int y = 0; y<hori_low;y++)
		*image(x,y) = getPixel(x,y);
	}
	return image;
}

void Quadtree::clockwiseRotate(){clockwiseRotate(root);}

void Quadtree::clockwiseRotate(QuadtreeNode* new_root){
    if(new_root == NULL){return;}
    
    QuadtreeNode* temp_ne = new_root->neChild;
    QuadtreeNode* temp_nw = new_root->nwChild;
    QuadtreeNode* temp_se = new_root->seChild;
	QuadtreeNode* temp_sw = new_root->swChild;

    new_root->seChild = temp_ne;
    new_root->neChild = temp_nw;
    new_root->swChild = temp_se;
    new_root->nwChild = temp_sw;
    
    clockwiseRotate(new_root->neChild);
    clockwiseRotate(new_root->nwChild);
    clockwiseRotate(new_root->seChild);
    clockwiseRotate(new_root->swChild);
}



void Quadtree::prune(int tolerance)
{
    prune(root, tolerance);
}

void Quadtree::prune(QuadtreeNode* root, int tolerance)
{
    if (root == NULL){return;}

    if (prune_tree(root, root, tolerance)!=0)
    {
        clear(root->nwChild);
        root->nwChild = NULL;
        clear(root->neChild);
        root->neChild = NULL;
        clear(root->swChild);
        root->swChild = NULL;
        clear(root->seChild);
        root->seChild = NULL;
    }
    else
    {
        prune(root->nwChild, tolerance);
        prune(root->neChild, tolerance);
        prune(root->swChild, tolerance);
        prune(root->seChild, tolerance);
    }
}

bool Quadtree::prune_tree(QuadtreeNode* root, QuadtreeNode* child, int tolerance) const
{
    if (child == NULL){return true;}

    if (child->nwChild == NULL || child->neChild == NULL || child->swChild == NULL || child->seChild == NULL)
    {
    	int diff = difference(root, child);
	if (diff <= tolerance){
	return 1;}
	if (diff > tolerance){
	return 0;}
    }
    return (prune_tree(root, child->nwChild, tolerance) && prune_tree(root, child->neChild, tolerance) && prune_tree(root, child->swChild, tolerance) && prune_tree(root, child->seChild, tolerance));
}

int Quadtree::difference(QuadtreeNode* root, QuadtreeNode* child) const{

        int total_diff = pow(root->element.red - child->element.red, 2) + pow(root->element.green - child->element.green, 2) + pow(root->element.blue - child->element.blue, 2);
	return total_diff;
}
int Quadtree::pruneSize(int tolerance) const{
    return pruneSize(root, tolerance);
}

int Quadtree::pruneSize(QuadtreeNode* root, int tolerance) const{
    if (root == NULL){return 0;}
    if (root->nwChild == NULL || root->neChild == NULL || root->swChild == NULL || root->seChild == NULL){return 1;}
    if (prune_tree(root, root, tolerance)!=0){return 1;}
    return (pruneSize(root->nwChild, tolerance) + pruneSize(root->neChild, tolerance) + pruneSize(root->swChild, tolerance) + pruneSize(root->seChild, tolerance));
}

int Quadtree::idealPrune(int numLeaves) const{
    return idealPrune(numLeaves, 0, 10000000);
}

int Quadtree::idealPrune(int numLeaves, int min_tolerance, int max_tolerance) const{
    if (min_tolerance >= max_tolerance){return min_tolerance;}
    int average_tolerance = (min_tolerance + max_tolerance)/2;
    int tmp = pruneSize(average_tolerance);
    if (tmp <= numLeaves){return idealPrune(numLeaves, min_tolerance, average_tolerance);}
    if (tmp > numLeaves){return idealPrune(numLeaves, average_tolerance + 1, max_tolerance);}
	return 0;
}

