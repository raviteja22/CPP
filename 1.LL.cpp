01.	middleOfList // 30 + 24 + 6 = 60 
02.	nthNode
03.	findCircular (detectLoop) // find length , find start node
04.	freeLinkedList
05.	palindrome
06.	selectionSort
07.	bubbleSort
08.	swapAdjList
09.	rev
10.	KRev
11.	KRevAlt
12.	revRec
13.	segregate
14.	intersectionPoint
15.	compare2Lists
16.	split2
17.	split2CLL
18.	merge2Lists 
19.	removeDupSort
20.	removeDupUnSort
21.	RemoveDuplicates
22.	merge
23.	lastNodeHead
24.	splitAlternate
25.	revCircularLL
26.	revPrint
27.	deleteEvenNodes
28.	deleteNoOddNodes
29.	setNextLarge
30.	clone

int middleOfList(node *head) // 1 2 3 4 5  -- > 3
{
	if(head == NULL || head->next == NULL)
		return -1;

	node *ptr1 = head;
	node *ptr2 = head->next;

	while( ptr2 && ptr2->next)
	{
		ptr1 = ptr1->next;
		ptr2 = ptr2->next->next;
	}
	return ptr1->data;
}

void printMiddle(node *head)
{
    int count = 0;
    node *mid = head;
 
    while (head != NULL)
    {
        if (count & 1)
            mid = mid->next;
 
        ++count;
        head = head->next;
    }

    if (mid != NULL)
        printf("\tThe middle element is %d\n\n", mid->data);
}
// 3 .use count

// 1. Use two pointers
int nthNode(node *head , int val) // 1 2 3 4 5 6  , val = 2  --- > 5 
{
	if(head == NULL || head->next == NULL)
		return -1;

	node *ptr1 = head , * ptr2 = head;
	int count = 0;
	while(count < val)
	{
		if(ptr1 == NULL)
			return 0;
		ptr1 = ptr1->next;
		count++;	
	}
	
	while(ptr1)
	{
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
	}
	
	return ptr2->data;
}

2. Use length of LL
1) Calculate the length of LL. Let the length be len.
2) Print the (len – n + 1)th node from the begining of the LL.

3. Use Recursion

void printNthFromLast(node* head, int n)
{
    int len = 0, i;
    node *temp = head;

    while (temp != NULL)
    {
        temp = temp->next;
        len++;
    }
    if (len < n)
      return;
 
    temp = head;

    for (i = 1; i < len-n+1; i++)
       temp = temp->next; 
    printf ("%d", temp->data);
}

void printNthFromLast(node* head, int n) // O(n)
{
    static int i = 0;
    if(head == NULL)
       return;
    printNthFromLast(head->next, n);
    if(++i == n)
       printf("%d", head->data);
}
// 3. Implementation of Floyd’s Cycle-Finding Algorithm
int findCircular(node *head) // 1 2 3 4 5
{
	if(head == NULL || head->next == NULL)
		return -1;

	node *ptr1 = head;
	node *ptr2 = head->next;

	while( ptr2 && ptr2->next)
	{
		if(ptr1 == ptr2)
			return 1;

		ptr1 = ptr1->next;
		ptr2 = ptr2->next->next;
	}
	return -1;
}

// 1. Use Hashing 
Traverse the list one by one and keep putting the node addresses in a Hash Table. 
At any point, if NULL is reached then return false and if next of cur node 
points to any of the previously stored nodes in Hash then return true.

// 2. Mark Visited Nodes
This solution requires modifications to basic LL data structure.  Have a 
visited flag with each node.  Traverse the LL and keep marking visited 
nodes.  If you see a visited node again then there is a loop. This solution works 
in O(n) but requires additional information with each node.


void freeLinkedList(node **head)
{
	node *cur = *head;
	while(cur)
	{
		*head = cur->next;
		delete cur;
		cur = NULL;
		cur = *head;	
	}	
}

