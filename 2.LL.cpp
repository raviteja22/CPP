01. ReverseDLL
02. rotate
03. isSumSorted
04. addTwoLists
05. mergesort
06. SortList123
07. sortedListToBST
08. sortedDLLToBST
09. delLesserNodes
10. detectAndRemoveLoop
11. removeLoop1
12. flatten
13. swapKth swapKth_and_lastKthnode
14. skipMdeleteN delete_MN_nodes
15. deleteNodeDLL deleteDLL
16. getUnion and getIntersetion.  
17. sortedInsertSLL
18. sortedInsert
19. deleteNodeOnlyGivenPtr
20. merge1 a1a2a3a4b1b2b3b4   a1b1a2b2a3b3a4b4
21. deleteNthnodeFromEnd
22. deleteEverykthnode
23. findDupsCLL
24. mergeAlt 

void reverseDLL(node **headRef)
{
     node *temp = NULL;  
     node *cur = *headRef;

     while(cur)
     {
       temp = cur->prev;
       cur->prev = cur->next;
       cur->next = temp;              
       cur = cur->prev;
     }     
    
     if(temp != NULL )
        *headRef = temp->prev;
}  

10->20->30->40->50->60 and k is 4,
50->60->10->20->30->40

void rotate (node **head, int k)
{
    if (k == 0)
        return;

    node* cur = *head;

    int count = 1;
    while (count < k && cur)
    {
        cur = cur->next;
        count++;
    }

    if (cur == NULL)
        return;

    node *kthNode = cur;

    while (cur->next != NULL)
        cur = cur->next;

    cur->next = *head;
    *head = kthNode->next;
    kthNode->next = NULL;
}

12->6->29, 23->5->8 and 90->20->59  
101, the output should be tripel “ 6 5 90 ".
bool isSumSorted(node *headA, node *headB, node *headC, int no)
{
    node *a = headA;

    while (a != NULL)
    {
        node *b = headB;
        node *c = headC;

        while (b != NULL && c != NULL)
        {
            int sum = a->data + b->data + c->data;
            if (sum == no)
            {
                printf ("Triplet Found: %d %d %d ", a->data, b->data, c->data);
                return true;
            }
            else if (sum < no)
                b = b->next;
            else 
                c = c->next;
        }
        a = a->next;  
    }

    printf ("No such triplet");
    return false;
}

node* addTwoLists (node* first, node* second)
{
    node *res = *temp = *prev = NULL; 
    int carry = 0, sum = 0;

    while (first != NULL || second != NULL)
    {
        sum = carry + (first? first->data: 0) + (second? second->data: 0);

        carry = (sum >= 10)? 1 : 0;

        sum = sum % 10;

        temp = createNew(sum);

        if(res == NULL)
            res = temp;
        else 
            prev->next = temp;

        prev  = temp;

        if (first) first = first->next;
        if (second) second = second->next;
    }

    if (carry > 0)
        temp->next = createNew(carry);

    return res;
}
 
// The main function that adds two LLs represented by head1 and head2.
// The sum of two lists is stored in a list referred by result
void addList(node* head1, node* head2, node** result)
{
    node *cur;
    if (head1 == NULL)
    {
        *result = head2;
        return;
    }
    else if (head2 == NULL)
    {
        *result = head1;
        return;
    }
 
    int size1 = getSize(head1);
    int size2 = getSize(head2) ;
 
    int carry = 0;
 
    if (size1 == size2)
        *result = addSameSize(head1, head2, &carry);
    else
    {
        int diff = abs(size1 - size2);
 
        if (size1 < size2)
            swapPointer(&head1, &head2);
 
        for (cur = head1; diff--; cur = cur->next);
        *result = addSameSize(cur, head2, &carry);
         addCarryToRemaining(head1, cur, &carry, result);
    }
    if (carry)
        push(result, carry);
}
node* addSameSize(node* head1, node* head2, int* carry)
{
    if (head1 == NULL)
        return NULL;

    node* result = new node;
    result->next = addSameSize(head1->next, head2->next, carry);
    int sum = head1->data + head2->data + *carry;
    *carry = sum / 10;
    sum = sum % 10;
    result->data = sum;
 
    return result;
}

void addCarryToRemaining(node* head1, node* cur, int* carry, node** result)
{
    if (head1 != cur)
    {
        addCarryToRemaining(head1->next, cur, carry, result);
 
        int sum = head1->data + *carry;
        *carry = sum/10;
        sum %= 10;
        push(result, sum);
    }
}

