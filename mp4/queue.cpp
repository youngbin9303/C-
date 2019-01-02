/**
 * @file queue.cpp
 * Implementation of the Queue class.
 *
 * @author CS 225 course staff
 * @date Fall 2009
 */

/**
 * Adds the parameter object to the back of the Queue.
 *
 * @param newItem object to be added to the Queue.
 */
//push the element in inStack since inStack is pointing the tail where elements enter
template <class T>
void Queue<T>::enqueue(T const& newItem)
{
    inStack.push(newItem);
    /**
     * @todo Your code here!
     */
}

/**
 * Removes the object at the front of the Queue, and returns it to the
 * caller.
 *
 * @return The item that used to be at the front of the Queue.
 */
//Since we need to remove the object in front, pop the stack in tail and push it to front until inStack pointer is empty.
//After this process, outStack will point the head which we need to pop.
template <class T>
T Queue<T>::dequeue()
{
     if(outStack.isEmpty())
     {
       while(!inStack.isEmpty())
      {
       outStack.push(inStack.pop());
      }
     
     }
     return outStack.pop();
     /**
     * @todo Your code here! You will need to replace the following line.
     */
   
}

/**
 * Adds an element to the ordering structure.
 *
 * @see OrderingStructure::add()
 */
//Call the enqueue function
template <class T>
void Queue<T>::add(const T& theItem)
{
      enqueue(theItem);
    /**
     * @todo Your code here! Hint: this function should call a Queue
     *  function to add the element to the Queue.
     */
}

/**
 * Removes an element from the ordering structure.
 *
 * @see OrderingStructure::remove()
 */
//
//Call the dequeue function
template <class T>
T Queue<T>::remove()
{
    /**
     * @todo Your code here! Hint: this function should call a Queue
     *  function to remove an element from the Queue and return it. You will
     *  need to replace the following line.
     */
    return dequeue();
}

/**
 * Finds the object at the front of the Queue, and returns it to the
 * caller. Unlike pop(), this operation does not alter the queue.
 *
 * @return The item at the front of the queue.
 */
//This is same procedure as dequeue. However, we return the peek which is the top of the stack
template <class T>
T Queue<T>::peek()
{
    if(outStack.isEmpty())
     {
       while(!inStack.isEmpty())
      {
       outStack.push(inStack.pop());
      }
     
     }
return outStack.peek();


    /**
     * @todo Your code here! You will need to replace the following line.
     */
 
}

/**
 * Determines if the Queue is empty.
 *
 * @return bool which is true if the Queue is empty, false otherwise.
 */
//It calls the isEmpty function in stack.cpp. We need to check both inStack and outStack.
template <class T>
bool Queue<T>::isEmpty() const
{
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    return (inStack.isEmpty()&&outStack.isEmpty());
}