bool palindrome(node *head) // 1 2 3 2 1  ( true ) 
{			          // 1 2 3 2 3  ( false )	 
	static node *temp = head;	
	static bool flag = true;

	if(head)
	{
		palindrome(head->next);

		if( flag && head->data != temp->data)
		{
			flag = false;
		}
		temp = temp->next;

	}	
	return flag;
}
// Use a Stack
A simple solution is to use a stack of list nodes. This mainly involves three steps
1) Traverse the given list from head to tail and push every visited node to stack.
2) Traverse the list again. For every visited node, pop a node from stack and 
   compare data of popped node with curly visited node.
3) If all nodes matched, then return true, else false.

Time complexity of above method is O(n), but it requires O(n) extra space. Following methods solve this with constant extra space.

// By reversing the list
1.  Get the middle of the LL.
2.  Reverse the second half of the LL.
3.  Compare the first half and second half.
4.  Construct the original LL by reversing the 
    second half again and attaching it back to the first half
	
// Using Recursion
bool isPalindrome(node **left, struct  node *right)
{
   if (!right)
      return true;

   bool isp = isPalindrome(left, right->next);
   if (isp == false)
      return false;

   bool isp1 = (right->data == (*left)->data);

   *left = (*left)->next; 
 
   return isp1;
}	

bool isPalindrome(node *head)
{
    node *slowPtr = head, *fastPtr = head;
    node *second_half, *prev_of_slowPtr = head;
    node *midnode = NULL;  // To handle odd size list
    bool res = true; // initialize result
 
    if (head!=NULL)
    {
        /* Get the middle of the list. Move slowPtr by 1
          and fastPtrr by 2, slowPtr will have the middle
          node */
        while (fastPtr != NULL && fastPtr->next != NULL)
        {
            fastPtr = fastPtr->next->next;
 
            /*We need previous of the slowPtr for
             linked lists  with odd elements */
            prev_of_slowPtr = slowPtr;
            slowPtr = slowPtr->next;
        }
 
 
        /* fastPtr would become NULL when there are even elements in list. 
           And not NULL for odd elements. We need to skip the middle node 
           for odd case and store it somewhere so that we can restore the
           original list*/
        if (fastPtr != NULL)
        {
            midnode = slowPtr;
            slowPtr = slowPtr->next;
        }
 
        // Now reverse the second half and compare it with first half
        second_half = slowPtr;
        prev_of_slowPtr->next = NULL; // NULL terminate first half
        reverse(&second_half);  // Reverse the second half
        res = compareLists(head, second_half); // compare
 
        /* Construct the original list back */
         reverse(&second_half); // Reverse the second half again
         if (midnode != NULL)  // If there was a mid node (odd size case) which                                                         
                               // was not part of either first half or second half.
         {
            prev_of_slowPtr->next = midnode;
            midnode->next = second_half;
         }
         else  prev_of_slowPtr->next = second_half;
    }
    return res;
}

