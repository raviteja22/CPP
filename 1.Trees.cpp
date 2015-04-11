PrintSumPaths  15+30=45    45+35+15=95
01. isBST1 
02. diameter
03. isBalance
04. LCA
05. itrPreorder
06. inOrderItr
07. itrPostorder
08. morrisTree
09. isPairPresent
10. isTripletPresent
11. addGreater
12. sortedArrayToBST
13. convertBST2DLL
14. convertBST2CLL
15. trimTree

01.	addnodeParent
02.	size1
03.	height
04.	max
05.	identical
06.	mirrorCopy
07.	mirrorCopyNewTree
08.	min
09.	leafCount
10.	nthnodeLeft
11.	DFS
12.	levelOrder
13.	levelOrderRev
13. printSpiral
14.	searchnode
15.	closeAncestor
16.	printCloseAncestor
17.	doubletree
18.	printAllPaths
19.	levelOfTree
20.	printKDistance
21.	printnodesInRange
22.	getMaxWidth
23.	sumTree
24.	inorderSuccessor
25.	isDiffMoreThanTwo
26.	convertToDLL
27.	buildTree
28. deleteTree
29. findCommon  // need to run

bool  isBST1(node *root)
{
      if(root == NULL)
        return 1;
        
      if(root->left && max(root->left) >= root->data)
         return 0;
      if(root->next && min(root->next) <= root->data)
         return 0;
         
      if( !isBST1(root->left) || !isBST1(root->next))
         return 0;
         
       return 1;          
}

bool  isBST2(node *root , int min , int max)
{
    if(root == NULL)
    {           
      return 1;
    }
    
    if(root->data < min || root->data > max)
       return 0;
    
    return isBST2(root->left , min , root->data) 
            && isBST2(root->next,root->data , max);                
      
}
Using In-Order Traversal
bool isBST(node* root)
{
    static node *prev = NULL;

    if (root)
    {
        if (!isBST(root->left))
          return false;

        if (prev != NULL && root->data <= prev->data)
          return false;
 
        prev = root;
 
        return isBST(root->next);
    } 
    return true;
}
The diameter of a tree (sometimes called the width) is the number of nodes 
on the longest path between two leaves in the tree.
The diameter of a tree T is the largest of the following quantities:

* the diameter of T’s left subtree
* the diameter of T’s next subtree
* the longest path between leaves that goes through the root of T 
(this can be computed from the heights of the subtrees of T)

int diameter1(node *root)
{
    if(root==NULL)
      return 0;
    
    int lh = height(root->left);
    int rh = height(root->next);
    
    int ld = diameter1(root->left);
    int rd = diameter1(root->next);
    
    return Max( (lh + rh + 1) , Max(ld,rd));
      
}
int diameter2(node *root , int *height)
{
    if(root==NULL)
    {
       *height = 0;
        return 0;              
    }   
    
    int lh = 0 , rh = 0;
    
    int ld = diameter2(root->left , &lh);
    int rd = diameter2(root->next , &rh);
    
    *height = lh > rh ? lh+1 : rh+1;
    
    return Max( (lh + rh + 1) , Max(ld,rd));    
}

bool isBalnace1(node *root)
{
   if(root==NULL)
      return 1;
      
   int lh = height(root->left);
   int rh = height(root->next);
   
   return ( (abs(lh-rh) <=1) && isBalnace1(root->left) 
				&& isBalnace1(root->next));       
}

bool isBalnace2(node *root , int *height)
{
   if(root == NULL)
   {
      *height = 0;
      return 1;        
   }     
   int lh = 0 , rh = 0;
   
   int l = isBalnace2(root->left , &lh);
   int r = isBalnace2(root->next , &rh);
   
   *height = lh > rh ? lh+1 : rh+1;
   
   if( abs(lh - rh)>=2)
      return 0;
   else
      return l && r;   
}

int LCA1(node *root , node *p , node *q)
{
    
   if(root == NULL || p == NULL || q == NULL)
      return -1;
      
   if( Max(p->data , q->data) < root->data)
   {
      return LCA1(root->left,p,q); // forgot return 
   }
   else if( Min(p->data,q->data) > root->data)
   {
      return LCA1(root->next,p,q); // forgot return 
   }
   else
   {
      return root->data;              
   }
}
node* LCA2(node *root , node *p , node *q)
{            
   //NOT HERE // cout<<root->data<<" "<<p->data<<" "<<q->data<<endl;
  
    if(root == NULL || p == NULL || q == NULL)
    {        
       return NULL;       
    }
    if(root == p || root == q)
    { 
       return root;
    }
      
    node *l = LCA2(root->left,p,q);
    node *r = LCA2(root->next,p,q);
    
    if( l && r )
       return root;
    else
       return l ? l : r;
           
}

