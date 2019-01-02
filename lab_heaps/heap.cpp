/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    /// @todo Update to return the index you are choosing to be your root.
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the left child.
    return 2*(currentIdx+1)-1;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the right child.
    return 2*(currentIdx+1);
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    /// @todo Update to return the index of the parent.
    return (currentIdx+1)/2 -1 ;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    /// @todo Update to return whether the given node has a child
    bool flag = false;
    if(leftChild(currentIdx) < _elems.size())
    flag = true;
  
    return flag;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
         int left = leftChild(currentIdx);
         int right = rightChild(currentIdx);
         if(higherPriority(_elems[left], _elems[right])) 
         return left;
         else 
         return right;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    /// @todo Implement the heapifyDown algorithm.
   if(!hasAChild(currentIdx))
  return;
  {
   int priorityChild = maxPriorityChild(currentIdx);
    if (higherPriority(_elems[priorityChild],_elems[currentIdx])){
    std::swap(_elems[priorityChild],_elems[currentIdx]);
     heapifyDown(priorityChild);
   }
 }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    /// @todo Construct a heap using the buildHeap algorithm
    int size = elems.size();
    for(int i = 0; i<size; i++)
    _elems.push_back(elems[i]);
    for(int i = parent(size); i>=0; i--)
    heapifyDown(i);
   
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    /// @todo Remove, and return, the element with highest priority
    T _popvalue = _elems[0];
    _elems[0] = _elems.back();
    _elems.pop_back();
    heapifyDown(0);
    return _popvalue;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    /// @todo Return, but do not remove, the element with highest priority
    return _elems[0];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    /// @todo Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
    return _elems.empty();
}