void reverse(node** head_ref)
{
    node* prev   = NULL;
    node* current = *head_ref;
    node* next;
    while (current != NULL)
    {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev;
}

bool compareLists(node* head1, node *head2)
{
    node* temp1 = head1;
    node* temp2 = head2;
 
    while (temp1 && temp2)
    {
        if (temp1->data == temp2->data)
        {
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else return 0;
    }
 
    /* Both are empty reurn 1*/
    if (temp1 == NULL && temp2 == NULL)
        return 1;
 
    /* Will reach here when one is NULL
      and other is not */
    return 0;
}
  
void selectionSort(node *head) // 3 2 6 1 ---- > 1 2 3 6
{
    if(head == NULL)
        return ;

    node *outer = head;

    while(outer)
    {
        node *inner = outer->next;

            while(inner)
            {
                if(outer->data > inner->data)
                {
                    int temp = outer->data;
                    outer->data = inner->data;
                    inner->data = temp;
                }
               inner = inner->next; 
            }
            outer = outer->next;
    }
}

void BubbleSort(node * head) // 3 2 6 1 ---- > 1 2 3 6
{
	if (head == NULL)
		return;
	 
	node *end = NULL;
	while (end != head->next)
	{
		node *p = head;
		node *q = head->next;

		while (q != end)
		{
			if (p->data > q->data)
			{
				int tmpData = p->data;
				p->data = q->data;
				q->data = tmpData;
			}
			p = p->next;
			q = q->next;
		}
		end = p;
	}
}

node* swapAdjList(node *head) // 1 2 3 4   ---- > 2 1 4 3
{
	node *first = head;
	if(first && first->next)
	{
		node *second = first->next;
		first->next = swapAdjList(second->next);
		second->next = first;
		first = second;		
	}
	return first;	
}

void rev(node **head) // 1 2 3 4   ----- > 4 3 2 1
{
    node *cur = *head;
    node *prev = NULL;
    node *next = NULL;

    while( cur )
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    *head = prev;
}

node * KRev(node *head , int k) // 1 2 3 4 5 6 7 8 9 , k=3   ----- >  3 2 1 6 5 4 9 8 7
{
    node *cur = head;
    node *prev = NULL;
    node *next = NULL;
    int count = 0;

    while( cur && count < k )
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
        count++;
    }
    if(next)
        head->next = KRev(next,k);

    return prev;
}

node * KRevAlt(node *head , int k) // 1 2 3 4 5 6 7 8 9 , k=3   ----- >  3 2 1 4 5 6 9 8 7
{
    node *cur = head;
    node *prev = NULL;
    node *next = NULL;
    int count = 0;

    while( cur && count < k )
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
        count++;
    }

    if(head)
        head->next = cur;

    count = 0;

    while ( cur && count < k-1 )
    {
        cur = cur->next;
        count++;
    }

    if(cur)
    {
        cur->next = KRevAlt (cur->next , k);
    }
    
    return prev;
}


node *revRec(node *head) // 1 2 3 4 5 -- > 5 4 3 2 1
{   
    static node *retVal = NULL;
    if(head == NULL || head->next == NULL)   
        return head;

    retVal = revRec(head->next);
    head->next->next = head;
    head->next = NULL;
    
	return retVal;
}
void recursiveReverse(node** head)
{  
    if (*head == NULL)
       return; 
	   
    static node *rest = NULL ; 
    node *first = NULL;
	first = *head;  
    rest  = first->next;

    if (rest == NULL)
       return;   

    recursiveReverse(&rest);
    first->next->next  = first;  
    first->next  = NULL; 
	
    *head = rest;              
}


void segregate(node **head) // 1 2 3 4 5 6 ---- > 2 4 6 1 3 5
{
	node *cur = *head;
	node *eStart = NULL , *eEnd = NULL;
	node *oStart = NULL , *oEnd = NULL;

	while(cur)
	{
		if(cur->data %2 == 0)
		{
			if(eStart == NULL)
			{
				eStart = eEnd = cur;
			}	
			else 
			{
				eEnd->next = cur;
				eEnd = cur;
			}
		}
		else
		{
			if(oStart == NULL)
			{
				oStart = oEnd = cur;
			}	
			else
			{
				oEnd->next = cur;
				oEnd = cur;
			}
		}			
			cur = cur->next;
	}
	if(oEnd )  oEnd->next = NULL;
	if(eEnd)  eEnd->next = NULL;

	if(eStart)
	{
		eEnd->next = oStart;	
		*head = eStart;
	}
	else 
	{
		*head = oStart; 
	} 
}
void segregateEvenOdd(node **head_ref)
{
  node *end = *head_ref;
  
  node *prev = NULL;
  node *curr = *head_ref;
  
  while(end->next != NULL)
       end = end->next; 
  
  node *new_end = end;

  while(curr->data %2 != 0 && curr != end)
  {
    new_end->next = curr;
    curr = curr->next;
    new_end->next->next = NULL;
    new_end = new_end->next;
  }   
  
  // 10->8->17->17->15
  if (curr->data%2 == 0)
  {
    *head_ref = curr;     
  
    while(curr != end)
    {
      if ( (curr->data)%2 == 0 )
      {
         prev = curr;
         curr = curr->next;
      }
      else
      {
         prev->next = curr->next;

         curr->next = NULL;

         new_end->next = curr;

         new_end = curr;

         curr = prev->next;
      }
    }
  }
  else  
    prev = curr;
  if((end->data)%2 != 0)
  {
      prev->next = end->next;
      end->next = NULL;
      new_end->next = end;
  }
  return;
}

 
node* intersectionPoint(node *list1, node *list2)
{
	if( list1 == NULL || list2 == NULL)
		return NULL;

	int c1 = lenRec(list1);
	int c2 = lenRec(list2);

	int diff = abs(c1 - c2);
	if( c1 > c2)
	{
		while(diff--)
			list1 = list1->next;
	}
	else
	{
		while(diff--)
			list2 = list2->next;
	}
	while( list1 != list2)
	{
		list1 = list1->next;
		list2 = list2->next;
	}

	if(list1 != NULL)
	{
		return list1;
	}	
	else
	{
		cout<<"not interseting"<<endl;
		return NULL;
	}
}