// parent ptr given

node *LCA(node *root, node *p, node *q) 
{
  hash_set<node *> visited;
  while (p || q)
  {
    if (p) {
      if (!visited.insert(p).second)
        return p; // insert p failed (p exists in the table)
      p = p->parent;
    }
    if (q) 
	{
      if (!visited.insert(q).second)
        return q; // insert q failed (q exists in the table)
      q = q->parent;
    }
  }
  return NULL;
}

int getHeight(node *p) 
{
  int height = 0;
  while (p) 
  {
    height++;
    p = p->parent;
  }
  return height;
}
 
// As root->parent is NULL, we don't need to pass root in.
node *LCA(node *p, node *q) 
{
  int h1 = getHeight(p);
  int h2 = getHeight(q);
  // swap both nodes in case p is deeper than q.
  if (h1 > h2) 
  {
    swap(h1, h2);
    swap(p, q);
  }
  // invariant: h1 <= h2.
  int dh = h2 - h1;
  for (int h = 0; h < dh; h++)
    q = q->parent;
  while (p && q) 
  {
    if (p == q) return p;
    p = p->parent;
    q = q->parent;
  }
  return NULL;  // p and q are not in the same tree
}
int LCA3(node* root, int n1, int n2)
{
  /* If we have reached a leaf node then LCA doesn't exist 
     If root->data is equal to any of the inputs then input is not valid. For example 20, 22 in the given figure */ 
  if(root == NULL || root->data == n1 || root->data == n2)
    return -1; 
   
  /* If any of the input nodes is child of the current node we have reached the LCA. For example, 
        in the above figure if we want to calculate LCA of 12 and 14, recursion should 
     terminate when we reach 8*/
	 
  if((root->next != NULL) && 
    (root->next->data == n1 || root->next->data == n2))
    return root->data;
  if((root->left != NULL) && 
    (root->left->data == n1 || root->left->data == n2))
    return root->data;    
     
  if(root->data > n1 && root->data < n2)
    return root->data;
  if(root->data > n1 && root->data > n2)
    return LCA3(root->left, n1, n2);
  if(root->data < n1 && root->data < n2)
    return LCA3(root->next, n1, n2);
}    

void itrPreorder(node *root)
{
    if (root == NULL)
       return;

    stack<node *> st;
    st.push(root);

    while ( !st.empty())
    {
        node *node = st.top();
        cout<<root->data<<endl;
        st.pop();

        if (root->next)
            st.push(root->next);
        if (root->left)
            st.push(root->left);
    }
}

void inOrder(node *root)
{
  node *current = root;
  stack<node *> s;  
  bool done = 0;
 
  while (!done)
  {
    while(current !=  NULL)
    {
      s.push(current);                                               
      current = current->left;  
    }                                                        

      if (!s.empty())
      {
        current = s.top(); s.pop();
        cout<<root->data<<endl;
        current = current->next;
      }
      else
	  {
        done = 1; 
	  }

  } /* end of while */ 
}     

void itrPostorder(node* root)
{
    stack<node *> s1;
    stack<node *> s2;

    push(s1, root);
    node* node;

    while (!isEmpty(s1))
    {
        node = pop(s1);
        push(s2, node);

        if (root->left)
            push(s1, root->left);
        if (root->next)
            push(s1, root->next);
    }

    while (!isEmpty(s2))
    {
        node = pop(s2);
        cout<<root->data<<endl;
    }
}

void itrPostorder(node* root)
{
    if (root == NULL)
        return;
     
    stack<node *> st;
    do
    {
        while (root)
        {
            if (root->next)
                push(st, root->next);
            push(st, root);
            root = root->left;
        }
 
        root = pop(st);

        if (root->next && peek(st) == root->next)
        {
            pop(st);  
            push(st, root);  
            root = root->next; 
        }
        else  
        {
            cout<<root->data<<endl;
            root = NULL;
        }
    } while (!isEmpty(st));
}


Morris traversal for Preorder
Using Morris Traversal, we can traverse the tree without using stack and recursion. The algorithm for Preorder is almost similar to Morris traversal for Inorder.

