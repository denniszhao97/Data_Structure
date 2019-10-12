template <class T>
void List<T>::display()
{
  ListNode* cur = head_;
  while(cur !=NULL)
  {
    cout<<cur->data<<endl;
    cur=cur->next;
  }
}
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  clear();
  /// @todo Graded in MP3.1
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {

    ListNode* cur = head_;
    while (cur != NULL){
      cur= cur -> next;
      delete head_;
      head_ = cur;
    }
    //now head_ == tail_
    delete cur;
    cur = NULL;
    length_ = 0;

}

/**
 * Inserts a new node at the cur of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata) {
    if (this -> empty()){
      tail_ = new ListNode(ndata);
      head_ = tail_;
      length_ ++;
    }else{
      ListNode* newHead = new ListNode(ndata);
      newHead ->next = head_;
      head_ = newHead;
      length_ ++;
    }

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T & ndata) {
    if (this->empty()){
      tail_ = new ListNode(ndata);
      head_ = tail_;
      length_ ++;
    }else{
      ListNode* newTail = new ListNode(ndata);
      tail_ -> next = newTail;
      tail_ = newTail;
      length_ ++;
    }
  /// @todo Graded in MP3.1
}

/**
 * Reverses the current List.
 */
 template <class T>
 void List<T>::reverse()
 {   if (head_ == NULL||tail_ == NULL||head_ == tail_)
 	return;
     reverse(head_, tail_);
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
  template <class T>
  void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {

      if (length_ <= 1) {
         return;
      }

      ListNode * cur = startPoint;
      ListNode * firstStart = startPoint -> prev;
      ListNode * firstEnd = endPoint -> next;
      ListNode * OriginStart = startPoint;
          for(cur = startPoint; cur != endPoint; cur = cur->next){
            cur -> prev = cur -> next;
          }
          endPoint -> prev = firstStart;
          for (cur = OriginStart; cur -> prev != firstStart; cur = cur -> prev){
            cur -> prev -> next = cur ;
          }
          startPoint -> next = firstEnd;
          startPoint = endPoint;
          endPoint = OriginStart;

      if (endPoint -> next != NULL){
        endPoint -> next -> prev = endPoint;
      }else{
         tail_ = endPoint;
      }

      if (startPoint -> prev != NULL){
        startPoint -> prev -> next = startPoint;
      }else{
        head_ = startPoint;
      }
    /// @todo Graded in MP3.1
  }

  /**
   * Reverses blocks of size n in the current List. You should use your
   * reverse( ListNode * &, ListNode * & ) helper function in this method!
   *
   * @param n The size of the blocks in the List to be reversed.
   */
  template <class T>
  void List<T>::reverseNth(int n) {
    if (head_ == NULL)
    	return;
    	ListNode * startPoint;
    	ListNode * endPoint = head_;
    	for(startPoint = head_; endPoint->next != NULL && startPoint->next != NULL;
        startPoint = endPoint->next)
    	{
    		endPoint = startPoint;
        int i = 0;
    		while(i < n-1){
          if(endPoint->next != NULL)
    			endPoint = endPoint->next;
          i++;
        }
    		reverse(startPoint, endPoint);
    }
  }

  /**
   * Modifies the List using the waterfall algorithm.
   * Every other node (starting from the second one) is removed from the
   * List, but appended at theOriginEnd, becoming the new tail. This continues
   * until the next thing to be removed is either the tail (**not necessarily
   * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
   * Note that since the tail should be continuously updated, some nodes will
   * be moved more than once.
   */
  template <class T>
  void List<T>::waterfall() {
    if( empty() || length_ == 2 || length_ == 1){
      return;
    } // Bas Case

    ListNode* cur = head_;
    ListNode* next = cur -> next;
    ListNode* head = head_;

    for( cur = head_; cur != tail_ && next != tail_; head = cur){
      cur = cur -> next;
      next = next -> next;
      head -> next = next;

      tail_ -> next = cur;
      tail_ = cur;
      cur -> next = NULL;

      cur = next;
      next = next->next;
    }
    /// @todo Graded in MP3.1
  }

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  ListNode* cur = start;
  ListNode* secondHead;
  for(int i = 1; i < splitPoint; i++){
    cur = cur->next;
  }
  tail_ = cur;
  secondHead = cur->next;
  cur->next = NULL;
  secondHead->prev = NULL;
  return secondHead;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
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
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {

 if (first == NULL)
     return second;

 if (second == NULL)
     return first;
 ListNode* cur = NULL;

 int a1 = 0;
 int a2 = 0;
 if(first && second){
   if(first->data < second->data){
     cur = first;
     first = first->next;
     a1 = 1;
   } else{
      cur = second;
      second = second->next;
      a2 = 1;
   }
 }
 ListNode* finalHead = cur;

 while(first && second){
   if(first->data < second->data){
     cur->next = first;
     cur = first;
     first = first->next;
   } else {
     cur->next = second;
     cur = second;
     second = second->next;
   }
 }
 if(first == NULL){
   cur->next = second;
 }
 if(second == NULL){
   cur->next = first;
 }

 if(a1 == 1){
   first = finalHead;
   return first;
 }

 if(a2 == 1){
   second = finalHead;
   return second;
 }
 return NULL;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
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
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  chainLength = chainLength/2;
  if (start == NULL|| start->next == NULL){
          return start;
  }
    ListNode* second = split(start, chainLength);
    start = mergesort(start,chainLength);
    second = mergesort(second,chainLength);
    return merge(start,second);
}
