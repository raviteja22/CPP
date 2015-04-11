01. isSubTree   15+20+4=35
02. connect
03. sortedArrayToBST
04. toSumTree
05. populateNext(inordr Succssor)
06. binaryTreeToBST
07. MergerTrees
08. largestBSTinBinaryTree
09. correctBST
10. printBoundary
11. isCompleteBT
12. verticalSum
13. hasOnlyOneChild
14. constructTree {'N', 'N', 'L', 'L', 'L'}
15. buildTree

01. hasPathSum
02. hasPathSums
03. hasMinPathSums
04. hasMaxPathSums
05. longestPathSum
06. longestPathLen
07. printLongestPath
08. printAllPaths
09. Flatten Binary Tree to Linked List 
10. Sum Root to Leaf Numbers 1 2 3 12 + 13 = 25
11. PrintSumPaths  venugopa
12. isSumProperty
13. printSorted
14. ceil , floor
15. deletenodeFromTree
16. allLeavesAtSameLevel
17. LL2CompleteBT
18. diffBetweenEvenOddHeight
19. printVerticalSumData
20. createLLWithEveryLevel

1. addnodeBT
2. sizeItr
3. sizeItr1
4. itrPreorder


if( isSubtree(T, S) )

1. bool isSubtree(node *T, node *S)
{
    if (S == NULL)
        return true;

    if (T == NULL)
        return false;

    if (areIdentical(T, S))
        return true;

    return isSubtree(T->left, S) ||
        isSubtree(T->next, S);
}

2. void connect (node *p)
{
    p->nextRight = NULL;
    connectRecur(p);
}
Method 1 (Extend Level Order Traversal or BFS) O(n)

Method 2 (Extend Pre Order Traversal) O(n)
void connectRecur(node* p)
{
    if (!p)        
	   return;

    if (p->left)
        p->left->nextRight = p->next;

    if (p->next)
        p->next->nextRight = (p->nextRight)? p->nextRight->left: NULL;

    connectRecur(p->left);
    connectRecur(p->next);
}

void connect (node *p)
{
    p->nextRight = NULL;

    connectRecur(p);
}
A Recursive Solution
  1
 2 3 
4 5  7 
void connectRecur(node* p)
{
    if (!p)
       return;
/* Before setting nextRight of left and next children, set nextRight
    of children of other nodes at same level (because we can access 
    children of other nodes using p's nextRight only) */
    if (p->nextRight != NULL)
       connectRecur(p->nextRight);

    if (p->left)
    {
       if (p->next)
       {
           p->left->nextRight = p->next;
           p->next->nextRight = getnextRight(p);
       }
       else
           p->left->nextRight = getnextRight(p);

       connectRecur(p->left);
    }
    else if (p->next)
    {
        p->next->nextRight = getnextRight(p);
        connectRecur(p->next);
    }
    else
       connectRecur(getnextRight(p));
}

node *getnextRight(node *p)
{
    node *temp = p->nextRight;

    while(temp != NULL)
    {
        if(temp->left != NULL)
            return temp->left;
        if(temp->next != NULL)
            return temp->next;
        temp = temp->nextRight;
    }

    return NULL;
}

void connect(node* p)
{
    node *temp;
 
    if (!p)
      return;

    p->nextRight = NULL;

    while (p != NULL)
    {
        node *q = p;

        while (q != NULL)
        {
            if (q->left)
            {
                if (q->next)
                    q->left->nextRight = q->next;
                else
                    q->left->nextRight = getnextRight(q);
            }
 
            if (q->next)
                q->next->nextRight = getnextRight(q);
 
            q = q->nextRight;
        }

        if (p->left)
           p = p->left;
        else if (p->next)
           p = p->next;
        else
           p = getnextRight(p);
    }
}

4. int toSumTree(node *root)
{
    if(root == NULL)
        return 0;

    int old_val = root->data;

    root->data = toSumTree(root->left) + toSumTree(root->next);

    return root->data + old_val;
}

5.  void populateNext(node* p)//inorder successor
{
    static node *next = NULL;

    if ( p )
    {
        populateNext(p->next);
        p->next = next;
        next = p;
        populateNext(p->left);
    }
}
populateNext(root);
node *ptr = root->left->left;
while(ptr)
{
    printf("Next of %d is %d \n", ptr->data, ptr->next? ptr->next->data: -1);
    ptr = ptr->next;
}
5. void populateNext(node *root)
{
    node *next = NULL;
    populateNextRecur(root, &next);
}