void MergeSort(node** headRef)
{
  node* head = *headRef; 
 
  if ((head == NULL) || (head->next == NULL))
      return;

  node *a=NULL, *b=NULL;
  FrontBackSplit(head, &a, &b);
 
  MergeSort(&a);
  MergeSort(&b);
 
  *headRef = SortedMerge(a, b);
}
node* SortedMerge(node* a, node* b)
{
  node* result = NULL;
 
  if (a==NULL) return(b);
  if (b==NULL) return(a);
 
  if (a->data <= b->data)
  {
     result = a;
     result->next = SortedMerge(a->next, b);
  }
  else
  {
     result = b;
     result->next = SortedMerge(a, b->next);
  }
  return(result);
}

void addNode(node **head , int val)
{
	node *temp = new node;
	temp->data = val;
	temp->next = NULL;
	temp->prev = NULL;

	if(*head == NULL)
	{
		*head = temp;
	}
	else
	{
		node *cur = *head;
		while(cur->next)
			cur = cur->next;		
		cur->next = temp;	
		temp->prev = cur;
	}
}

void disp(node *head)
{
	while(head)
	{
		cout<<head->data<<" ";
		head = head->next;	
	}
	cout<<endl;
}
node* end(node *head)
{
	if(head == NULL)
		return NULL;

	while(head->next)
		head = head->next;

	return head;
}
int swap(node *a , node *b)
{
		int c = a->data;
		a->data = b->data;
		b->data = c;
}

void SortList123(node* head)
{
	node* low = head;
	node* mid = head;
	node* high = end(head);
    
	while(mid <= high)
	{
     	switch(mid->data)
		{
			case 1:
				swap(low, mid);
				low = low->next;
				mid = mid->next;
				break;
			case 2:
				mid = mid->next;
				break;
			case 3:
				swap(mid, high);
				high = high->prev;
				break;
		}
	
		printf (" low :: %u  mid :: %u high :: %u \n",low,mid,high);
		
	}
}

void SortList(node* head)
{
	node* low = head;
	node* mid = head;
	node* high = end(head);
    
	while(mid <= high)
	{
    	if(mid->data == 1)
        {
        		swap(low, mid);
				low = low->next;
				mid = mid->next;
		}
        else if(mid->data == 2)
        { 
				mid = mid->next;
         }
         else if(mid->data == 3)
         {		
				swap(mid, high);
				high = high->prev;
		 }
		printf (" low :: %u  mid :: %u high :: %u \n",low,mid,high);
	}
}

void sortList(node *head)
{
    int count[3] = {0, 0, 0};  
    node *ptr = head;
 
    while (ptr != NULL)
    {
        count[ptr->data]++;
        ptr = ptr->next;
    }
 
    int i = 0;
    ptr = head;
 
    while (ptr != NULL)
    {
        if (count[i] == 0)
            ++i;
        else
        {
            ptr->data = i;
            --count[i];
            ptr = ptr->next;
        }
    }
}

node* sortedArrayToBST(int arr[], int n) 
{
    return sortedArrayToBST(arr, 0, n-1);
}
node* sortedArrayToBST(int arr[], int start, int end) 
{
    if (start > end) return NULL;
    // same as (start+end)/2, avoids overflow.
    int mid = start + (end - start) / 2;
	
    node *temp = new node(arr[mid]);
    temp->left = sortedArrayToBST(arr, start, mid-1);
    temp->right = sortedArrayToBST(arr, mid+1, end);
	
    return temp;
}


node* sortedListToBST(node *head)
{
    int n = countnodes(head);
    return LL2BST(&head, n);
}

node* LL2BST(node **head, int n)
{
    if (n <= 0)
        return NULL;

    node *left = LL2BST(head, n/2);

    node *root = createNew((*head)->data);
    root->left = left;
    *head = (*head)->next;
    root->right = LL2BST(head, n-n/2-1);

    return root;
}

 
node* sortedListToBST(ListNode *head, int n) 
{
  return sortedListToBST(head, 0, n-1);
}

node* sortedListToBST(ListNode *& list, int start, int end) 
{
  if (start > end) 
       return NULL;

  int mid = (start + end) / 2;
  node *leftChild = sortedListToBST(list, start, mid-1);
  node *parent = new node(list->data);
  parent->left = leftChild;
  list = list->next;
  parent->right = sortedListToBST(list, mid+1, end);
  return parent;
}


