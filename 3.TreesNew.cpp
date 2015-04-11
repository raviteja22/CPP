01. leavesAtSameLevel  1  
02. leftView 2
03. prune 3
04. depthOfOddLeaf 4
04. diffBetEvenAndOddNode 5
06. BTToDLL  6
16. extractLeafList 7 
08. isIsomorphic  8
14. removeOutsideRange 9

13. convertList2Binary 10
07. printAncestors 11
12. Ceil 12
11. constructTree 13


05. printPostOrder
10. isSameBSTUtil
15. getMatchingPrefix
09. printAllInterpretations


[Q].Construct Complete Binary Tree from its Linked List Representation
10 12 15 25 30 36 

      10 
   12   15
 25 30 36 

 void convertList2Binary(Listnode *head, BinaryTreenode* &root)
{
    queue<BinaryTreenode *> q;
 
    if (head == NULL)
    {
        root = NULL; 
        return;
    }
 
    root = newBinaryTreenode(head->data);
    q.push(root);
 
    head = head->next;
 
    while (head)
    {
        BinaryTreenode* parent = q.front();
        q.pop();

        BinaryTreenode *leftChild = NULL, *rightChild = NULL;
        leftChild = newBinaryTreenode(head->data);
        q.push(leftChild);
        head = head->next;
        if (head)
        {
            rightChild = newBinaryTreenode(head->data);
            q.push(rightChild);
            head = head->next;
        }
 
        parent->left = leftChild;
        parent->right = rightChild;
    }
}

[Q].Print ancestors of a given binary tree node without recursion
bool printAncestors(node *root, int target)
{
  if (root == NULL)
     return false;
 
  if (root->data == target)
     return true;
 
  if ( printAncestors(root->left, target) ||
       printAncestors(root->right, target) )
  {
    cout << root->data << " ";
    return true;
  }
  return false;
}
void printAncestors(node *root, int key)
{
    if (root == NULL) return;
 
    struct Stack* stack = createStack(MAX_SIZE);
 
    while (1)
    {
        while (root && root->data != key)
        {
            push(stack, root);   
            root = root->left; 
        }
 
        if (root && root->data == key)
            break;
 
        if (peek(stack)->right == NULL)
        {
		   // If the popped node is right child of top, then remove the top
           // as well. Left child of the top must have processed before.
            root = pop(stack);
 
            while (!isEmpty(stack) && peek(stack)->right == root)
               root = pop(stack);
        }
        root = isEmpty(stack)? NULL: peek(stack)->right;
    } 
    while (!isEmpty(stack))
        cout<<pop(stack)->data<<endl;
}



[Q]. Floor and Ceil from a BST
int Ceil(node *root, int input)
{
    if( root == NULL )
        return -1;
 
    if( root->key == input )
        return root->key;
 
    if( root->key < input )
        return Ceil(root->right, input);
 
    int ceil = Ceil(root->left, input);
    return (ceil >= input) ? ceil : root->key;
}
1. Modify above code to find floor value of input key in a binary search tree.

2. Write neat algorithm to find floor and ceil values in a sorted array. Ensure to handle all possible boundary conditions.


[Q]. Construct BST from given preorder traversal 
The first element of preorder traversal is always root. We first construct the root. 
Then we find the index of first element which is greater than root. Let the index be ‘i’.
The values between root and ‘i’ will be part of left subtree, and the values between 
‘i+1′ and ‘n-1′ will be part of right subtree. Divide given pre[] at index “i” and 
recur for left and right sub-trees.
 
For example in {10, 5, 1, 7, 40, 50}, 10 is the first element, so we make it root. Now we look for the first element greater than 10, we find 40. So we know the structure of BST is as following.
{10, 5, 1, 7, 40, 50}
     10
   /   \
  5     40
 /  \      \
1    7      50