void populateNextRecur(node* p, node **next_ref)
{
    if (p)
    {
        populateNextRecur(p->next, next_ref);

        p->next = *next_ref;
        *next_ref = p;
        populateNextRecur(p->left, next_ref);
    }
}

6. void binaryTreeToBST (node *root)
{
    if(root == NULL)
        return;

    int n = countnodes (root);

    int *arr = new int[n];
    int i = 0;
    storeInorder (root, arr, &i);

    qsort (arr, n, sizeof(arr[0]), compare);

    i = 0;
    arrayToBST (arr, root, &i);

    delete [] arr;
}
void storeInorder (node* node, int inorder[], int *indexPtr)
{
    if (node == NULL)
        return;

    storeInorder (root->left, inorder, indexPtr);

    inorder[*indexPtr] = root->data;
    (*indexPtr)++;  

    storeInorder (root->next, inorder, indexPtr);
}
int compare (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

void arrayToBST (int *arr, node* root, int *indexPtr)
{
    if (root == NULL)
        return;

    arrayToBST (arr, root->left, indexPtr);

    root->data = arr[*indexPtr];
    (*indexPtr)++;

    arrayToBST (arr, root->next, indexPtr);
}
int countnodes (node* root)
{
    if (root == NULL)
        return 0;
    return countnodes (root->left) +
        countnodes (root->next) + 1;
}

7. node* mergeTrees(node *root1, node *root2, int m, int n)
{
    int *arr1 = new int[m];
    int i = 0;
    storeInorder(root1, arr1, &i);

    int *arr2 = new int[n];
    int j = 0;
    storeInorder(root2, arr2, &j);

    int *mergedArr = merge(arr1, arr2, m, n);

    return sortedArrayToBST (mergedArr, 0, m+n-1);
}

int *merge(int arr1[], int arr2[], int m, int n)
{
    int *mergedArr = new int[m + n];
    int i = 0, j = 0, k = 0;

    while (i < m && j < n)
    {
        if (arr1[i] < arr2[j])
        {
            mergedArr[k++] = arr1[i++];
        }
        else
        {
            mergedArr[k++] = arr2[j++];
        }
    }

    while (i < m)
    {
        mergedArr[k] = arr1[i];
        i++; k++;
    }

    while (j < n)
    {
        mergedArr[k] = arr2[j];
        j++; k++;
    }

    return mergedArr;
}
 
7. void  merge(node *root1, node *root2)
{
    struct snode *s1 = NULL;
    node  *current1 = root1;
    struct snode *s2 = NULL;
    node  *current2 = root2;

    if (root1 == NULL)
    {
        inorder(root2);
        return;
    }
    if (root2 == NULL)
    {
        inorder(root1);
        return ;
    }

    while (current1 != NULL || !isEmpty(s1) ||
            current2 != NULL || !isEmpty(s2))
    {
        if (current1 != NULL || current2 != NULL )
        {
            if (current1 != NULL)
            {
                push(&s1, current1);
                current1 = current1->left;
            }
            if (current2 != NULL)
            {
                push(&s2, current2);
                current2 = current2->left;
            }

        }
        else
        {
            if (isEmpty(s1))
            {
                while (!isEmpty(s2))
                {
                    current2 = pop (&s2);
                    current2->left = NULL;
                    inorder(current2);
                }
                return ;
            }
 

            if (isEmpty(s2))
            {
                while (!isEmpty(s1))
                {
                    current1 = pop (&s1);
                    current1->left = NULL;
                    inorder(current1);
                }
                return ;
            }

            current1 = pop(&s1);
            current2 = pop(&s2);

            if (current1->data < current2->data)
            {
                printf("%d ", current1->data);
                current1 = current1->next;
                push(&s2, current2);
                current2 = NULL;
            }
            else
            {
                printf("%d ", current2->data);
                current2 = current2->next;
                push(&s1, current1);
                current1 = NULL;
            }
        }
    }
}
 
8. int largestBST(node *root)
{
    if (isBST(root))
        return size(root);
    else
        return max(largestBST(root->left), largestBST(root->next));
}

/* Returns size of the largest BST subtree in a Binary Tree
  (efficient version). */
8. int largestBST(node* node)
{
  int min = INT_MAX;  
  int max = INT_MIN;  
 
  int max_size = 0;  
  bool is_bst = 0;
 
  largestBSTUtil(node, &min, &max, &max_size, &is_bst);
 
  return max_size;
}

int largestBSTUtil(node* node, int *min_ref, int *max_ref,
                            int *max_size_ref, bool *is_bst_ref)
{

  if (node == NULL)
  {
     *is_bst_ref = 1; 
     return 0;    
  }
   int min = INT_MAX;

  bool left_flag = false;

  bool next_flag = false;
 
  int ls, rs; 

  *max_ref = INT_MIN;
  ls = largestBSTUtil(root->left, min_ref, max_ref, max_size_ref, is_bst_ref);
  if (*is_bst_ref == 1 && root->data > *max_ref)
     left_flag = true;

  min = *min_ref;

  *min_ref =  INT_MAX;
  rs = largestBSTUtil(root->next, min_ref, max_ref, max_size_ref, is_bst_ref);
  if (*is_bst_ref == 1 && root->data < *min_ref)
     next_flag = true;

  if (min < *min_ref)
     *min_ref = min;
  if (root->data < *min_ref) 
     *min_ref = root->data;
  if (root->data > *max_ref)
     *max_ref = root->data;

  if(left_flag && next_flag)
  {
     if (ls + rs + 1 > *max_size_ref)
         *max_size_ref = ls + rs + 1;
     return ls + rs + 1;
  }
  else
  {
     *is_bst_ref = 0;
     return 0;
  }
}
 
9.
printInorder(root);
correctBST(root,INT_MIN,INT_MAX);
swap(first,second);
printInorder(root);

void correctBSTUtil( node* root, node** first,middle,last,prev )
{
    if( root )
    {
        correctBSTUtil( root->left, first, middle, last, prev );

        if (*prev && root->data < (*prev)->data)
        {
            if ( !*first )
            {
                *first = *prev;
                *middle = root;
            }
            else
			{
                *last = root;
			}	
        }
 
        *prev = root;

        correctBSTUtil( root->next, first, middle, last, prev );
    }
}
        20
	  8    22
    4  12     25
      10 14
	  
---> 20 8 4 10 14 25 22	  
10. void printBoundary (node* root)
{
    if (root)
    {
        printf("%d ",root->data);

        printBoundaryLeft(root->left);
        printLeaves(root->left);
        printLeaves(root->next);
        printBoundarynext(root->next);
    }
}

void printBoundaryLeft(node* root)
{
    if (root)
    {
        if (root->left)
        {
            printf("%d ", root->data);
            printBoundaryLeft(root->left);
        }
        else if( root->next )
        {
            printf("%d ", root->data);
            printBoundaryLeft(root->next);
        }
    }
}
void printBoundarynext(node* root)
{
    if (root)
    {
        if ( root->next )
        {
            printBoundarynext(root->next);
            printf("%d ", root->data);
        }
        else if ( root->left )
        {
            printBoundarynext(root->left);
            printf("%d ", root->data);
        }
    }
}
void printLeaves(node* root)
{
    if ( root )
    {
        printLeaves(root->left);
 
       if ( (root->left == NULL)  &&  (root->next == NULL) )
            printf("%d ", root->data);
 
        printLeaves(root->next);
    }
}

11. bool isCompleteBT(node* root)
{
  if (root == NULL)
    return true;
  
  node *a[100]={NULL};
  int f = 0 , b = 0;
  bool flag = false;
 
  while(root)
  {
    if(root->left)
    {
       if (flag == true)
         return false;
       a[b++] = root->left;
    }
    else 
    {
       flag = true;
    }
 
    if(root->next)
    {
       if(flag == true)
         return false;
       a[b++] = root->next;
    }
    else 
    {
       flag = true;
    }
    root = a[f++];
   }
  return true;
}
//another version
11. bool isCompleteBT(node* root)
{
   if (root == NULL)
    return true;
 
  int rear, front;
  node **queue = createQueue(&front, &rear);
 
  bool flag = false;
 
  enQueue(queue, &rear, root);
  while(!isQueueEmpty(&front, &rear))
  {
    node *temp_node = deQueue(queue, &front);
 
    if(temp_root->left)
    {
       if (flag == true)
         return false;
 
       enQueue(queue, &rear, temp_root->left);
    }
    else 
       flag = true;
 
   if(temp_root->next)
    {
       if(flag == true)
         return false;
 
       enQueue(queue, &rear, temp_root->next); 
    }
    else 
       flag = true;
  }
  return true;
}

int *findVerticalSum(node *root,int *len)
{
    int SpanCount,leftSpan,nextSpan;
    leftSpan=nextSpan=SpanCount=0;
    maxLeftnext(root,0,&leftSpan,&nextSpan);
 
    SpanCount = nextSpan-leftSpan + 1;
 
    int *arr = new int[SpanCount];
 
    findVerticalSumRec(root,0,arr,-leftSpan); // preorder traversal recursion
    *len = SpanCount;
    return arr;
}
void maxLeftnext(node * node,int curHD,int *left,int *next)
{
    if(node==NULL) 
	    return;
    
	if(curHD < *left) *left=curHD;
    else if(curHD > *next) *next=curHD;
    
	maxLeftnext(root->left,curHD-1,left,next);
    maxLeftnext(root->next,curHD+1,left,next);
}
 
 
void findVerticalSumRec(node *root,int HD,int *arr,int leftMargin) 
{
    if(root)
    {
        printf("Data : %d, HD: %d\n",root->data,HD);
        arr[leftMargin+HD] += root->data;
 
        findVerticalSumRec(root->left,HD-1,arr,leftMargin); 
        findVerticalSumRec(root->next,HD+1,arr,leftMargin);
    }
}

12. bool hasOnlyOneChild(int pre[], int size)
{							//{8, 3, 5, 7, 6};
    int nextDiff; 
    int lastDiff; 
 
    for(int i=0; i<size; i++)
    {
        nextDiff = pre[i] - pre[i+1];
        lastDiff = pre[i] - pre[size-1];
        if(nextDiff*lastDiff < 0)
            return false;;
    }
    return true;
}

12. int hasOnlyOneChild(int pre[], int size)
{						//{8, 3, 5, 7, 6};
    int min, max;
    if (pre[size-1] > pre[size-2])
    {
        max = pre[size-1];
        min = pre[size-2]):
    else
    {
        max = pre[size-2];
        min = pre[size-1];
    }
    for(int i=size-3; i>=0; i--)
    {
        if (pre[i] < min)
            min = pre[i]; //6 , 5 , 3 
        else if (pre[i] > max)
            max = pre[i]; // 7 , 8
        else
            return false;
    }
    return true;
}
 
Input:  pre[] = {10, 30, 20, 5, 15},  
preLN[] = {'N', 'N', 'L', 'L', 'L'}

          10
         /  \
        30   15
       /  \
      20   5
// A wrapper over constructTreeUtil()
14. node *constructTree(int pre[], char preLN[], int n)
{
   int index = 0;
  return constructTreeUtil (pre, preLN, &index, n);
}
 
node *constructTreeUtil(int pre[], char preLN[], int *index_ptr, int n)
{
    int index = *index_ptr;  
  
    if (index == n)
        return NULL;
 
    node *temp = createNew ( pre[index] );
    (*index_ptr)++;  // {10, 30, 20, 5, 15} 
					 // {'N', 'N', 'L', 'L', 'L'} 
	// If this is an internal node, construct left and next subtrees and link the subtrees
    if (preLN[index] == 'N')
    {
      temp->left  = constructTreeUtil(pre, preLN, index_ptr, n);
      temp->next = constructTreeUtil(pre, preLN, index_ptr, n);
    }
 
    return temp;
}
 
Construct Special Binary Tree from given Inorder traversal
Input: inorder[] = {5, 10, 40, 30, 28}
Output: root of following tree
         40
      10     30
    5          28 

{1, 5, 10, 40, 30, 15, 28, 20}. 
         40
 {1,5,10} {30,15,28,20}

         40
       10   30
     5       28
   1      15   20
 

node* buildTree (int inorder[], int start, int end)
{
    if (start > end)
        return NULL;
 
    int i = max (inorder, start, end);

    node *root = createNew(inorder[i]);

    if (start == end)
        return root;
 
    root->left  = buildTree (inorder, start, i-1);
    root->next = buildTree (inorder, i+1, end);
 
    return root;
}

int max (int arr[], int strt, int end)
{
    int i, max = arr[strt], maxind = strt;
    for(i = strt+1; i <= end; i++)
    {
        if(arr[i] > max)
        {
            max = arr[i];
            maxind = i;
        }
    }
    return maxind;
}





bool hasPathSum(node * root, int sum) 
 {
    if(root==null)
        return false;
    if(root->left==null && root->next==null && root->val==sum)
        return true;
    else
        return hasPathSum(root->left, sum-root->val)||
				 hasPathSum(root->next,sum-root->val);
}

bool hasPathSum(node *root, int sum)
{
	if (root == NULL) 
	     return false;
	if (root->left == NULL && root->next == NULL)
		return sum == root->val;

	return hasPathSum(root->left, sum - root->val) || 
	        hasPathSum(root->next, sum - root->val);
}

bool hasPathSum(node *root , int sum)
{
     static bool flag = 0;
     if(!flag)
     {
        if(root)
        {
             int subSum = sum - root->data;   
             hasPathSum(root->left , subSum);
             
             if(root->left == NULL && root->next == NULL)
             {
                 if(subSum == 0)
                   flag = 1;              
             } 
             hasPathSum(root->next , subSum);
        }
     }
     return flag;        
}
bool hasPathSum(struct node* node, int sum)
{
  if (node == NULL)
  {
     return (sum == 0);
  }
  
  else
  {
    bool ans = 0;  
  
    int subSum = sum - node->data;

    if ( subSum == 0 && node->left == NULL && node->next == NULL )
      return 1;
  
    if(node->left)
      ans = ans || hasPathSum(node->left, subSum);
    if(node->next)
      ans = ans || hasPathSum(node->next, subSum);
  
    return ans;
  }
}
int hasPathSums(node *root , int sum)
{
    static int count = 0;
    
    if(root)
    {
         int subSum = sum - root->data;   
         hasPathSums(root->left , subSum);
             
         if(root->left == NULL && root->next == NULL)
         {
              if(subSum == 0)
                 count++;              
          } 
         hasPathSums(root->next , subSum);
     }     
     return count;    
}

int minPathSum(node *root , int sum)
{
    static int min = INT_MAX;
    
    if(root)
    {
         int subSum = sum + root->data;   
         minPathSum(root->left , subSum);
             
         if(root->left == NULL && root->next == NULL)
         {
              if(subSum < min)
                 min = subSum;              
          } 
         minPathSum(root->next , subSum);
     }     
     return min;    
}

int maxPathSum(node *root , int sum)
{
    static int max = INT_MIN;
    
    if(root)
    {
         int subSum = sum + root->data;   
         maxPathSum(root->left , subSum);
             
         if(root->left == NULL && root->next == NULL)
         {
              if(subSum > max)
                 max = subSum;              
          } 
         maxPathSum(root->next , subSum);
     }     
     return max; 
}

int longestPathLen(node *root , int sum)
{
   static int max = INT_MIN;
    
    if(root)
    {
         sum++;   
         longestPathLen(root->left , sum);
             
         if(root->left == NULL && root->next == NULL)
         {
              if(sum > max)
                 max = sum;              
          } 
         longestPathLen(root->next , sum);
     }     
     return max;    
}
int longestPathSum(node *root , int sum , int len)
{
   static int max = INT_MIN , maxSum = 0;
    
    if(root)
    {
         int subSum = sum + root->data;   
         len++;
         longestPathSum(root->left , subSum , len);
             
         if(root->left == NULL && root->next == NULL)
         {
              if(len >= max)
              {                     
                 maxSum = subSum;   
                 max = len;           
              }
          } 
         longestPathSum(root->next , subSum , len);
     }     
     return maxSum;     
}

//cout<<"printLongestPath :: "<<endl; printLongestPath(root,0,&root1);  
//printCloseAncestor(root,root1->data);

void printLongestPath(node *root , int sum , node **leaf)
{
    static int max = INT_MIN;
    
    if(root)
    {
         sum++;   
         printLongestPath(root->left , sum , leaf);
             
         if(root->left == NULL && root->next == NULL)
         {
              if(sum >= max)
              {
                 max = sum;              
                 *leaf = root;   
              }
          } 
         printLongestPath(root->next , sum , leaf);
     }     
}

bool printCloseAncestor(node *root , int val)
{
   if(root==NULL)
     return 0;
     
   if(root->data == val)
   {
     cout<<root->data<<" ";            
     return 1;       
   }
     
   if(printCloseAncestor(root->left,val) 
      || printCloseAncestor(root->next,val))
   {
       cout<<root->data<<" ";
       return 1;                                      
   }  
   return 0;
} 

void printAllPaths(node *root , int *arr, int len)
{
	if(root == NULL)
		return ;

	arr[len++] = root->data;

	printAllPaths(root->left , arr , len);

	if(root->left == NULL && root->next == NULL)	
	{
		print(arr,len);	
	}
	printAllPaths(root->next , arr , len);
}
void print(int *arr , int len)
{
	for(int i = 0 ; i < len ; i++)
		cout<<arr[i]<<" ";
	cout<<endl;
}




         1
        / \
       2   5
      / \   \
     3   4   6
1
 2
  3
   4
    5
	 6
http://discuss.leetcode.com/questions/280/flatten-binary-tree-to-linked-list

void flatten(node *root) 
{
    if (!root) 
	    return;

    node* left = root->left;
    node* next = root->next;

    if (left) 
	{
        root->next = left;
        root->left = NULL;

        node* nextmost = left;
        while(nextmost->next)
		{
			nextmost = nextmost->next;
		}
        nextmost->next = next; // point the next most to the original next child
    }

    flatten(root->next);        
}

void flatten(node *root)
{
    node* temp = NULL;
    postorder(root, temp);
}

void postorder(node* root , node*& temp) 
{
    if (root)
	{
        postorder(root->next,temp);
        postorder(root->left,temp);
        root->next = temp;
        temp = node;
        root->left = NULL;
    }
}
 1
2 3 
12 + 13 = 25
int sumNumbers(Treenode *root) 
{
    int num = 0, sum = 0;
    sumNumbersImpl(root, num, sum);
    return sum;
}

void sumNumbersImpl(Treenode *root, int& num, int& sum) 
{
    if (root == nullptr) return;
    num = num * 10 + root->val;
   
    if (root->left == nullptr && root->next == nullptr) 
	{
        sum += num;
    } 
	else 
	{
        sumNumbersImpl(root->left, num, sum);
        sumNumbersImpl(root->next, num, sum);
    }
    num /= 10;
}

int sumNumbers(Treenode *root)
{
    return sumNumbersImpl(root, 0);
}

int sumNumbersImpl(Treenode *root, int num) 
{
    if (root == nullptr) return 0;
    num = num * 10 + root->val;
    if (root->left == nullptr && root->next == nullptr)
        return num;
    else
        return sumNumbersImpl(root->left, num)
             + sumNumbersImpl(root->next, num);
}

void helper (Treenode *root,int &Sum, int target)
{
    if (!root) 
	     return;
		 
    target+=root->val;
    if(!root->left && !root->next)
    {
        Sum+=target;
        return;

    }

    helper(root->left,Sum,target*10);
    helper(root->next,Sum,target*10);
}

Binary Tree Maximum Path Sum

 1
2 3
sum = 6  

int maxPathSum(Treenode *root) 
{
        int csum;
        int maxsum = INT_MIN;
        maxPathSumHelper(root, csum, maxsum);
        return maxsum;

}


void maxPathSumHelper(Treenode *node, int &csum, int &maxsum) 
{
        if (!node)
		{
            csum = 0;
            return;
        }
        int lsum = 0, rsum = 0;
        maxPathSumHelper(root->left, lsum, maxsum);
        maxPathSumHelper(root->next, rsum, maxsum);
        csum = max(root->val, max(root->val + lsum, root->val + rsum));
        maxsum = max(maxsum, max(csum, root->val + lsum + rsum));
}

-----------------------------------------------------------------

int GetSum(list<node*>& lst)
{
	int sum = 0;
	for(list<node*>::iterator iter = lst.begin(); iter != lst.end(); iter++)
	{
		sum += (*iter)->data;
	}
	return sum;
}

int printPath(list<node*>& lst)
{
	for(list<node*>::iterator iter = lst.begin(); iter != lst.end(); iter++)
	{
		cout << (*iter)->data <<"\t";
	}
	cout << endl;
}

void PrintSumPaths(node* root, list<node*> lst, int sum)
{

	if(!root)
		return;
	
	lst.push_back(root);
	int pathSum = GetSum(lst);
	if(pathSum == sum)
	{
		printPath(lst);
		lst.pop_front();
	}
	else if(pathSum > sum)
	{
		while(GetSum(lst) > sum && !lst.empty())
		{
			lst.pop_front();
			if(GetSum(lst) == sum)
				printPath(lst);
		}
	}
	
	if(root->left)
	{
		PrintSumPaths(root->left, lst, sum);
	}

	if(root->next)
	{ 
		PrintSumPaths(root->next, lst, sum);
	}
	
	lst.remove(root);	
}


int main()
{
	node* root = ConstructBSTree();
	PrintInOrder(root);
	cout <<endl<<endl;
	PrintPreOrder(root);
	cout << endl<< endl;
	cout << "Enter sum number: "<<endl;
	int sum;
	cin >> sum;
	list<node*> lst;
	PrintSumPaths(root, lst, sum);	
}
  
int isSumProperty(root* node)
{
  int leftData = 0, nextData = 0;

  if(root == NULL ||(root->left == NULL && root->next == NULL))
  {
    return 1;
  }
  else
  {
    if(root->left)
      leftData = root->left->data;
 

    if(root->next)
      nextData = root->next->data;

    if((root->data == leftData + nextData)&&
        isSumProperty(root->left) &&
        isSumProperty(root->next))
      return 1;
    else
      return 0;
  }
} 
// For example, given an array [4, 2, 5, 1, 3], the function should print 1, 2, 3, 4, 5
// Sorted order printing of a given array that represents a BST
void printSorted(int arr[], int start, int end)
{     
  if(start > end)
    return;
 
  // print left subtree
  printSorted(arr, start*2 + 1, end);
 
  // print root
  printf("%d  ", arr[start]);
 
  // print next subtree
  printSorted(arr, start*2 + 2, end);  
}

Binary Tree Maximum Path Sum
	   1
      / \
     2   3
return 6

class Solution {
public:
   int maxPathSum(Treenode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int csum;
        int maxsum = INT_MIN;
        maxPathSumHelper(root, csum, maxsum);
        return maxsum;

    }
    void maxPathSumHelper(Treenode *node, int &csum, int &maxsum) {
        if (!node) {
            csum = 0;
            return;
        }
        int lsum = 0, rsum = 0;
        maxPathSumHelper(root->left, lsum, maxsum);
        maxPathSumHelper(root->next, rsum, maxsum);
        csum = max(root->val, max(root->val + lsum, root->val + rsum));
        maxsum = max(maxsum, max(csum, root->val + lsum + rsum));
    }
};



// probs on Binary Trees ( BT ) 
void addnodeBT(node **root , int val)
{
    node *temp = new node;
    temp->data = val;
    temp->left = NULL;
    temp->next = NULL;

    if(*root == NULL)
    {
        *root = temp;
    }
    else
    {
        node *a[10]={NULL};
        int start = 0 , end = 0;   
        node *cur = *root ;
        while(cur)
        {
            if(cur->left)
            {
                a[end++] = cur->left   ;
            } 
            else
            {
               cur->left = temp;
               return ; 
            }
            if(cur->next)
            {
                a[end++]= cur->next;
            }
            else
            {
                cur->next = temp;
                return ;
            }
            cur = a[start++];
        }
    }
}
int sizeRec(node *root)
{
    if(root == NULL)
        return 0;
    else
        return ( 1 + sizeRec(root->left) + sizeRec(root->next) );
}
int sizeItr(node *root)
{
    node *a[10]={NULL};
    int front = 0 , end = 0 , c = 0;
    node *cur = root;

    while(cur)
    {
        c++;
        if(cur->left)
            a[end++] = cur->left;
        if(cur->next)
            a[end++] = cur->next;
        cur = a[front++];
    }

    return c;
}

int sizeItr1(node *root)
{
    int front = 0 , end = 0 , c = 0;
    queue<node *> a;   

    while(root)
    {
        c++;
        if(root->left)
            a.push(root->left);
        if(root->next)
            a.push(root->next);
        root = a.front();
        a.pop();
    }

    return c;
}
 
int leafItr(node *root)
{
    int front = 0 , end = 0 , c = 0;
    queue<node *> a;   

    while(root)
    {
        if(root->left)
            a.push(root->left);
        if(root->next)
            a.push(root->next);
        if( (root->left == NULL ) && (root->next == NULL))
            c++;
        root = a.front();
        a.pop();
    }

    return c;
}