1...If left child is null, print the current node data. Move to next child.
….Else, Make the next child of the inorder predecessor point to the current node. Two cases arise:
………a) The next child of the inorder predecessor already points to the current node. Set next child to NULL. Move to next child of current node.
………b) The next child is NULL. Set it to current node. Print current node’s data and move to left child of current node.
2...Iterate until current node is not NULL.

void morrisTraversalPreorder(node* root)
{
    while (root)
    {
        // If left child is null, print the current node data. Move to
        // next child.
        if (root->left == NULL)
        {
            printf( "%d ", root->data );
            root = root->next;
        }
        else
        {
            // Find inorder predecessor
            node* current = root->left;
            while (current->next && current->next != root)
                current = current->next;
 
            // If the next child of inorder predecessor already points to
            // this node
            if (current->next == root)
            {
                current->next = NULL;
                root = root->next;
            }
 
            // If next child doesn't point to this node, then print this
            // node and make next child point to this node
            else
            {
                printf("%d ", root->data);
                current->next = root;
                root = root->left;
            }
        }
    }
}

Inorder Tree Traversal without recursion and without stack!

Using Morris Traversal, we can traverse the tree without using stack and recursion. The idea of Morris Traversal is based on Threaded Binary Tree. In this traversal, we first create links to Inorder successor and print the data using these links, and finally revert the changes to restore original tree.

1. Initialize current as root 
2. While current is not NULL
   If current does not have left child
      a) Print current’s data
      b) Go to the next, i.e., current = current->next
   Else
      a) Make current as next child of the nextmost node in current's left subtree
      b) Go to this left child, i.e., current = current->left
Although the tree is modified through the traversal, it is reverted back to its original shape after the completion. Unlike Stack based traversal, no extra space is required for this traversal.

void MorrisTraversal(struct tnode *root) // inorder
{
  struct tnode *current,*pre;
 
  if(root == NULL)
     return; 
 
  current = root;
  while(current != NULL)
  {                 
    if(current->left == NULL)
    {
      printf(" %d ", current->data);
      current = current->next;      
    }    
    else
    {
      /* Find the inorder predecessor of current */
      pre = current->left;
      while(pre->next != NULL && pre->next != current)
        pre = pre->next;
 
      /* Make current as next child of its inorder predecessor */
      if(pre->next == NULL)
      {
        pre->next = current;
        current = current->left;
      }
             
      /* Revert the changes made in if part to restore the original 
        tree i.e., fix the next child of predecssor */   
      else 
      {
        pre->next = NULL;
        printf(" %d ",current->data);
        current = current->next;      
      } /* End of if condition pre->next == NULL */
    } /* End of if condition current->left == NULL*/
  } /* End of while */
}


Find a pair with given sum in a Balanced BST - tree should not be modified...
Expected time complexity is O(n) and only O(Logn) space

bool isPairPresent(node *root, int target)
{
    struct Stack* s1 = createStack(MAX_SIZE);
    struct Stack* s2 = createStack(MAX_SIZE);

    bool done1 = false, done2 = false;
    int val1 = 0, val2 = 0;
    node *curr1 = root, *curr2 = root;

    while (1)
    {
        while (done1 == false)
        {
            if (curr1 != NULL)
            {
                push(s1, curr1);
                curr1 = curr1->left;
            }
            else
            {
                if (isEmpty(s1))
                    done1 = 1;
                else
                {
                    curr1 = pop(s1);
                    val1 = curr1->val;
                    curr1 = curr1->next;
                    done1 = 1;
                }
            }
        }

        while (done2 == false)
        {
            if (curr2 != NULL)
            {
                push(s2, curr2);
                curr2 = curr2->next;
            }
            else
            {
                if (isEmpty(s2))
                    done2 = 1;
                else
                {
                    curr2 = pop(s2);
                    val2 = curr2->val;
                    curr2 = curr2->left;
                    done2 = 1;
                }
            }
        }
 
        if ((val1 + val2) == target)
        {
            printf("\n Pair Found: %d + %d = %d\n", val1, val2, target);
            return true;
        }
        else if ((val1 + val2) < target)
            done1 = false;
        else if ((val1 + val2) > target)
            done2 = false;
			
        if ((curr1==NULL && isEmpty(s1)) || ((curr2==NULL) && isEmpty(s2)))
            return false;
    }
}

