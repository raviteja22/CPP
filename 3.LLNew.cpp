[Q01]. flatten
[Q02]. flattenList
[Q03]. quickSort 
[Q04]. quickSort1
[Q05]. quickSort2
[Q06]. findMiddle
[Q07]. LRU
[Q08]. mergeAlt 


Flattening a Linked List

Given a linked list where every node represents a linked list and contains 
two pointers of its type:
(i) Pointer to next node in the main list 
(we call it ‘right’ pointer in below code)
(ii) Pointer to a linked list where this node is head 
(we call it ‘down’ pointer in below code).
All linked lists are sorted. See the following example

       5 -> 10 -> 19 -> 28
       |    |     |     |
       V    V     V     V
       7    20    22    35
       |          |     |
       V          V     V
       8          50    40
       |                |
       V                V
       30               45
Write a function flatten() to flatten the lists into a single linked list. 
The flattened linked list should also be sorted. For example, for 
the above input list, output list should be 
5->7->8->10->19->20->22->28->30->35->40->45->50.

typedef struct node
{
    int data;
    struct node *right;
    struct node *down;
} node;

node* flatten (node* root)
{
    if ( root == NULL || root->right == NULL )
        return root;
 
    return merge( root, flatten(root->right) );
}
node* merge( node* a, node* b )
{
    if (a == NULL) return b;
    if (b == NULL) return a;

    node* result;
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

struct list
{
    int data;
    struct list *next;
    struct list *child;
};
The above 10->5->12->7->11->4->20->13->17->6->2->16->9->8->3->19->15
struct node *createList(int *arr, int n)
{
    struct node *head = NULL;
    struct node *p;
 
    int i;
    for (i = 0; i < n; ++i) {
        if (head == NULL)
            head = p = (struct node *)malloc(sizeof(*p));
        else {
            p->next = (struct node *)malloc(sizeof(*p));
            p = p->next;
        }
        p->data = arr[i];
        p->next = p->child = NULL;
    }
    return head;
}
void printList(struct node *head)
{
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}
struct node *createList(void)
{
    int arr1[] = {10, 5, 12, 7, 11};
    int arr2[] = {4, 20, 13};
    int arr3[] = {17, 6};
    int arr4[] = {9, 8};
    int arr5[] = {19, 15};
    int arr6[] = {2};
    int arr7[] = {16};
    int arr8[] = {3};
 
    /* create 8 linked lists */
    struct node *head1 = createList(arr1, SIZE(arr1));
    struct node *head2 = createList(arr2, SIZE(arr2));
    struct node *head3 = createList(arr3, SIZE(arr3));
    struct node *head4 = createList(arr4, SIZE(arr4));
    struct node *head5 = createList(arr5, SIZE(arr5));
    struct node *head6 = createList(arr6, SIZE(arr6));
    struct node *head7 = createList(arr7, SIZE(arr7));
    struct node *head8 = createList(arr8, SIZE(arr8));
 
 
    /* modify child pointers to create the list shown above */
    head1->child = head2;
    head1->next->next->next->child = head3;
    head3->child = head4;
    head4->child = head5;
    head2->next->child = head6;
    head2->next->next->child = head7;
    head7->child = head8;
 
 
    /* Return head pointer of first linked list.  Note that all nodes are
       reachable from head1 */
    return head1;
}
void flattenList(struct node *head)
{
    /*Base case*/
    if (head == NULL)
       return;
 
    struct node *tmp;
 
    /* Find tail node of first level linked list */
    struct node *tail = head;
    while (tail->next != NULL)
        tail = tail->next;
 
    // One by one traverse through all nodes of first level
    // linked list till we reach the tail node
    struct node *cur = head;
    while (cur != tail)
    {
        // If current node has a child
        if (cur->child)
        {
            // then append the child at the end of current list
            tail->next = cur->child;
 
            // and update the tail to new last node
            tmp = cur->child;
            while (tmp->next)
                tmp = tmp->next;
            tail = tmp;
        }
 
        // Change current node
        cur = cur->next;
    }
}

QuickSort on Doubly Linked List
/* A typical recursive implementation of Quicksort for array*/
 
/* This function takes last element as pivot, places the pivot element at its
   correct position in sorted array, and places all smaller (smaller than 
   pivot) to left of pivot and all greater elements to right of pivot */
int partition (int arr[], int l, int h)
{
    int x = arr[h];
    int i = (l - 1);
 
    for (int j = l; j <= h- 1; j++)
    {
        if (arr[j] <= x)
        {
            i++;
            swap (&arr[i], &arr[j]);
        }
    }
    swap (&arr[i + 1], &arr[h]);
    return (i + 1);
}
 
/* A[] --> Array to be sorted, l  --> Starting index, h  --> Ending index */
void quickSort(int A[], int l, int h)
{
    if (l < h)
    {        
        int p = partition(A, l, h); /* Partitioning index */
        quickSort(A, l, p - 1);  
        quickSort(A, p + 1, h);
    }
}

void quickSort1(struct node *head)
{
    // Find last node
    struct node *h = lastnode(head);
 
    // Call the recursive QuickSort
    _quickSort(head, h);
}

void _quickSort(struct node* l, struct node *h)
{
    if (h != NULL && l != h && l != h->next)
    {
        struct node *p = partition(l, h);
        _quickSort(l, p->prev);
        _quickSort(p->next, h);
    }
}
node* partition(node *l, node *h)
{
    // set pivot as h element
    int x  = h->data;
 
    // similar to i = l-1 for array implementation
    node *i = l->prev;
 
    // Similar to "for (int j = l; j <= h- 1; j++)"
    for (node *j = l; j != h; j = j->next)
    {
        if (j->data <= x)
        {
            // Similar to i++ for array
            i = (i == NULL)? l : i->next;
 
            swap(&(i->data), &(j->data));
        }
    }
    i = (i == NULL)? l : i->next; // Similar to i++
    swap(&(i->data), &(h->data));
    return i;
}

struct node *lastnode(node *root)
{
    while (root && root->next)
        root = root->next;
    return root;
}
void swap ( int* a, int* b )
{   
	int t = *a; 
	*a = *b;
	*b = t;   
}

QuickSort on Singly Linked List
void quickSort2(struct node **headRef)
{
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
    return;
}
struct node *quickSortRecur(struct node *head, struct node *end)
{
    // base condition
    if (!head || head == end)
        return head;
 
    node *newHead = NULL, *newEnd = NULL;
 
    // Partition the list, newHead and newEnd will be updated
    // by the partition function
    struct node *pivot = partition(head, end, &newHead, &newEnd);
 
    // If pivot is the smallest element - no need to recur for
    // the left part.
    if (newHead != pivot)
    {
        // Set the node before the pivot node as NULL
        struct node *tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;
 
        // Recur for the list before pivot
        newHead = quickSortRecur(newHead, tmp);
 
        // Change next of last node of the left half to pivot
        tmp = getTail(newHead);
        tmp->next =  pivot;
    }
 
    // Recur for the list after the pivot element
    pivot->next = quickSortRecur(pivot->next, newEnd);
 
    return newHead;
}

struct node *partition(struct node *head, struct node *end,
                       struct node **newHead, struct node **newEnd)
{
    struct node *pivot = end;
    struct node *prev = NULL, *cur = head, *tail = pivot;
 
    // During partition, both the head and end of the list might change
    // which is updated in the newHead and newEnd variables
    while (cur != pivot)
    {
        if (cur->data < pivot->data)
        {
            // First node that has a value less than the pivot - becomes
            // the new head
            if ((*newHead) == NULL)
                (*newHead) = cur;
 
            prev = cur;  
            cur = cur->next;
        }
        else // If cur node is greater than pivot
        {
            // Move cur node to next of tail, and change tail
            if (prev)
                prev->next = cur->next;
            struct node *tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }
 
    // If the pivot data is the smallest element in the current list,
    // pivot becomes the head
    if ((*newHead) == NULL)
        (*newHead) = pivot;
 
    // Update newEnd to the current last node
    (*newEnd) = tail;
 
    // Return the pivot node
    return pivot;
}
struct node *getTail(struct node *cur)
{
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}
 
-----------------------------------------------------------

int findMiddle(myStack *ms)
{
    if (ms->count  ==  0)
    {
        printf("Stack is empty now\n");
        return -1;
    }
 
    return ms->mid->data;
}

typedef struct DLLnode
{
    DLLnode *prev;
    int data;
    DLLnode *next;
}DLLnode;

typedef struct myStack
{
    DLLnode *head;
    DLLnode *mid;
    int count;
}myStack;

myStack *createMyStack()
{
    myStack *ms =
               (myStack*) malloc(sizeof(myStack));
    ms->count = 0;
    return ms;
};

void push(myStack *ms, int new_data)
{
    DLLnode* new_DLLnode = new DLLnode;
    new_DLLnode->data  = new_data;
 
    new_DLLnode->prev = NULL;
 
    new_DLLnode->next = ms->head;
 
    ms->count += 1;
 
    if (ms->count == 1)
    {
         ms->mid = new_DLLnode;
    }
    else
    {
        ms->head->prev = new_DLLnode;
 
        if (ms->count & 1) 
           ms->mid = ms->mid->prev;
    }
 
    ms->head  = new_DLLnode;
}
 
int pop(myStack *ms)
{
    if (ms->count  ==  0)
    {
        printf("Stack is empty\n");
        return -1;
    }
 
    DLLnode *head = ms->head;
    int item = head->data;
    ms->head = head->next;
 
    if (ms->head != NULL)
        ms->head->prev = NULL;
 
    ms->count -= 1;
 
    if (!((ms->count) & 1 ))
        ms->mid = ms->mid->next;
 
    delete head;
 
    return item;
} 

Implement LRU Cache

typedef struct Qnode
{
    struct Qnode *prev, *next;
    unsigned pageNumber;  // the page number stored in this Qnode
} Qnode;
 
// A Queue (A FIFO collection of Queue nodes)
typedef struct Queue
{
    unsigned count;  // Number of filled frames
    unsigned numberOfFrames; // total number of frames
    Qnode *front, *rear;
} Queue;
 
// A hash (Collection of pointers to Queue nodes)
typedef struct Hash
{
    int capacity; // how many pages can be there
    Qnode* *array; // an array of queue nodes
} Hash;
 
// A utility function to create a new Queue node. The queue node
// will store the given 'pageNumber'
Qnode* newQnode( unsigned pageNumber )
{
    // Allocate memory and assign 'pageNumber'
    Qnode* temp = (Qnode *)malloc( sizeof( Qnode ) );
    temp->pageNumber = pageNumber;
 
    // Initialize prev and next as NULL
    temp->prev = temp->next = NULL;
 
    return temp;
}
 
// A utility function to create an empty Queue.
// The queue can have at most 'numberOfFrames' nodes
Queue* createQueue( int numberOfFrames )
{
    Queue* queue = (Queue *)malloc( sizeof( Queue ) );
 
    // The queue is empty
    queue->count = 0;
    queue->front = queue->rear = NULL;
 
    // Number of frames that can be stored in memory
    queue->numberOfFrames = numberOfFrames;
 
    return queue;
}
 
// A utility function to create an empty Hash of given capacity
Hash* createHash( int capacity )
{
    // Allocate memory for hash
    Hash* hash = (Hash *) malloc( sizeof( Hash ) );
    hash->capacity = capacity;
 
    // Create an array of pointers for refering queue nodes
    hash->array = (Qnode **) malloc( hash->capacity * sizeof( Qnode* ) );
 
    // Initialize all hash entries as empty
    int i;
    for( i = 0; i < hash->capacity; ++i )
        hash->array[i] = NULL;
 
    return hash;
}
 
// A function to check if there is slot available in memory
int AreAllFramesFull( Queue* queue )
{
    return queue->count == queue->numberOfFrames;
}
 
// A utility function to check if queue is empty
int isQueueEmpty( Queue* queue )
{
    return queue->rear == NULL;
}
 
// A utility function to delete a frame from queue
void deQueue( Queue* queue )
{
    if( isQueueEmpty( queue ) )
        return;
 
    // If this is the only node in list, then change front
    if (queue->front == queue->rear)
        queue->front = NULL;
 
    // Change rear and remove the previous rear
    Qnode* temp = queue->rear;
    queue->rear = queue->rear->prev;
 
    if (queue->rear)
        queue->rear->next = NULL;
 
    free( temp );
 
    // decrement the number of full frames by 1
    queue->count--;
}
 
// A function to add a page with given 'pageNumber' to both queue
// and hash
void Enqueue( Queue* queue, Hash* hash, unsigned pageNumber )
{
    // If all frames are full, remove the page at the rear
    if ( AreAllFramesFull ( queue ) )
    {
        // remove page from hash
        hash->array[ queue->rear->pageNumber ] = NULL;
        deQueue( queue );
    }
 
    // Create a new node with given page number,
    // And add the new node to the front of queue
    Qnode* temp = newQnode( pageNumber );
    temp->next = queue->front;
 
    // If queue is empty, change both front and rear pointers
    if ( isQueueEmpty( queue ) )
        queue->rear = queue->front = temp;
    else  // Else change the front
    {
        queue->front->prev = temp;
        queue->front = temp;
    }
 
    // Add page entry to hash also
    hash->array[ pageNumber ] = temp;
 
    // increment number of full frames
    queue->count++;
}
 
// This function is called when a page with given 'pageNumber' is referenced
// from cache (or memory). There are two cases:
// 1. Frame is not there in memory, we bring it in memory and add to the front
//    of queue
// 2. Frame is there in memory, we move the frame to front of queue
void ReferencePage( Queue* queue, Hash* hash, unsigned pageNumber )
{
    Qnode* reqPage = hash->array[ pageNumber ];
 
    // the page is not in cache, bring it
    if ( reqPage == NULL )
        Enqueue( queue, hash, pageNumber );
 
    // page is there and not at front, change pointer
    else if (reqPage != queue->front)
    {
        // Unlink rquested page from its current location
        // in queue.
        reqPage->prev->next = reqPage->next;
        if (reqPage->next)
           reqPage->next->prev = reqPage->prev;
 
        // If the requested page is rear, then change rear
        // as this node will be moved to front
        if (reqPage == queue->rear)
        {
           queue->rear = reqPage->prev;
           queue->rear->next = NULL;
        }
 
        // Put the requested page before current front
        reqPage->next = queue->front;
        reqPage->prev = NULL;
 
        // Change prev of current front
        reqPage->next->prev = reqPage;
 
        // Change front to the requested page
        queue->front = reqPage;
    }
}
 
// Driver program to test above functions
int main()
{
    // Let cache can hold 4 pages
    Queue* q = createQueue( 4 );
 
    // Let 10 different pages can be requested (pages to be
    // referenced are numbered from 0 to 9
    Hash* hash = createHash( 10 );
 
    // Let us refer pages 1, 2, 3, 1, 4, 5
    ReferencePage( q, hash, 1);
    ReferencePage( q, hash, 2);
    ReferencePage( q, hash, 3);
    ReferencePage( q, hash, 1);
    ReferencePage( q, hash, 4);
    ReferencePage( q, hash, 5);
 
    // Let us print cache frames after the above referenced pages
    printf ("%d ", q->front->pageNumber);
    printf ("%d ", q->front->next->pageNumber);
    printf ("%d ", q->front->next->next->pageNumber);
    printf ("%d ", q->front->next->next->next->pageNumber);
 
    return 0;
}
Output:

5 4 1 3

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