Node* sortedDLLToBST(Node *head)
{
    int n = counnodes(head);
    return sortedDLLToBSTRecur(&head, n);
}

Node* sortedDDLToBSTRecur(Node **head, int n)
{
    if (n <= 0)
        return NULL;

    Node *left = sortedDDLToBSTRecur(head, n/2);

    Node *root = *head;

    root->prev = left;
    *head = (*head)->next;
    root->next = sortedDDLToBSTRecur(head, n-n/2-1);

    return root;
}
Delete nodes which have a greater value on right side
12->15->10->11->5->6->2->3->NULL  15->11->6->3->NULL
10->20->30->40->50->60->NULL 60->NULL
60->50->40->30->20->10->NULL should not be changed.

void delLesserNodes(node **headRef)
{
    reverseList(headRef);
    _delLesserNodes(*headRef);
    reverseList(headRef);
}

void _delLesserNodes(node *head)
{
    node *cur = head;
    node *maxNode = head , *temp = NULL ;

    while (cur && cur->next)
    {
        if(cur->next->data < maxNode->data)
        {
            temp = cur->next;
            cur->next = temp->next;
            delete temp;
        }
        else
        {
            cur = cur->next;
            maxNode = cur;
        }
    }
}


int detectAndRemoveLoop(node *list)
{
    node  *slowPtr = list, *fastPtr = list;

    while (slowPtr && fastPtr && fastPtr->next)
    {
        slowPtr = slowPtr->next;
        fastPtr  = fastPtr->next->next;

        if (slowPtr == fastPtr)
        {
            removeLoop1(slowPtr, list);
            return 1;
        }
    }
    return 0;
}

void removeLoop1(node *loopNode, node *head)
{
    node *ptr1 = head;
    node *ptr2 = loopNode;

    while(1)
    {
        ptr2 = loopNode;
        while(ptr2->next != loopNode && ptr2->next != ptr1)
        {
            ptr2 = ptr2->next;
        }
        if(ptr2->next == ptr1)
            break;
        else
            ptr1 = ptr1->next;
    }
    ptr2->next = NULL;
}