void isPairPresent(node * root1,int target,node * root2)
{
    if(root1==NULL || root2 == NULL){
        return;
    }
    if(min+max<target)
	{
        isPairPresent(root1->left,target,root2);
        min = root1->val;
        if(min + max == target){
            printf("values = %d and  %d ", min,max);
            return;
        }
        isPairPresent(root1->next,target,root2);
    }
    else if(min+max>target)
	{
        isPairPresent(root1,target,root2->next);
        max = root2->val;
        if(min + max == target){
            printf("values = %d and  %d ", min,max);
            return;
        }
        isPairPresent(root1,target,root2->left);
    }
}

Find if there is a triplet in a Balanced BST that adds to zero
Expected time complexity is O(n^2) and only O(Logn) extra space can be used. You can modify given 
Binary Search Tree. Note that height of a Balanced BST is always O(Logn)

bool isTripletPresent(node *root)
{
    if (root == NULL)
       return false;
 
    node* head = NULL;
    node* tail = NULL;
    convertBSTtoDLL(root, &head, &tail);
 
    while ((head->next != tail) && (head->key < 0))
    {
        if (isPresentInDLL(head->next, tail, -1*head->key))
            return true;
        else
            head = head->next;
    }

    return false;
}

void convertBSTtoDLL(node* root, node** head, node** tail)
{
    if (root == NULL)
        return;

    if (root->left)
        convertBSTtoDLL(root->left, head, tail);

    root->left = *tail;

    if (*tail)
        (*tail)->next = root;
    else
        *head = root;

    *tail = root;

    if (root->next)
        convertBSTtoDLL(root->next, head, tail);
}

bool isPresentInDLL(node* head, node* tail, int sum)
{
    while (head != tail)
    {
        int curr = head->key + tail->key;
        if (curr == sum)
            return true;
        else if (curr > sum)
            tail = tail->left;
        else
            head = head->next;
    }
    return false;
}


Time Complexity:Time taken to convert BST to DLL is O(n) and time taken to find triplet in DLL is O(n^2)


 -------------------------------------------------------------------------------------
Convert a BST to a Binary Tree such that sum of all greater keys is added to every key
void addGreater(node *root)
{
    int sum = 0;
    addGreaterUtil(root, &sum);
}

void addGreaterUtil(node *root, int *sum_ptr)
{
    if (root == NULL)      5       18
        return;          2   13  20  13  
    addGreaterUtil(root->next, sum_ptr);

    *sum_ptr = *sum_ptr + root->key;
    root->key = *sum_ptr;

    addGreaterUtil(root->left, sum_ptr);
}

 
{1,2,3,4,5,6,7}
node* sortedArrayToBST(int arr[], int start, int end)
{
    if (start > end)
        return NULL;

    int mid = (start + end)/2;
    node *root = createNew(arr[mid]);

    root->left =  sortedArrayToBST(arr, start, mid-1);
    root->next = sortedArrayToBST(arr, mid+1, end);

    return root;
}

node* sortedListToBST(struct Lnode *head)
{
    int n = countLnodes(head);
    return sortedListToBSTRecur(&head, n);
}

node* sortedListToBSTRecur(struct Lnode **head_ref, int n)
{
    if (n <= 0)
        return NULL;

    node *left = sortedListToBSTRecur(head_ref, n/2);

    node *root = createNew((*head_ref)->data);
    root->left = left;

    *head_ref = (*head_ref)->next;
    root->next = sortedListToBSTRecur(head_ref, n-n/2-1);
 
    return root;
}


node* tree2DLL(node *root , node **head)
{
    node *temp = NULL;
    bool static flag = true;
    if(root == NULL)
    {
        return NULL;
    }
    else if(isLeaf(root))
    {
        return root;
    }
    else
    {
        temp = tree2DoubleLL(root->left,head);

        while(temp->next)
            temp = temp->next;

        temp->next = root;
        root->left = temp;

        if(flag)
        {
            *head = temp;
            flag = false;
        }

        temp = tree2DoubleLL(root->next,head);

        while(temp->left)
            temp = temp->left;

        temp->left = root;
        root->next = temp;
    }
    return root;
}

------------------------------------------------------------------
------------------------------------------------------------------
------------------------------------------------------------------
------------------------------------------------------------------
------------------------------------------------------------------
------------------------------------------------------------------
------------------------------------------------------------------


// 100 , 200 , 300 , 222 ,333

int size1(node *root)
{
	if(root == NULL)
		return 0;
	else
		return ( 1 + size1(root->left) + size1(root->next) );
}

int sizeItr(node *root)
{
   if(root == NULL)
     return 0;
   
   int count = 0;  
   queue < node * > q;
   q.push(root);
   
   while( ! q.empty() )
   {
      root = q.front(); 
      q.pop();
      count++;
      if(root->left)
         q.push(root->left);
      if(root->next)
         q.push(root->next);            
   }      
   return count;
}