node *constructTree (int pre[], int size) //  O(n^2)
{
    int preIndex = 0;
    return constructTreeUtil (pre, &preIndex, 0, size - 1, size);
}

node* constructTreeUtil (int pre[], int* preIndex,
                                int low, int high, int size)
{

    if (*preIndex >= size || low > high)
        return NULL;
 
    node* root = newnode ( pre[*preIndex] );
    *preIndex = *preIndex + 1;
 
    if (low == high)
        return root;


    for ( int i = low; i <= high; ++i )
        if ( pre[ i ] > root->data ) // left to i and right to i
            break;
 
    root->left = constructTreeUtil ( pre, preIndex, *preIndex, i - 1, size );
    root->right = constructTreeUtil ( pre, preIndex, i, high, size );
 
    return root;
}
 
Method 2 ( O(n) time complexity )
The idea used here is inspired from method 3 of this post. The trick is to set a range 
{min .. max} for every node. Initialize the range as {INT_MIN .. INT_MAX}. The 
first node will definitely be in range, so create root node. To construct the left 
subtree, set the range as {INT_MIN …root->data}. If a values is in the range 
{INT_MIN .. root->data}, the values is part part of left subtree. To construct 
the right subtree, set the range as {root->data..max .. INT_MAX}.
 
node *constructTree (int pre[], int size) // O(n)
{
    int preIndex = 0;
    return constructTreeUtil ( pre, &preIndex, pre[0], INT_MIN, INT_MAX, size );
}

node* constructTreeUtil( int pre[], int* preIndex, int key,
                                int min, int max, int size ) //  O(n^2)
{
    if( *preIndex >= size )
        return NULL;
  
    node* root = NULL;
  
    if( key > min && key < max )
    {
        root = newnode ( key );
        *preIndex = *preIndex + 1;
         
        if (*preIndex < size)
        {
            root->left = constructTreeUtil( pre, preIndex, pre[*preIndex],
                                        min, key, size );
            root->right = constructTreeUtil( pre, preIndex, pre[*preIndex],
                                         key, max, size );
        }
    }
  
    return root;
} 
Given preorder traversal of a binary search tree, construct the BST.

For example, if the given traversal is {10, 5, 1, 7, 40, 50}, then the output should be root of following tree.

     10
   /   \
  5     40
 /  \      \
1    7      50  
We have discussed O(n^2) and O(n) recursive solutions in the previous post. Following is a stack based iterative solution that works in O(n) time.

1. Create an empty stack.

2. Make the first value as root. Push it to the stack.

3. Keep on popping while the stack is not empty and the next value is greater than stack’s top value. Make this value as the right child of the last popped node. Push the new node to the stack.

4. If the next value is less than the stack’s top value, make this value as the left child of the stack’s top node. Push the new node to the stack.

5. Repeat steps 2 and 3 until there are items remaining in pre[].


node* constructTree ( int pre[], int size )
{
    stack<node > s;
    node* root = newnode( pre[0] ) , temp = NULL;
    s.push(root);

    for (int i = 1; i < size; ++i ) // {10, 5, 1, 7, 40, 50}
    {
        temp = NULL;
 
        while ( !s.empty() && pre[i] > s.top()->data )
            temp = s.pop();
 
        if ( temp != NULL)
        {
            temp->right = newnode( pre[i] );
            s.push(temp->right);
        }
        else
        {
            s.top()->left = newnode( pre[i] );
            s.push( s.top()->left );
        }
    } 
    return root;
}

Construct Special Binary Tree from given Inorder traversal
{5, 10, 40, 30, 28}
        40
       /   \
      10     30
     /         \
    5          28 
struct node* buildTree (int inorder[], int start, int end) // O(n^2)
{
    if (start > end)
        return NULL;
 
    int i = max (inorder, start, end);
 
    struct node *root = newNode(inorder[i]);
 
    if (start == end)
        return root;
 