void removeLoop2(node *loopNode, node *head)
{
    node *ptr1 = loopNode;
    node *ptr2 = loopNode;

    unsigned int k = 1, i;
    while (ptr1->next != ptr2)
    {
        ptr1 = ptr1->next;
        k++;
    }

    ptr1 = head;
    ptr2 = head;
    for(i = 0; i < k; i++)
        ptr2 = ptr2->next;

    while(ptr2 != ptr1)
    {
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    ptr2 = ptr2->next;
    while(ptr2->next != ptr1)
        ptr2 = ptr2->next;

    ptr2->next = NULL;
}

Let us create the following LL
       5 -> 10 -> 19 -> 28
       |    |    |     |
       7    20   22    35
       |    |    |
       8    50   40
       |         |   
       30        45
// 5 7 8 10 19 20 20 22 30 35 40 45 50    
Node* flatten (Node* root)
{
     if ( root == NULL || root->right == NULL )
        return root;

    return merge( root, flatten(root->right) );
}

Node* merge( Node* a, Node* b )
{
    if (a == NULL)
        return b;
    if (b == NULL)
        return a;
 
    Node* result;
    if( a->data < b->data )
    {
        result = a;
        result->down = merge( a->down, b );
    }
    else
    {
        result = b;
        result->down = merge( a, b->down );
    }
 
    return result;
}



How to implement LRU caching scheme? What data structures should be used?

1->2->3->4->a->b->c->d->5->6->e->f
1->a->2->b->3->c->4->d->5->e->6->f
http://www.careercup.com/question?id=11395723

l1: a->b->c->d ->null 
l2: 1->2->3->4->null
l3: a->1->b->2->c->3->d->4->null
http://www.careercup.com/question?id=208880

merge LL in sorted order
1->9->3->8->5->7->7
1->3->5->7->7->8->9
?? can it be done inplace ?
http://www.careercup.com/question?id=13275678
Final list should be sorted , so better is to break list into two parts one 
containing all even nodes and one containing all odd nodes.
then, reverse the list containing even nodes.
Then merge the both sorted lists in O(n) inplace.

Given a singly LL which may or may not contain loop and loop may or 
may not start from the head node.Count the number of elements in the LL.
http://www.careercup.com/question?id=13556672

delete every nth node :
Given a doubly linked circular LL and a pointer to any node and a 
number 'n'. Starting from the given node, keep on deleting the "nth" node till 
one node remains. Return a pointer to that node.
http://www.careercup.com/question?id=2321

delete M,N nodes:
given a LL and two integers M and N. Scan the LL such that you 
retain M nodes then delete next N nodes and continue the same till the end of 
LL.
http://www.careercup.com/question?id=13164667

Convert a binary search tree to a circular sorted LL. The highest valued
node should point to the lowest valued node at each step.
http://www.careercup.com/question?id=123685

Write code (in C) to convert a binary search tree into a sorted doubly linked 
list. The algorithm should use recursion and should be done in place.
http://www.careercup.com/question?id=2972	

How to implement LRU caching scheme? What data structures should be used?

We are given total possible page numbers that can be referred. We are also given 
cache (or memory) size (Number of page frames that cache can hold at a time). 
The LRU caching scheme is to remove the least recently used frame when the cache 
is full and a new page is referenced which is not there in cache. Please see 
the Galvin book for more details (see the LRU page replacement slide here).

We use two data structures to implement an LRU Cache.

1. A Queue which is implemented using a doubly LL. The maximum size of t
he queue will be equal to the total number of frames available (cache size).
The most recently used pages will be near front end and least recently pages will
 be near rear end.

2. A Hash with page number as key and address of the corresponding queue node as 
value.

When a page is referenced, the required page may be in the memory. If it is in 
the memory, we need to detach the node of the list and bring it to the front of 
the queue.
If the required page is not in the memory, we bring that in memory. In simple 
words, we add a new node to the front of the queue and update the corresponding 
node address in the hash. If the queue is full, i.e. all the frames are full, we 
remove a node from the rear of queue, and add the new node to the front of queue.

Note: Initially no page is in the memory.


Write a function that will return true if a circular singly LL has 
duplicate values. For example, given a pointer to a node in the circular singly 
LL, *slist, where the only values each node of this list contains int 
value, and *nxt_pointer. How would you traverse it and what way will allow you 
to have the best case for time-complexity? How would we know when the circular 
singly LL stops?
http://www.careercup.com/question?id=15026777

Given an array of pointers to some nodes in a doubly LL, find 
the number of connected node blocks the pointers point to.
http://www.careercup.com/question?id=14945568

You have a LL in which each node is another LL. How do you 
find the 7th most unique element in the among all the nodes in the most optimal
time ?
http://www.careercup.com/question?id=14474161

There is a LL of numbers of length N. N is very large and you don't 
know N. You have to write a function that will return k random numbers from the 
list. Numbers should be completely random.
http://www.careercup.com/question?id=3780057



void skipMdeleteN(node  *head, int M, int N)
{
    node *curr = head, *t;
    int count;

    while (curr)
    {
        for (count = 1; count<M && curr; count++)
            curr = curr->next;
 
        if (curr == NULL)
            return;

		t = curr->next;
        for (count = 1; count<=N && t; count++)
        {
            node *temp = t;
            t = t->next;
            delete temp;
        }
        curr->next = t; 
        curr = t;
    }
}

void swapKth(node **headRef, int k)
{
    int n = countNodes(*headRef);

    if (n < k)  return;

    if (2*k - 1 == n) return;

    node *x = *headRef;
    node *xPrev = NULL;
    for (int i = 1; i < k; i++)
    {
        xPrev = x;
        x = x->next;
    }

    node *y = *headRef;
    node *yPrev = NULL;
    for (int i = 1; i < n-k+1; i++)
    {
        yPrev = y;
        y = y->next;
    }

    if (xPrev)
        xPrev->next = y;

    if (yPrev)
        yPrev->next = x;
 
    node *temp = x->next;
    x->next = y->next;
    y->next = temp;
 
    if (k == 1)
        *headRef = y;
    if (k == n)
        *headRef = x;
}

node *getUnion (node *head1, node *head2)
{
    node *result = NULL;
    node *t1 = head1, *t2 = head2;

    while (t1 != NULL)
    {
        push(&result, t1->data);
        t1 = t1->next;
    }

    while (t2 != NULL)
    {
        if (!isPresent(result, t2->data))
            push(&result, t2->data);
        t2 = t2->next;
    }
 
    return result;
}

node *getIntersection (node *head1, node *head2)
{
    node *result = NULL;
    node *t1 = head1;

    while (t1 != NULL)
    {
        if (isPresent(head2, t1->data))
            push (&result, t1->data);
        t1 = t1->next;
    }
 
    return result;
}

bool isPresent (node *head, int data)
{
    node *t = head;
    while (t != NULL)
    {
        if (t->data == data)
            return 1;
        t = t->next;
    }
    return 0;
}

void deleteNode(node node *nodePtr)   
{
   node node *temp = nodePtr->next;
   nodePtr->data    = temp->data;
   nodePtr->next    = temp->next;
   delete temp;
}


void deleteNodeDLL(node **headRef, node *del)
{
  if(*headRef == NULL || del == NULL)
    return;

  if(*headRef == del)
    *headRef = del->next;
 
  if(del->next != NULL)
    del->next->prev = del->prev;
 
  if(del->prev != NULL)
    del->prev->next = del->next;     

  delete del;
  return;
}

// insert in SLL 
void sortedInsertSLL(node** head, node* newNode)
{
  if (*head == NULL || (*head)->data >= newNode->data)
  {
    newNode->next = *head;
    *head = newNode;
  }
  else
  {
    node *cur = *head;
    while (cur->next!=NULL && cur->next->data < newNode->data)
    {
      cur = cur->next;
    }
    newNode->next = cur->next;
    cur->next = newNode;
  }
}

void sortedInsert(node** headRef, node* newNode)
{
  node* cur = *headRef;

  if (cur == NULL)
  {
     newNode->next = newNode;
     *headRef = newNode;
  }

  else if (cur->data >= newNode->data)
  {
    while(cur->next != *headRef)
        cur = cur->next;
    cur->next = newNode;
    newNode->next = *headRef;
    *headRef = newNode;
  }
  else
  {
    while (cur->next!= *headRef && cur->next->data < newNode->data)
      cur = cur->next;
 
    newNode->next = cur->next;
    cur->next = newNode;
  }
}

else if (cur->data >= newNode->data)
{
  swap(&(cur->data), &(newNode->data));  // swap(int *, int *)
 
  newNode->next = (*headRef)->next;
  (*headRef)->next = newNode;
}

void sortedInsert(node** head_ref, node* new_node)
{
  node* current;
  /* Special case for the head end */
  if (*head_ref == NULL || (*head_ref)->data >= new_node->data)
  {
    new_node->next = *head_ref;
    *head_ref = new_node;
  }
  else
  {
    /* Locate the node before the point of insertion */
    current = *head_ref;
    while (current->next!=NULL && current->next->data < new_node->data)
    {
      current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
  }
}
int getIntesectionNode(node* head1, node* head2)
{
  int c1 = getCount(head1);
  int c2 = getCount(head2);
  int d;
 
  if(c1 > c2)
  {
    d = c1 - c2;
    return _getIntesectionNode(d, head1, head2);
  }
  else
  {
    d = c2 - c1;
    return _getIntesectionNode(d, head2, head1);
  }
}

int _getIntesectionNode(int d, node* head1, node* head2)
{
  int i;
  node* current1 = head1;
  node* current2 = head2;
 
  for(i = 0; i < d; i++)
  {
    if(current1 == NULL)
    {  return -1; }
    current1 = current1->next;
  }
 
  while(current1 !=  NULL && current2 != NULL)
  {
    if(current1 == current2)
      return current1->data;
    current1= current1->next;
    current2= current2->next;
  }
 
  return -1;
}

int getCount(node* head)
{
  node* current = head;
  int count = 0;
 
  while (current != NULL)
  {
    count++;
    current = current->next;
  }
 
  return count;
}

27. Merge a linked list into another linked list at alternate positions
5->7->17->13->11  12->10->2->4->6,
5->12->7->10->17->2->13->4->11->6

1->2->3  4->5->6->7->8
1->4->2->5->3->6 and second list to 7->8


void mergeAlt(node *p, node **q)
{
     node *pCurr = p, *qCurr = *q;
     node *pNext, *qNext;
 
     // While therre are avialable positions in p
     while (pCurr != NULL && qCurr != NULL)
     {
         // Save next pointers
         pNext = pCurr->next;
         qNext = qCurr->next;
 
         // Make qCurr as next of pCurr
         qCurr->next = pNext;  // Change next pointer of qCurr
         pCurr->next = qCurr;  // Change next pointer of pCurr
 
         // Update current pointers for next iteration
         pCurr = pNext;
         qCurr = qNext;
    }
 
    *q = qCurr; // Update head pointer of second list
}