int height(node *root)
{
	if(root == NULL)
		return 0;

	int lh = height(root->left);
	int rh = height(root->next);
	
	return ( (lh > rh) ? (lh+1):(rh+1));
}
int heightItr(node *root)
{
   if(root == NULL)
      return 0;
      
  int level = 0;
  queue <node *> q;
  q.push(root);
  q.push(NULL);
  
  while ( ! q.empty() )
  {
     root = q.front() ; q.pop();
     if(root)
     {
        if(root->left)
          q.push(root->left);
        if(root->next)
          q.push(root->next);                
     }
     else
     {
        level++;
        
        if (!q.empty())
           q.push(NULL); 
     }      
  }    
  return level;  
}
int min(node *root)
{
   if(root==NULL)
     return -1;
   if(root->left == NULL)
     return root->data;
    
   return min(root->left);        
}

int max(node *root)
{
   if(root == NULL)
      return -1;
   if(root->next == NULL)
      return root->data;
      
   return max(root->next);          
}

int maxItr(node *root)
{
   if(root == NULL)
     return -1;
     
   while(root->next)
     root = root->next;
     
   return root->data;        
}
 
int identical(node *a , node *b)
{
	if(a == NULL && b == NULL)
	{
		return 1;	
	}
	else if( a != NULL && b!= NULL)
	{
		return ( (a->data == b->data) &&
				identical(a->left,b->left) &&
				identical(a->next,b->next) );
	}
	else
	{
		return 0;
	}
}

bool identicalMirror(node *a , node *b)
{
    if(a==NULL && b==NULL)
    {
      return 1;
    }
    else if( a != NULL && b != NULL)
    {
        return ( (a->data==b->data) && identicalMirror(a->left,b->next)
                 && identicalMirror(a->next,b->left));
               
    }     
    else
    {
       return 0;    
    }
}

void mirrorCopy(node *root)
{
	if(root == NULL)
	{
		return ;
	}
	else
	{
		mirrorCopy(root->left);
		mirrorCopy(root->next);

		node *temp = root->left;
		root->left = root->next;
		root->next = temp;
	}
}
node* mirrorCopy(node *root)
{
	if(root == NULL)
	{
		return NULL;
	}
	else
	{
		node *temp = new node;
		temp->data = root->data;
		temp->left = mirrorCopy(root->next);	
		temp->next = mirrorCopy(root->left);
		
		return temp;
	}
}

int leafCount(node *root)
{
    static int count = 0;
    
    if(root)    
    {           
        leafCount(root->left);
        if(root->left==NULL && root->next==NULL)
           count++;
        leafCount(root->next);
   }
   return count;       
}

int leafCountItr(node *root)
{
   int count = 0; 
   if(root)
   {
      queue < node * > q;
      q.push(root);
      
      while( ! q.empty() )
      {
          root = q.front() ; q.pop();
          if(root->left==NULL && root->next==NULL)
            count++;
            
          if(root->left)
             q.push(root->left);
          if(root->next)
             q.push(root->next);            
      }       
   }
   return count;      
}
unsigned int getLeafCount(node* node)
{
  if(node == NULL)       
    return 0;
  if(root->left == NULL && root->next==NULL)      
    return 1;            
  else
    return getLeafCount(root->left)+
           getLeafCount(root->next);      
}


bool kthSmallest(node *root , int k, int *kth)
{
    static bool flag = 0;
    if(k <= 0)
    {
        return flag;
    }
      
    static int count = 0;
    
    if( !flag )
    {
       if(root)
       {
           kthSmallest(root->left , k , kth);               
           if(++count == k)
           {
               cout<<"kth node "<<endl;       
               flag = 1;           
               *kth = root->data;
           }            
           kthSmallest(root->next , k , kth);
       }   
    }
    return flag;  
}

int kthSmallestItr(node *root , int k)
{
    if(root == NULL || k <= 0 )
       return 0;
   
    bool done = 0;
    int count = 0;
    stack < node *> s;
    
    while ( !done)
    {
         while(root)
         {
            s.push(root);
            root = root->left;           
         }      
         
         if( !s.empty())
         {
              root = s.top() ; s.pop();
                           
              if(++count == k)
                  return root->data;                       
              root = root->next;   
         }
         else
         {
            done = 1;    
         }       
    }
    cout<<endl;  
    return -1;          
}
 