    root->left  = buildTree (inorder, start, i-1);
    root->right = buildTree (inorder, i+1, end);
 
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

------------------------------------------------------------------------------


Check if all leaves are at same level //  O(n).
1. bool leavesAtSameLevel(node *root) //  O(n).
{
   int level = 0;
   return checkUtil(root, level);
}
1. bool checkUtil(node *root, int level, int *leafLevel)
{

    if (root == NULL)  
	    return true;
 
    if ( isLeaf(root) )
    {
        if (*leafLevel == 0)
        {
            *leafLevel = level; 
            return true;
        }
        return (level == *leafLevel);
    }

    return checkUtil(root->left, level+1, leafLevel) &&
           checkUtil(root->right, level+1, leafLevel);
}

int checkUtil(node *root, int level)
{

    if (root == NULL)  
		return 1;
 

    if ( isLeaf(root) )
        return (level+1);
 
    return checkUtil(root->left, level+1) == checkUtil(root->right, level+1);
}

2. Print Left View of a Binary Tree // 12 10 25
		 12
       /     \
     10       30
            /    \
          25      40 
void leftView(node *root)
{
    int maxLevel = 0;
    leftViewUtil(root, 1, &maxLevel);
}
void leftViewUtil(node *root, int level, int *maxLevel)
{
    if (root==NULL)  
	    return;
 
    if (*maxLevel < level)
    {
        cout<<root->data<<endl;
        *maxLevel = level;
    }

    leftViewUtil(root->left, level+1, maxLevel);
    leftViewUtil(root->right, level+1, maxLevel);
}

3. Remove all nodes which don’t lie in any path with sum>= k

Consider the following Binary Tree
          1 
      /      \
     2        3
   /   \     /  \
  4     5   6    7
 / \    /       /
8   9  12      10
   / \           \
  13  14         11
      / 
     15 

For input k = 20, the tree should be changed to following
(nodes with values 6 and 8 are deleted)
          1 
      /      \
     2        3
   /   \        \
  4     5        7
   \    /       /
    9  12      10
   / \           \
  13  14         11
      / 
     15 

For input k = 45, the tree should be changed to following.
      1 
    / 
   2   
  / 
 4  
  \   
   9    
    \   
     14 
     /
    15 
	
node *prune(node *root, int k)
{
    int sum = 0;
    return pruneUtil(root, k, &sum);
}
node *pruneUtil(node *root, int k, int *sum)
{
    if (root == NULL)  
		return NULL;
 
    int lsum = *sum + (root->data);
    int rsum = lsum;
 
    root->left = pruneUtil(root->left, k, &lsum);
    root->right = pruneUtil(root->right, k, &rsum);
 
    *sum = max(lsum, rsum);
 
    if (*sum < k)
    {
        delete root;
        root = NULL;
    } 
    return root;
}
	
[Q]. Find depth of the deepest odd level leaf node
	   1     // 9 depth 5
     /   \
    2     3
  /      /  \  
 4      5    6
        \     \
         7     8
        /       \
       9         10
                 /
                11
				

int depthOfOddLeaf(node *root)
{
    int level = 1;
    return depthOfOddLeafUtil(root, level);
}
int depthOfOddLeafUtil(node *root,int level)
{
    if (root == NULL)
        return 0;
 
    if (isLeaf(root) && level&1)
        return level;
 
    return max(depthOfOddLeafUtil(root->left, level+1),
               depthOfOddLeafUtil(root->right, level+1));
}
				

[Q].Difference between sums of odd level and even level nodes of a Binary Tree
	  5
    /   \
   2     6
 /  \     \  
1    4     8
    /     / \ 
   3     7   9  
(5 + 1 + 4 + 8) which is 18  
(2 + 6 + 3 + 7 + 9) which is 27. 
18 – 27 which is -9.

int getLevelDiff(node *root) // O(n),
{
   if (root == NULL)
         return 0;
 
   return root->data - getLevelDiff(root->left) - getLevelDiff(root->right);
}   

int getLevelDiff(node *root)
{
    if (root == NULL)
        return 0;
    int rear, front;
    node **queue = createQueue(&front, &rear);
    node *temp = root;

    int level = 1, oddLevel_sum, evenLevel_sum;
    oddLevel_sum = evenLevel_sum = 0;

    enQueue(queue, &rear, root);
    enQueue(queue, &rear, NULL);

    while (rear != front)
    {
        temp = deQueue(queue, &front);

        if (temp == NULL)
        {
            level++;

            if (rear != front)
                enQueue(queue, &rear, NULL);
        }
        else 
        {
            if (level & 1)
                oddLevel_sum += temp->data;
            else
                evenLevel_sum += temp->data;
            if (temp->left)
                enQueue(queue, &rear, temp->left);
            if (temp->right)
                enQueue(queue, &rear, temp->right);
        }
    }
    return (oddLevel_sum - evenLevel_sum);
}

[Q].Print Postorder traversal from given Inorder and Preorder traversals
Inorder traversal in[] = {4, 2, 5, 1, 3, 6}
Preorder traversal pre[] = {1, 2, 4, 5, 3, 6}
Postorder traversal is {4, 5, 2, 6, 3, 1}
        1
      /     \   
     2       3
   /   \      \
  4     5      6
  
A naive method is to first construct the tree, then use simple recursive method 
to print postorder traversal of the constructed tree.

void printPostOrder(int in[], int pre[], int n)
{
   int root = search(in, pre[0], n);
 
   if (root != 0)
      printPostOrder(in, pre+1, root);
 
   if (root != n-1)
      printPostOrder(in+root+1, pre+root+1, n-root-1);
 
   cout << pre[0] << " ";
}
int search(int arr[], int x, int n)
{
    for (int i = 0; i < n; i++)
      if (arr[i] == x)
         return i;
    return -1;
}
  
[Q].Convert a given Binary Tree to Doubly Linked List
Given a Binary Tree (BT), convert it to a Doubly Linked List(DLL). The left and right 
pointers in nodes are to be used as previous and next pointers respectively in converted 
DLL. The order of nodes in DLL must be same as Inorder of the given Binary Tree. 
The first node of Inorder traversal (left most node in BT) must be head node of the DLL.