// Method 1(Simply use two loops)

// Method 2 (Mark Visited Nodes)
This solution requires modifications to basic LL data structure. Have a visited 
flag with each node. Traverse the first LL and keep marking visited nodes. Now 
traverse second LL, If you see a visited node again then there is an intersection 
point, return the intersecting node. This solution works in O(m+n) but requires 
additional information with each node. 

// Method 3 (Hashing )
A variation of this solution that doesn’t require modification to basic DS can be 
implemented using hash.Traverse the first LL and store the addresses of visited 
nodes in a hash. Now traverse the second LL and if you see an address that already 
exists in hash then return the intersecting node.

// Method 4(Using difference of node counts)
1) Get count of the nodes in first list, let count be c1.
2) Get count of the nodes in second list, let count be c2.
3) Get the difference of counts d = abs(c1 – c2)
4) Now traverse the bigger list from the first node till d nodes so that from here onwards 
both the lists have equal no of nodes.
5) Then we can traverse both the lists in parallel till we come across a common node. 
(Note that getting a common node is done by comparing the address of the nodes)structure 
an be implemented using hash

// Method 5(Make circle in first list)

Thanks to Saravanan Man for providing below solution.
1. Traverse the first LL(count the elements) and make a circular LL. (Remember last node so that we can break the circle later on).
2. Now view the problem as find the loop in the second LL. So the problem is solved.
3. Since we already know the length of the loop(size of first LL) we can traverse those many number of nodes in second list, and then start another pointer from the beginning of second list. we have to traverse until they are equal, and that is the required intersection point.
4. remove the circle from the LL.

Time Complexity: O(m+n)
Auxiliary Space: O(1)

Method 6 (Traverse both lists and compare addresses of last nodes) This method is only to detect if there is an intersection point or not. (Thanks to NeoTheSaviour for suggesting this)

1) Traverse the list 1, store the last node address
2) Traverse the list 2, store the last node address.
3) If nodes stored in 1 and 2 are same then they are intersecting.
Time complexity of this method is O(m+n) and used Auxiliary space is O(1)

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
  node* current1 = head1;
  node* current2 = head2;
 
  for(int i = 0; i < d; i++)
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