void  DFS(node *root)
{
   if(root == NULL)
     return ;
     
   cout<<root->data<<" ";  
   DFS(root->left);
   DFS(root->next);        
}

void  levelOrder1(node *root)
{
    if(root==NULL)
       return ;
       
    queue<node *> q;
    
    q.push(root);
    q.push(NULL);
    
    while( !q.empty())
    {
        root = q.front() ; q.pop();
        
        if(root)
        {
           cout<<root->data<<" ";        
           if(root->left)
              q.push(root->left);
           if(root->next)
              q.push(root->next);   
        }       
        else
        {
            cout<<endl;
            if( ! q.empty() )
              q.push(NULL);
        }
    }         
}

void printKDist1(node *root,int k)
{
       if(root == NULL || k <= 0)
         return ;
         
       if(k == 1)
         cout<<root->data<<" ";
      
      printKDist1(root->left, k-1);   
      printKDist1(root->next, k-1);             
}

void printKDist2(node *root,int k)
{
       if(root == NULL || k <= 0)
         return ;
         
       if(k == 1)
         cout<<root->data<<" ";
         
      printKDist2(root->next, k-1); 
      printKDist2(root->left, k-1);
        
}

void  levelOrder2(node *root)
{
   if(root == NULL)
     return ;
     
   int h = height(root);
   
   for(int i = 1; i <= h ; i++)
   {
      printKDist1(root,i);        
      cout<<endl;
   }
}

void  levelOrderRev1(node *root)
{
    if(root == NULL)
      return ;
      
    queue<node *> q;
    stack<node *> s;
    
    q.push(root);
    q.push(NULL);
    
    while(!q.empty())
    {
       root = q.front() ; q.pop();
       s.push(root);
       if(root)
       {
         if(root->left)
            q.push(root->left);
          
         if(root->next)
            q.push(root->next);                    
       }
       else
       {
          if(!q.empty())
             q.push(NULL);    
       }
    }        
    while(!s.empty())
    {
       root = s.top(); s.pop();
       if(root)
       {
           cout<<root->data<<" ";                 
       }
       else
       {
           cout<<endl;
       }
       
    }
    cout<<endl;
    
}
void  levelOrderRev2(node *root)
{
   if(root == NULL)
     return ;
     
   int h = height(root);
   
   for(int i = h; i >=1  ; i--)
   {
      printKDist2(root,i);        
      cout<<endl;
   }
}

void levelOrder(node *root)
{
	if(root == NULL)
	{
		return ;
	}
	node *queue[20] ={NULL};
	int front = 0, back = 0;

	while(root)
	{
		cout<<root->data<<" ";
		
		if(root->left)
			queue[back++] = root->left;

		if(root->next)
			queue[back++] = root->next;

		root = queue[front++];
	}
}

void levelOrderRev(node *root) // O(n)
{
	if(root == NULL)
	{
		return ;
	}
	node *queue[20] ={NULL};
	int front = 0, back = 0;
	int top = 0 , arr[20] ={0};

	while(root)
	{
		//cout<<root->data<<" ";
		arr[top++] = root->data;
		
		if(root->next)
			queue[back++] = root->next;
		
		if(root->left)
			queue[back++] = root->left;

		root = queue[front++];
	}
	while(top)
	{
		cout<<arr[--top]<<" ";
	}	
	cout<<endl;
}

void printSpiral(node* root)
{
    int h = height(root);

    bool ltr = false;
    for(int i=1; i<=h; i++)
    {
        printGivenLevel(root, i, ltr);
        ltr = !ltr;
    }
}
      1
	2   3
   4  5 6 7	
void printGivenLevel(node* root, int level, int ltr)
{
    if(root == NULL)
        return;
    if(level == 1)
        printf("%d ", root->data);
    else if (level > 1)
    {
        if(ltr)
        {
            printGivenLevel(root->left, level-1, ltr);
            printGivenLevel(root->next, level-1, ltr);
        }
        else
        {
            printGivenLevel(root->next, level-1, ltr);
            printGivenLevel(root->left, level-1, ltr);
        }
    }
}
void printSpiral(node *root)
{
    if (root == NULL)  
	    return;  

    stack<node *> s1;  
    stack<node *> s2; 

    s1.push(root);

    while (!s1.empty() || !s2.empty())
    {
        while (!s1.empty())
        {
            node *temp = s1.top();
            s1.pop();
            cout << temp->data << " ";

            if (temp->next)
                s2.push(temp->next);
            if (temp->left)
                s2.push(temp->left);
        }
        while (!s2.empty())
        {
            node *temp = s2.top();
            s2.pop();
            cout << temp->data << " ";

            if (temp->left)
                s1.push(temp->left);
            if (temp->next)
                s1.push(temp->next);
        }
    }
}