     10
   12   15
 25 30 36

25 12 30 10 36 15
 
node *BTToDLL(node *root)
{
    fixPrevPtr(root);
    return fixNextPtr(root);
}
void fixPrevPtr(node *root)
{
    static node *pre = NULL;
 
    if (root != NULL)
    {
        fixPrevPtr(root->left);
        root->left = pre;
        pre = root;
        fixPrevPtr(root->right);
    }
}
// Since left pointers are changed to point to previous node in DLL, we can 
// linearly traverse the complete DLL using these pointers. The traversal 
// would be from last to first node. 

node *fixNextPtr(node *root)
{
    node *prev = NULL;
 
    while (root && root->right != NULL)
        root = root->right;

    while (root && root->left != NULL)
    {
        prev = root;
        root = root->left;
        root->right = prev;
    }
 
    return (root);
}


[Q].Tree Isomorphism Problem
bool isIsomorphic(node* n1, node *n2)
{
 if (n1 == NULL && n2 == NULL)
    return true;
 
 if (n1 == NULL || n2 == NULL)
    return false;
 
 if (n1->data != n2->data)
    return false;
 
 return
 (isIsomorphic(n1->left,n2->left) && isIsomorphic(n1->right,n2->right))||
 (isIsomorphic(n1->left,n2->right) && isIsomorphic(n1->right,n2->left));
}
 
[Q].Find all possible interpretations of an array of digits
Input: {1, 1} Output: ("aa", 'k") 
Input: {1, 2, 1} Output: ("aba", "au", "la") 
Input: {9, 1, 8} Output: {"iah", "ir"}

private static final String[] alphabet = {"", "a", "b", "c", "d", "e",
        "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r",
        "s", "t", "u", "v", "w", "x", "v", "z"};
		
class node {
 
    String dataString;
    node left;
    node right;
 
    node(String dataString) {
        this.dataString = dataString;
        //Be default left and right child are null. 
    }
 
    public String getDataString() {
        return dataString;
    }
}
// The main function that prints all interpretations of array
static void printAllInterpretations(int[] arr) 
{
 
        // Step 1: Create Tree
        node root = createTree(0, "", arr);
 
        // Step 2: Print Leaf nodes
        printleaf(root);
 
        System.out.println();  // Print new line
}
	
public class arrayToAllInterpretations 
{
    public static node createTree(int data, String pString, int[] arr) 
	{
         if (data > 26) 
            return null;
 
        String dataToStr = pString + alphabet[data];
 
        node root = new node(dataToStr);
 
        if (arr.length != 0) 
		{
            data = arr[0];

            int newArr[] = Arrays.copyOfRange(arr, 1, arr.length);
 
            root.left = createTree(data, dataToStr, newArr);
 
            if (arr.length > 1) 
			{
 
                data = arr[0] * 10 + arr[1];
 
                newArr = Arrays.copyOfRange(arr, 2, arr.length);
 
                root.right = createTree(data, dataToStr, newArr);
            }
        }
        return root;
    }
 
public static void printleaf(node root) 
{
        if (root == null) 
            return;
 
        if (root.left == null && root.right == null) 
            System.out.print(root.getDataString() + "  ");
         
        printleaf(root.left);
        printleaf(root.right);
}
 


[Q].Check for Identical BSTs without building the trees
/* The main function that checks if two arrays a[] and b[] of size n construct
  same BST. The two values 'min' and 'max' decide whether the call is made for
  left subtree or right subtree of a parent element. The indexes i1 and i2 are
  the indexes in (a[] and b[]) after which we search the left or right child.
  Initially, the call is made for INT_MIN and INT_MAX as 'min' and 'max'
  respectively, because root has no parent.
  i1 and i2 are just after the indexes of the parent element in a[] and b[]. */
bool isSameBSTUtil(int a[], int b[], int n, int i1, int i2, int min, int max)
{
   int j, k;
 
   /* Search for a value satisfying the constraints of min and max in a[] and 
      b[]. If the parent element is a leaf node then there must be some 
      elements in a[] and b[] satisfying constraint. */
   for (j=i1; j<n; j++)
       if (a[j]>min && a[j]<max)
           break;
   for (k=i2; k<n; k++)
       if (b[k]>min && b[k]<max)
           break;
 
   /* If the parent element is leaf in both arrays */
   if (j==n && k==n)
       return true;
 
   /* Return false if any of the following is true
      a) If the parent element is leaf in one array, but non-leaf in other.
      b) The elements satisfying constraints are not same. We either search
         for left child or right child of the parent element (decinded by min
         and max values). The child found must be same in both arrays */
   if (((j==n)^(k==n)) || a[j]!=b[k])
       return false;
 
   /* Make the current child as parent and recursively check for left and right
      subtrees of it. Note that we can also pass a[k] in place of a[j] as they
      are both are same */
   return isSameBSTUtil(a, b, n, j+1, k+1, a[j], max) &&  // Right Subtree
          isSameBSTUtil(a, b, n, j+1, k+1, min, a[j]);    // Left Subtree
}







 
[Q].Remove BST keys outside the given range
        6                 6
   -13     14         -8     13  
     -8  13  15             7 
         7	 
  
node* removeOutsideRange(node *root, int min, int max)
{
   if (root == NULL)
      return NULL;
 
   root->left =  removeOutsideRange(root->left, min, max);
   root->right =  removeOutsideRange(root->right, min, max);
 

   if (root->key < min)
   {
       node *rChild = root->right;
       delete root;
       return rChild;
   }

   if (root->key > max)
   {
       node *lChild = root->left;
       delete root;
       return lChild;
   }

   return root;
}  

Longest prefix matching
Let the dictionary contains the following words:
{are, area, base, cat, cater, children, basement}
caterer                 cater
basemexy                base
child                   < Empty >

We build a Trie of all dictionary words. Once the Trie is built, traverse through 
it using characters of input string. If prefix matches a dictionary word, store 
current length and look for a longer match. Finally, return the longest match.

class Trienode 
{           
    public Trienode(char ch)  
	{
        value = ch;
        children = new HashMap<>();
        bIsEnd = false;
    }    
    public HashMap<Character,Trienode> getChildren() {   return children;  }    
    public char getValue()                           {   return value;     }    
    public void setIsEnd(boolean val)                {   bIsEnd = val;     }    
    public boolean isEnd()                           {   return bIsEnd;    }
       
    private char value;    
    private HashMap<Character,Trienode> children;
    private boolean bIsEnd;  
}
   

class Trie 
{        
    // Constructor
    public Trie()
	{     
		root = new Trienode((char)0);  
	}    
   
    public void insert(String word)  
	{
        int length = word.length();        
        Trienode crawl = root;
           
        for( int level = 0; level < length; level++)
        {
            HashMap<Character,Trienode> child = crawl.getChildren();            
            char ch = word.charAt(level);
               
            if( child.containsKey(ch))
                crawl = child.get(ch);
            else   
            {              
                Trienode temp = new Trienode(ch);
                child.put( ch, temp );
                crawl = temp;
            }
        }
        crawl.setIsEnd(true);
    }
       
public String getMatchingPrefix(String input)  
{
        String result = ""; // Initialize resultant string
        int length = input.length();  // Find length of the input string       
           
        // Initialize reference to traverse through Trie
        Trienode crawl = root;   
          
        // Iterate through all characters of input string 'str' and traverse 
        // down the Trie
        int level, prevMatch = 0; 
        for( level = 0 ; level < length; level++ )
        {    
            // Find current character of str
            char ch = input.charAt(level);    
              
            // HashMap of current Trie node to traverse down
            HashMap<Character,Trienode> child = crawl.getChildren();                        
             
            if( child.containsKey(ch) )
            {
               result += ch;          
               crawl = child.get(ch); 
                 
               if( crawl.isEnd() ) 
                    prevMatch = level + 1;
            }            
            else  break;
        }
          
        if( !crawl.isEnd() )
                return result.substring(0, prevMatch);        
         
        else return result;
    }
       
    private Trienode root;      
}
  

  Extract Leaves of a Binary Tree in a Doubly Linked List
http://www.geeksforgeeks.org/connect-leaves-doubly-linked-list/
        1
     /     \
    2       3
   / \       \
  4   5       6
 / \         / \
7   8       9   10
Output:
Doubly Linked List
7<->8<->5<->9<->10

Modified Tree:
        1
     /     \
    2       3
   /         \
  4           6
  
root = extractLeafList(root, &head);
printList(head);  

node* extractLeafList(node *root, node **head_ref)
{
   if (root == NULL)  
       return NULL;
 
   if ( isLeaf(root) )
   {
       root->right = *head_ref;
       if (*head_ref != NULL) 
	         (*head_ref)->left = root;
       *head_ref = root;
 
       return NULL;  
   }

   root->right = extractLeafList(root->right, head_ref);
   root->left  = extractLeafList(root->left, head_ref);
 
   return root;
}

Check if each internal node of a BST has exactly one child
August 5, 2012
Given Preorder traversal of a BST, check if each non-leaf node has only one child. Assume that the BST contains unique entries.

Examples

Input: pre[] = {20, 10, 11, 13, 12}
Output: Yes
The give array represents following BST. In the following BST, every internal
node has exactly 1 child. Therefor, the output is true.
        20
       /
      10
       \
        11
          \
           13
           /
         12
In Preorder traversal, descendants (or Preorder successors) of every node appear after the node. In the above example, 20 is the first node in preorder and all descendants of 20 appear after it. All descendants of 20 are smaller than it. For 10, all descendants are greater than it. In general, we can say, if all internal nodes have only one child in a BST, then all the descendants of every node are either smaller or larger than the node. The reason is simple, since the tree is BST and every node has only one child, all descendants of a node will either be on left side or right side, means all descendants will either be smaller or greater.

Approach 1 (Naive) 
This approach simply follows the above idea that all values on right side are either smaller or larger. Use two loops, the outer loop picks an element one by one, starting from the leftmost element. The inner loop checks if all elements on the right side of the picked element are either smaller or greater. The time complexity of this method will be O(n^2).

Approach 2
Since all the descendants of a node must either be larger or smaller than the node. We can do following for every node in a loop.
1. Find the next preorder successor (or descendant) of the node.
2. Find the last preorder successor (last element in pre[]) of the node.
3. If both successors are less than the current node, or both successors are greater than the current node, then continue. Else, return false.

#include <stdio.h>
 
bool hasOnlyOneChild(int pre[], int size)
{
    int nextDiff, lastDiff;
 
    for(int i=0; i<size-1; i++)
    {
        nextDiff = pre[i] - pre[i+1];
        lastDiff = pre[i] - pre[size-1];
        if(nextDiff*lastDiff < 0)
            return false;;
    }
    return true;
}
 
// driver program to test above function
int main()
{
    int pre[] = {8, 3, 5, 7, 6};
    int size = sizeof(pre)/sizeof(pre[0]);
    if (hasOnlyOneChild(pre, size) == true )
        printf("Yes");
    else
        printf("No");
    return 0;
}
Output:

 Yes 
Approach 3
1. Scan the last two nodes of preorder & mark them as min & max.
2. Scan every node down the preorder array. Each node must be either smaller than the min node or larger than the max node. Update min & max accordingly.

#include <stdio.h>
 
int hasOnlyOneChild(int pre[], int size)
{
    // Initialize min and max using last two elements
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
 
 
    // Every element must be either smaller than min or
    // greater than max
    for(int i=size-3; i>=0; i--)
    {
        if (pre[i] < min)
            min = pre[i];
        else if (pre[i] > max)
            max = pre[i];
        else
            return false;
    }
    return true;
}
 
// Driver program to test above function
int main()
{
    int pre[] = {8, 3, 5, 7, 6};
    int size = sizeof(pre)/sizeof(pre[0]);
    if (hasOnlyOneChild(pre,size))
        printf("Yes");
    else
        printf("No");
    return 0;
}
Output:

Yes
Total number of possible Binary Search Trees with n keys
Total number of possible Binary Search Trees with n different keys = 
Catalan number Cn = (2n)!/(n+1)!*n!

Convert a given tree to its Sum Tree
                 10
               /      \
	         -2        6
           /   \      /  \ 
	      8     -4   7    5
should be changed to

                 20(4-2+12+6)
               /      \
	     4(8-4)      12(7+5)
           /   \      /  \ 
	      0    0    0     0
	 

Check for Children Sum Property in a Binary Tree.
   10
  8  2
3  5   2

Convert an arbitrary Binary Tree to a tree that holds Children Sum Property
Question: Given an arbitrary binary tree, convert it to a binary tree that holds Children Sum Property. You can only increment data values in any node (You cannot change structure of tree and cannot decrement value of any node).

For example, the below tree doesn’t hold the children sum property, convert it to a tree that holds the property.

             50
           /     \     
         /         \
       7             2
     / \             /\
   /     \          /   \
  3        5      1      30
  
http://www.geeksforgeeks.org/convert-an-arbitrary-binary-tree-to-a-tree-that-holds-children-sum-property/
