/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
	Node *temp = t->right;
	t->right = temp->left;
	temp->left = t;
	t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
	t = temp;
	temp = NULL;
	t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    Node *temp = t->left;
    t->left = temp->right;
    temp->right = t;
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = temp;
    temp = NULL;
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if((heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right)) < -1){
		if((heightOrNeg1(subtree->right->left) - heightOrNeg1(subtree->right->right))>0){
			rotateRightLeft(subtree);}
		else{
			rotateLeft(subtree);}
	}
    if((heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right)) > 1){
		if((heightOrNeg1(subtree->left->left) - heightOrNeg1(subtree->left->right))>=0){
			rotateRight(subtree);}
		else{
			rotateLeftRight(subtree);}
    }
	subtree->height=max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right))+1;
}


template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree==NULL){subtree=new Node(key,value);}
    
	if(subtree->key > key){insert(subtree->left,key,value);}
    
	if(subtree->key < key){insert(subtree->right, key, value);}	
    
	rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}


template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
         remove(subtree->left,key);
         
    } else if (key > subtree->key) {
        // your code here
         remove(subtree->right,key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
              delete subtree;
              subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* temp1 = subtree->left;
            Node* temp2;
            while(temp1->right !=NULL)
            {
             temp2 = temp1;
             temp1 = temp1->right;
            }
            swap(temp1, subtree);
            remove(temp1, key);
            temp1 = NULL;
            temp2->right = NULL;
            temp2 = NULL;
        } else {
            /* one-child remove */
            // your code here
             Node* temp = subtree;
             if(subtree->left != NULL)
             {
               subtree = subtree->left;
             }
             else
             {
               subtree = subtree->right;
             }
             delete temp;
        }
        // your code here
    }
        if(subtree!=0)
        rebalance(subtree);
}