bool compare2Lists(node *list1 , node *list2)
{
	if(list1 == NULL && list2 == NULL)
	{
		return 1;
	}
	else if( list1 != NULL && list2 != NULL)
	{
		return (list1->data != list2->data) &&
				compare2Lists(list1->next,list2->next);
	}	
	else 
	{
	    return 0;
	}	
}
bool compareLists(node* head1, node *head2)
{
    node* temp1 = head1;
    node* temp2 = head2;
 
    while (temp1 && temp2)
    {
        if (temp1->data == temp2->data)
        {
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else 
			return 0;
    }

    if (temp1 == NULL && temp2 == NULL)
        return 1;

    return 0;
}

void split2(node *head , node **a , node **b)
{
	node *f = head;
	node *s = f->next;

	while( s && s->next )
	{
		f = f->next;
		s = s->next->next;	
	}
	*a = head;
	*b = f->next;
	f->next = NULL;

}

void split2CLL(node *head,node **head1,node **head2)
{
  node *slowPtr = head;
  node *fastPtr = head; 
 
  if(head == NULL)
    return;
  
  /* If there are odd nodes in the circular list then
     fastPtr->next becomes head and for even nodes 
     fastPtr->next->next becomes head */
  while(fastPtr->next != head &&
         fastPtr->next->next != head) 
  {
     fastPtr = fastPtr->next->next;
     slowPtr = slowPtr->next;
  }  
 
 /* If there are even elements in list then move fastPtr */
  if(fastPtr->next->next == head)
    fastPtr = fastPtr->next;      
   
  /* Set the head pointer of first half */
  *head1 = head;    
      
  /* Set the head pointer of second half */
  if(head->next != head)
    *head2 = slowPtr->next;
   
  /* Make second half circular */  
  fastPtr->next = slowPtr->next;
   
  /* Make first half circular */  
  slowPtr->next = head;       
}

void merge2Lists(node **a, node **b)
{
	if(*a == NULL && *b == NULL)
		return ;
	
	if(*a == NULL)
	{
		*a = *b;
		return ;
	}
	if(*b == NULL)
		return ;
	node *cur = *a;

	while(cur->next)
		cur = cur->next;
	cur->next = *b;
	return ;
}

//1 1 2 3 3 4  --> 1 2 3 4
void removeDupSort(node *head)
{
	node *f = head;
	node *temp = NULL;

	while(f && f->next)
	{
		if(f->data == f->next->data)
		{
			temp = f->next;	
			f->next = temp->next;
			delete temp;
		}
		else
		{
			f = f->next;	
		}
	}
}

//2 1 4 2 1 5 --> 1 2 4 5
void removeDupUnSort(node *head)
{
	node *f = head;
	node *s = NULL;
	node *pre = NULL;	

	while(f)
	{
		pre = f;
		s = f->next;
		while(s)
		{
			if( f->data == s->data)
			{
				pre->next = s->next;				
				delete s;
				s = pre->next;
			}
			else
			{
				pre = s;
				s = s->next;		
			}
		}
		f = f->next;
	}	
}
void removeDuplicates(node *start)
{
  node *ptr1, *ptr2, *dup;
  ptr1 = start;
 
  while(ptr1 != NULL && ptr1->next != NULL)
  {
     ptr2 = ptr1;

     while(ptr2->next != NULL)
     {
       if(ptr1->data == ptr2->next->data)
       {
          dup = ptr2->next;
          ptr2->next = ptr2->next->next;
          delete dup;
       }
       else 
       {
          ptr2 = ptr2->next;
       }
     }
     ptr1 = ptr1->next;
  }
}
METHOD 3 (Use Hashing)
We traverse the link list from head to end. For every newly encountered element, 
we check whether it is in the hash table: if yes, we remove it; otherwise we put it in the 
hash table.

Time Complexity: O(n) on average (assuming that hash table access time is O(1) on average).
 
//1 1 2 3 4  --> 2 3 4
bool RemoveDuplicates( node** head )
{
	if(*head == NULL )
	{
		return false;
	}

	node* cur = *head;
	node *old = *head;

	while(cur)
	{
		if(cur->next && cur->data == cur->next->data)
		{
			int curData = cur->data;

			while(cur!= NULL && cur->data == curData)
			{
				node* temp = cur->next;
				if(cur == *head)
				{
					*head = old = temp;	
				}
				else
				{
					old->next = temp;
				}
				delete cur;
				cur = temp;		
			}
		}
		else
		{
			old = cur;
			cur = cur->next;
		}
	}
	return true;
}
1 2 3 4 5 --> 5 1 2 3 4
void lastNodeHead(node **head)
{
	node *cur = *head;
	node *pre = *head;

	while(cur->next)
	{
		pre = cur;
		cur = cur->next;
	}

	pre->next = NULL;
	cur->next = *head;
	*head = cur;
}

5->10->15  2->3->20 
2->3->5->10->15->20

node* merge(node *p , node *q)
{
	if(p == NULL) return q;
	if(q == NULL) return p;

	if(p->data == q->data)
	{
		p->next = merge(p->next , q->next);
		delete q;
		return p;
	}
	else if(p->data > q->data)
	{
		q->next = merge(p,q->next);
		return q;
	}
	else
	{
		p->next = merge(p->next,q);
		return p;
	}
}
/*  Method 1 (Using Dummy Nodes)
The strategy here uses a temporary dummy node as the start of the result list. The pointer Tail 
always points to the last node in the result list, so appending new nodes is easy.
The dummy node gives tail something to point to initially when the result list is empty. This 
dummy node is efficient, since it is only temporary, and it is allocated in the stack. The 
loop proceeds, removing one node from either ‘a’ or ‘b’, and adding it to tail. When
we are done, the result is in dummy.next.

2 (Using Local References)
This solution is structurally very similar to the above, but it avoids using a dummy node. 
Instead, it maintains a node** pointer, lastPtrRef, that always points to the last 
pointer of the result list. This solves the same case that the dummy node did — dealing with 
the result list when it is empty. If you are trying to build up a list at its tail, either the 
dummy node or the node** “reference” strategy can be used */

node* SortedMerge(node* a, node* b) 
{
   node dummy;      

   node* tail = &dummy;  
 
   dummy.next = NULL;
   while(1) 
   {
      if(a == NULL) 
      { 
         tail->next = b;
         break;
      }
      else if (b == NULL) 
      {
         tail->next = a;
         break;
      }
      if (a->data <= b->data) 
      {
         MoveNode(&(tail->next), &a);
      }
      else
     {
        MoveNode(&(tail->next), &b);
     }
     tail = tail->next;
  }
  return(dummy.next);
}  

void MoveNode(node** destRef, node** sourceRef)
{
  node* newNode = *sourceRef;
  assert(newNode != NULL);

  *sourceRef = newNode->next;

  newNode->next = *destRef; 

  *destRef = newNode;
}
node* SortedMerge(node* a, node* b) 
{
  node* result = NULL;

  node** lastPtrRef = &result; 
   
  while(1) 
  {
    if (a == NULL) 
    {
      *lastPtrRef = b;
       break;
    }
    else if (b==NULL) 
    {
       *lastPtrRef = a;
       break;
    }
    if(a->data <= b->data) 
    {
      MoveNode(lastPtrRef, &a);
    }
    else
    {
      MoveNode(lastPtrRef, &b);
    }

    lastPtrRef = &((*lastPtrRef)->next); 
  }
  return(result);
} 
// 1 2 3  4 5 6 --> 1 4 2 5 3 6
node *merge1(node *p , node *q , bool flag)
  {
      if(p==NULL) return q;
      if(q==NULL) return p;
      
      node *result;
      if(flag)
      {
            result = p ;
            result->next = merge1(p->next,q,0);
      }   
      else
      {
            result = q;
            result->next = merge1(p,q->next,1);    
      }
      return result;
      
  }        



Method 3 (Using Recursion)
http://www.geeksforgeeks.org/merge-two-sorted-linked-lists/

void minMaxAvg(node *head)
{
	int min = head->data , max = min;
	int avg = 0,sum = 0,count = 0;

	head = head->next;
	while(head)
	{
		if(head->data < min)	
			min = head->data;			

		if(head->data > max)
			max = head->data;	

		sum += head->data;
		count++;
		head = head->next;
	}
	avg = sum/count; 
}

void splitAlternate(node *head , node **list1 , node **list2)
{
	*list1 = head;
	*list2 = head->next;

	node *cur = head->next->next;
	node *f = *list1;
	node *s = *list2;

	while(cur && cur->next)
	{
		f = f->next = cur;
		s = s->next = cur->next;
		cur = cur->next->next;	
	}

	if(cur) // odd
	{
		f = f->next = cur;
		s->next = NULL;
	}
	else // even
	{
		f->next = NULL;
	}
}

void revCircularLL(node **head)
{
    if(*head == NULL)
        return ;

    node *curr = *head;
    node *next = NULL;
    node *prev = NULL;

    while( curr && curr->next != *head)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    curr->next = prev;
    (*head)->next = curr;
    *head = curr;
}
 
int lenRec(node *head)
{
	if(head == NULL)
		return 0;
	else
		return ( 1 + lenRec(head->next) );
}
void revPrint(node *head)
{
	if(head)
	{
		revPrint(head->next);
		cout<<head->data<<" ";
	}
}

void deleteEvenNodes(node **head)
{
	node *cur = *head ,  *nxt = NULL;

	while(cur && cur->next)
	{
		nxt = cur->next;
		cur->next = nxt->next;	
		delete nxt;
		cur = cur->next;
	}
}

void deleteOddNodes(node **head)
{
	node *cur = *head;
   	*head = (*head)->next;
	delete cur;
	cur = *head;

   	 node *old = NULL;

	while(cur && cur->next)
	{
		old = cur->next;
		cur->next = old->next;	
		delete old;
		cur = cur->next;
	}

}
 
void deleteNoOddNodes(node **head)
{
	if(*head == NULL)
		return ;

	node *cur = *head;
	node *old = NULL;

	while(cur)
	{
		// if(cur->data %2 == 0) // for number odd nodes
		if(cur->data %2 != 0)
		{
			if(cur == *head)
			{
				*head = cur->next;
				delete cur;
				cur = *head;
			}
			else
			{
				old->next = cur->next;
				delete cur;
				cur = old->next;
			}		
		}
		else
		{
			old = cur;
			cur = cur->next;	
		}
	}
}
   

void countArray(node *head , node **arr)
{
	cout<<"countArray"<<endl;
	while(head)
	{
		arr[head->data] = head;
		head = head->next;
	}	
}
node* setNextLarge(node **arr , int val)
{
	cout<<"setNextLarge"<<endl;
	int i = val + 1;
	for(; i < 10 ; i++)
	{
		if(arr[i] != NULL)
			return arr[i];		
	}
	return NULL;
}

void printNextLarge(node *head)
{
	while(head)
	{
		cout<<head->data<<"  ";
		if(head->large)
			cout<<head->large->data<<endl;
		head = head->next;
	}	
	cout<<endl;
}

Clone list
node* createNode(int val)
{
	node *temp = new node;
	temp->data = val;
	temp->next = NULL;
	temp->random = NULL;

	return temp;
}

void disp1(node *head)
{
	while(head)
	{
		printf("head   - %u , data - %d\n",head,head->data);
		printf("random - %u , data - %d\n",head->random,head->random->data);
		//cout<<head->data<<"  "<<head->random->data<<endl;
		head = head->next;
	}		
}

void setRandom(node *head)	
{
	cout<<"setRandom"<<endl;
	head->random = 	head->next->next;
	head->next->random = head;
	head->next->next->random = head->next; 	
}
// by usning hash

void clone(node *head)
{
	cout<<"cloning"<<endl;
	node *cur = head;

	while(head)
	{
		node *temp = createNode(head->data);
		temp->next = head->next;
		head->next = temp;

		head = head->next->next;	
	}
	head = cur;

	node *a = cur;
	node *b = cur->next;

	while(b && b->next)
	{
		b->random = a->random->next;
		b = b->next->next;
		a = a->next->next;		
	}
	if(b->next == NULL)
		b->random = a->random->next;

	splitAlternate(cur,&a,&b);

	//disp(a);
	//disp(b);
	disp1(a);
	disp1(b);
}
