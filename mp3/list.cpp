/* MP3 Young Bin Jo
This mp modifies linked list in various ways. Explanation is included in every section
*/

/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
 #include <iostream>
 using namespace std;
template <class T>
List<T>::~List()
{
    /// @todo Graded in MP3.1
	clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */

template <class T>
void List<T>::clear()
{
	ListNode * delNextNode = head;
	//move delNextNode to delNode->next and free the node until delNextNode reaches NULL
	while(delNextNode != NULL)
	{
		ListNode * delNode = delNextNode;
		delNextNode = delNextNode->next;
		delete delNode;
		delNode = NULL;
	}
	length = 0;
    /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
//This section creates a node and attach it in front of original list head.
template <class T>
void List<T>::insertFront(T const& ndata)
{
	//malloc new node to insert
	ListNode *newNode = new ListNode(ndata);

    /// @todo Graded in MP3.1
	//If head is not null, insert a created newNode in front of head and set newNode as head
	if (head != NULL)
	{
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
	//If the list is empty, just set newNode as head and set newNode->next to null
	else
	{
		head = newNode;
		newNode->next = NULL;
		tail = head;
	}
   	length++;
}
/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
//This section creates a new node and attach at the tail of original list.
template <class T>
void List<T>::insertBack(const T& ndata)
{
    /// @todo Graded in MP3.1
ListNode* newNode = new ListNode(ndata);

	//If list is not empty, set tail's next to newNode 
	if (head != NULL)
	{
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
	else
	{
		head = newNode;
		newNode->next = NULL;
		tail = head;
	}
	length++;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
     reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
//This section reverses the list with given parament (startpoint and endpoint). At the end, I included a section which considers
//the sublist of linked list
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
{
	if (startPoint == endPoint || startPoint == NULL || endPoint == NULL){
    		return;
	}
	ListNode *  temp = NULL;
	ListNode *  location = startPoint;
	ListNode *  endPoint_next = endPoint->next;
	ListNode *  startPoint_prev = startPoint->prev;
	
	//Reverse the list
	while (startPoint != endPoint)
	{
		temp = startPoint->prev;				
		startPoint->prev = startPoint->next;
		startPoint->next = temp;
		startPoint = startPoint->prev;
	}
		//reset the node in correct position
		temp = startPoint->prev;				
		startPoint->prev = startPoint_prev;
		startPoint->next = temp;
		endPoint = location;
		endPoint->next = endPoint_next;
    

	// if in sublist, endPoint->next is null, reset the endpoint 
	if (endPoint_next != NULL)				 
	{
		endPoint_next->prev = endPoint;
	}

	if (startPoint_prev != NULL)
	{
		startPoint_prev->next = startPoint;
	} 
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */

//This part reverses the list by given section. 
template <class T>
void List<T>::reverseNth( int n )
{
	if (head == NULL || n<=0){
		return;
	}
	ListNode * startPoint = head;
	ListNode * endPoint = startPoint;

	int a = 0;
	while (endPoint->next != NULL){
		//For the first sublist, the first parameter for reverse is head not startPoint
		if(a==0){
		for (int i=1; i<n; i++)
		{	
			if (endPoint->next != NULL)
			endPoint = endPoint->next;
		}
			reverse(head,endPoint);
			a++;   
			startPoint = endPoint->next;  				
		}

		//After first sublist, the first parameter for reverse in startPoint			
		else
		{
		endPoint = startPoint;
		for (int i=1; i<n; i++)
		{	
			if (endPoint->next != NULL)
			endPoint = endPoint->next;
		}

		reverse(startPoint,endPoint);  
		startPoint = endPoint->next;
		}
	}
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */

//This section sends the odd node of linked list to the tail. I have isolated the odd node and sent to the tail.
template <class T>
void List<T>::waterfall()
{
    /// @todo Graded in MP3.1
	if (head == NULL || head->next == NULL || head -> next -> next == NULL){
	return;
	}
	
	ListNode* odd = head; 
	ListNode* even = odd->next;
	ListNode* next_odd; 
   

	while (odd->next != NULL && odd->next->next != NULL)
		{
			odd->next->next = even -> next;
			next_odd = even->next;
			odd->next = next_odd;
			next_odd->prev = odd;

			//isolate even node which will move to tail
			even->next = NULL;
			even->prev = NULL;
	
			even->prev = tail;
			tail->next = even;
			tail = even;
			even->next = NULL;

			//reset the odd and even node
			odd = next_odd;
			even = odd->next;
		}
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
	ListNode * head = start;
	
	//Set the new head
	for (int i=0; i < splitPoint; i++)
	{
		if (head->next != NULL)
		head = head->next;
	}
	//Disconnect new list and old list
	ListNode* new_head = head;
	ListNode* old_tail = head->prev;
	old_tail->next = NULL;
	new_head->prev = NULL;
	//Return new list														
    return head; 
}
/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if (tail != NULL) {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
//This section, I used the element data in node struct to compare the value inside the node. Based on the value, I sorted the
//two list and merged it to one.
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
    /// @todo Graded in MP3.2
    
	ListNode* first_next = first;
	ListNode* second_next = second;
	ListNode* merged_list = NULL;
	ListNode* result_next = NULL;

	if (first->data < second->data)
	{
		merged_list = first;
		result_next = merged_list;
		first_next = first->next;
	}
	else
	{
		merged_list = second;
		result_next = merged_list;
		second_next = second->next;
	}

	while (first_next != NULL && second_next != NULL)
	{
		if (first_next->data < second_next->data)
		{
			first_next->prev = result_next;
			result_next->next = first_next;
			first_next = first_next->next;
			result_next = result_next->next;
		}
		else
		{
			second_next->prev = result_next;
			result_next->next = second_next;
			second_next = second_next->next;
			result_next = result_next->next;
		}
	}
	if (first_next == NULL && second_next != NULL)
	{
		second_next->prev = result_next;	
		result_next->next = second_next;
		second_next = second_next->next;
	}
	if (second_next == NULL && first_next != NULL)
	{
		first_next->prev = result_next;
		result_next->next = first_next;
		first_next = first_next->next;
	}

	return merged_list;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
//This section uses recursion to split the list and sort it and merge it until the unsorted list becomes a sorted single list.
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
    /// @todo Graded in MP3.2
	int index = chainLength/2;
	
	//If index is less than 1, return original list since it has less than 2 elements 											
	if (index < 1){
	return start;
	}
	//split the list first and run recursion until it is sorted
	ListNode * right = split(start,index);
	start = mergesort(start,index);
	right = mergesort(right,chainLength-index);
	//after finishing sorting, merge it to one list
    return merge(start,right); 
}