bool searchnode(node *root , int val)
{
  if(root==NULL)
    return 0;
    
  node *cur = root;
  
  while(cur)
  {
    if(cur->data == val)
         return 1;
    cur = cur->data > val ? cur->left : cur->next;               
  }   
  return 0;    
}
int levelOfTree(node *root , int val)
{
    if(root == NULL)
      return 0;
      
    int level = 0;
    node *cur = root;
    
    while(cur)
    {
      level++;
      if(cur->data == val)
         return level;
         
      cur = cur->data > val ? cur->left : cur->next;                     
    } 
    return 0;         
}

void doubleTree(node *root)
{
   if(root==NULL)
     return ;
     
   doubleTree(root->left);
   doubleTree(root->next);
   
   node* temp = root->left;
   root->left = createNew(root->data);
   root->left->left = temp;
}

bool printCloseAncestor(node *root, int val)
{
	if(root == NULL)
	{
		return false;
	}		

	if(root->data == val)
	{
		return true;
	}

	if( printCloseAncestor(root->left,val) ||
			printCloseAncestor(root->next,val) )
	{
		cout<<root->data<<" ";
		return true;
	}
	return false;
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

void printnodesInRange(node *root , int k1 , int k2)
{
	if( root == NULL)
		return ;

	if(k1 < root->data)
	{
		printnodesInRange(root->left,k1,k2);
	}	

	if( k1 <= root->data && k2 >= root->data)
	{
		cout<<root->data<<" ";
	}

	if(k2 > root->data)
	{
		printnodesInRange(root->next,k1,k2);
	}
}

int getWidth(node *root , int k)
{
	if(root == NULL)
		return 0;

	if( k == 1)
		return 1;
	else if(k > 1)
		return getWidth(root->left,k-1) + getWidth(root->next,k-1);	
}
 

int getMaxWidth(node *root)
{
	if(root == NULL)
		return 0;

	int h = height(root);

	int width = 0 , max = 0;

	for(int i = 1 ; i <= h ; i++)
	{
		width = getWidth(root,i);
		if(width > max)
		{
			max = width;
		}
	}
	return max;
}

int getMaxWidth(node* root)
{
  int width , level = 0;
  int h = height(root);

  int *count = new int[h]; 
 
  getMaxWidthRecur(root, count, level);
 
  return getMax(count, h);
}

void getMaxWidthRecur(node *root, int count[], int level)
{
  if(root)
  {
    count[level]++;
    getMaxWidthRecur(root->left, count, level+1);
    getMaxWidthRecur(root->next, count, level+1);
  }
}

int sum(node *root)
{
	if(root == NULL)
		return 0;
	else
		return ( sum(root->left) + root->data + sum(root->next) );
}

int sumTree(node *root) O(n^2)
{
	if((root == NULL) ||( root->left == NULL && root->next == NULL))
		return 1;

	int ls = sum(root->left);
	int rs = sum(root->next);

	if( (root->data == ls + rs) && sumTree(root->left)
               && sumTree(root->next) );
	{
		return 1;
	}
	return 0;
}


int isLeaf(node *node)
{
    if(node == NULL)
        return 0;
    if(root->left == NULL && root->next == NULL)
        return 1;
    return 0;
}
int isSumTree(node* root) O(n)
{
    int ls = 0 ,rs = 0; 

    if(root == NULL || isLeaf(root))
        return 1;
 
    if( isSumTree(root->left) && isSumTree(root->next))
    {
        if(root->left == NULL)
            ls = 0;
        else if(isLeaf(root->left))
            ls = root->left->data;
        else
            ls = 2*(root->left->data);
 
        if(root->next == NULL)
            rs = 0;
        else if(isLeaf(root->next))
            rs = root->next->data;
        else
            rs = 2*(root->next->data);
 
        return(root->data == ls + rs);
    }
     return 0;
}

 
int inorderSuccessor(node *root, node *find)
{
	if(root == NULL)
		return 0;

	if(find->next != NULL)
	{
		return min(find->next);
	}	

	node *p = find->parent;

	while( p && p->next == find)
	{
		find = p;
		p = p->parent;
	}
	if(p)
		return p->data;
	else
		return 0;	
}
node * inOrderSuccessor(node *root, node *n)
{
    if(root==NULL || n == NULL)
	    return NULL;
    // step 1 of the above algorithm
    if( n->next != NULL )
        return minValue(n->next);
 
    node *succ = NULL;
 
    // Start from root and search for successor down the tree
    while (root != NULL)
    {
        if (n->data < root->data)
        {
            succ = root;
            root = root->left;
        }
        else if (n->data > root->data)
            root = root->next;
        else
           break;
    }
 
    return succ;
}

int maxDepth(node* root)
{
	if (root == NULL) return 0;
	else
	{
		int ldepth = maxDepth(root->left) + 1;
		int rdepth = maxDepth(root->next) + 1;

		return ((ldepth>rdepth) ? ldepth:rdepth);
	}
}

int minDepth(node* root)
{
	if (root == NULL) return 0;
	else
	{
		int ldepth = minDepth(root->left) + 1;
		int rdepth = minDepth(root->next) + 1;

		return ((ldepth>rdepth) ? rdepth:ldepth);
	}
}
 
bool isDiffMoreThanTwo(node* root)
{
	int ret = maxDepth(root) - minDepth(root);
	cout<<"ret - "<<ret<<endl;
	return (ret >=2 );
}
 
void show(node *root)
{
	while(root)
	{
		cout<<root->data<<"  ";
		root = root->left;	
	}
}
node* convertToDLL(node* root)
{
	if(root == NULL) 
		return NULL;
	
	stack<node*> s1, s2;
	s1.push(root);
	
	node* pre = root;
	int level = 0;
	
	while(!s1.empty())
	{
		node* temp = s1.top();
		s1.pop();
		
		if(level % 2 )
		{
			if(temp->left) s2.push(temp->left);
			if(temp->next) s2.push(temp->next);
		}
		else
		{
			if(temp->next) s2.push(temp->next);
			if(temp->left) s2.push(temp->left);
		}

		pre->next = temp;
		temp->left = pre;
		pre = temp;

		if(s1.empty())
		{
			swap(s1,s2);
			level++;
		}
	}
	pre->next = NULL;
	root->left = NULL;

	return root;
}

node* buildTree(char in[], char pre[], int start, int end)
{
	static int preIndex = 0;

	if(start > end)
		return NULL;

	node *temp = createNew(pre[preIndex++]);

	if(start == end)
		return temp;

	int inIndex = search(in, start, end, temp->data);

	temp->left = buildTree(in, pre, start, inIndex-1);
	temp->next = buildTree(in, pre, inIndex+1, end);

	return temp;
}
 
int search(char arr[], int start, int end, char value)
{
	for(int i = start; i <= end; i++)
	{
		if(arr[i] == value)
			return i;
	}
}

void DeleteTree(node* root)
{
	stack<node*> st;
	st.push(root);
	node* temp;
	
	while( ! st.empty())
	{
		temp = st.top();
		st.pop();
		if ( temp->left )
			st.push(temp->left);
		if ( temp->next )
			st.push(temp->next);
		delete temp;
	}
}

void deleteTree(TREE* head)
{
	if(head==NULL)
		return ;
	
	deleteTree(head->left);
	deleteTree(head->next);
	
	free(head);
}

void findCommon(node* r1, node* r2) 
{
  if (r1 == NULL || r2 == NULL) return;
  if (r1->data == r2->data) {
    cout << r1->data << "\n";
    findCommon(r1->left, r2->left);
    findCommon(r1->next, r2->next);
  }
  else if (r1->data < r2->data)
    findCommon(r1, r2->left);
  else 
    findCommon(r1->left, r2);
}

void findCommon2(node* a, node* b) {
	if(!a || !b)
		return;
	stack<node*> p,q;
	node* n1 = a, *n2 = b;
	while(true)
	{
		if(n1)
		{
			p.push(n1);
			n1 = n1->left;
		}
		else if(n2)
		{
			q.push(n2);
			n2 = n2->left;
		}
		else if (!p.empty() && !q.empty())
		{
			n1 = p.top(); n2 = q.top();			
			if(n1->data < n2->data)
			{
				p.pop();
				n1 = n1->next;
				n2 = NULL;
			}
			else if(n2->data < n1->data)
			{
				q.pop();
				n2 = n2->next;
				n1 = NULL;
			}
			else
			{
				cout<<n1->data<<" ";
				p.pop();  q.pop();
				n1 = n1->next;
				n2 = n2->next;
			}
		}
		else
			break;
	}
}


