/*************************************
* Tanner Wagner
* Professor Haugh
* CS 241
* Group 3RW
*
* This file stores all the code for
* binarytree.c and is meant to implement
* binarytree.h.
* To use it, you can compile it using 
* the standard gcc -Wall flags and 
* use a makefile such as treetest.c.
*
*************************************/

#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"

/*************************************
* Each parameter’s type and name:
* input: char data
* its meaning: represents the data to be stored in the new tree node
* its range of values: any valid character
* output: None
* Function’s return value: struct TreeNode* (pointer to the newly created tree node)
* Description of what the function does: Creates a new tree node with the given data and returns a pointer to it.
* Function’s algorithm:
1. Allocate memory for a new tree node using malloc.
2. If memory allocation is successful (newNode is not NULL):
    a. Set the data of the new node to the given data.
    b. Set the left and right pointers of the new node to NULL.
3. Return a pointer to the newly created tree node (newNode).
*************************************/

struct TreeNode* createNode(char data)
{
  struct TreeNode* newNode = malloc(sizeof(struct TreeNode));
  
  if (newNode)
  {
    newNode->data = data;
    newNode->left = newNode->right = NULL;
  }

  return newNode;
}

/*************************************
* Each parameter’s type and name:
* input: struct TreeNode* root
* its meaning: pointer to the root of the binary search tree (BST)
* its range of values: any valid memory address (NULL if the tree is empty)
* input: char data
* its meaning: represents the data to be inserted into the BST
* its range of values: any valid character
* output: None
* Function’s return value: struct TreeNode* (pointer to the root of the modified BST)
* Description of what the function does: Inserts a new node with the given data into the binary search tree and returns a pointer to the root of the modified tree.
* Function’s algorithm:
1. If the root is NULL, call createNode to create a new node with the given data and return a pointer to it.
2. If the given data is less than the data in the current root node:
    a. Recursively call insertBST with the left subtree of the current root and the given data.
    b. Assign the returned pointer to the left child of the current root.
3. If the given data is greater than the data in the current root node:
    a. Recursively call insertBST with the right subtree of the current root and the given data.
    b. Assign the returned pointer to the right child of the current root.
4. Return the root of the modified BST.
*************************************/

struct TreeNode* insertBST(struct TreeNode* root, char data)
{
  if (!root) return createNode(data);

  if (data < root->data)
  {
    root->left = insertBST(root->left, data);
  }

  else if (data > root->data)
  {
    root->right = insertBST(root->right, data);
  }

  return root;
}

/*************************************
* Each parameter’s type and name:
* input: struct TreeNode** rootRef
* its meaning: pointer to a pointer to the root of the binary search tree (BST)
* its range of values: any valid memory address (NULL if the tree is empty)
* input: char data
* its meaning: represents the data to be removed from the BST
* its range of values: any valid character
* output: None
* Function’s return value: int
* its meaning: indicates whether the removal operation was successful (1) or not (0)
* Description of what the function does: Removes a node with the given data from the binary search tree and updates the tree accordingly.
* Function’s algorithm:
1. If the root is NULL, return 0 indicating failure.
2. If the given data is less than the data in the current root node:
    a. Recursively call removeBST with the left subtree of the current root and the given data.
3. If the given data is greater than the data in the current root node:
    a. Recursively call removeBST with the right subtree of the current root and the given data.
4. If the data to be removed is found:
    a. If the current node has at most one child:
        i. Assign the child (if any) to a temporary node.
        ii. Free the memory of the current node.
        iii. Update the pointer to the current node to point to the temporary node.
    b. If the current node has two children:
        i. Find the inorder successor (the smallest node in the right subtree).
        ii. Copy the data of the inorder successor to the current node.
        iii. Recursively call removeBST to remove the inorder successor from the right subtree.
5. Return 1 indicating success.
*************************************/

int removeBST(struct TreeNode** rootRef, char data)
{
  struct TreeNode* temp;
  struct TreeNode** successor;
  
  if (!*rootRef) return 0;

  if (data < (*rootRef)->data)
  {
    return removeBST(&((*rootRef)->left), data);
  }

  else if (data > (*rootRef)->data)
  {
    return removeBST(&((*rootRef)->right), data);
  }

  else
  {
    if (!(*rootRef)->left || !(*rootRef)->right)
    {
      temp = (*rootRef)->left ? (*rootRef)->left : (*rootRef)->right;
      free(*rootRef);
      *rootRef = temp;
    }
    else
    {
      successor = &(*rootRef)->right;
      while ((*successor)->left)
      {
	successor = &(*successor)->left;
      }
      (*rootRef)->data = (*successor)->data;
      return removeBST(&(*rootRef)->right, (*successor)->data);
    }
    return 1;
  }
}

/*************************************
* Each parameter’s type and name:
* input: struct TreeNode* root
* its meaning: pointer to the root of the binary search tree (BST)
* its range of values: any valid memory address (NULL if the tree is empty)
* output: char
* its meaning: the minimum value stored in the BST
* Description of what the function does: Finds and returns the minimum value stored in the binary search tree.
* Function’s algorithm:
1. Traverse the left subtree of the BST until reaching the leftmost node (which contains the minimum value).
2. Return the data stored in the leftmost node.
*************************************/

char minValueBST(struct TreeNode* root)
{
  while (root->left)
  {
    root = root->left;
  }

  return root->data;
}

/*************************************
* Each parameter’s type and name:
* input: struct TreeNode* root
* its meaning: pointer to the root of the binary tree
* its range of values: any valid memory address (NULL if the tree is empty)
* output: int
* its meaning: the maximum depth of the binary tree
* Description of what the function does: Calculates and returns the maximum depth of the binary tree.
* Function’s algorithm:
1. If the root is NULL, return 0.
2. Recursively calculate the maximum depth of the left subtree.
3. Recursively calculate the maximum depth of the right subtree.
4. Return the maximum depth among the left and right subtrees, plus 1 (to account for the root node).
*************************************/

int maxDepth(struct TreeNode* root)
{
  int leftDepth;
  int rightDepth;
  
  if (!root) return 0;

  leftDepth = maxDepth(root->left);
  rightDepth = maxDepth(root->right);

  return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

/*************************************
* Each parameter’s type and name:
* input: struct TreeNode* root
* its meaning: pointer to the root of the binary tree
* its range of values: any valid memory address (NULL if the tree is empty)
* output: int
* its meaning: indicates whether the tree is balanced (1) or not (0)
* Description of what the function does: Checks if the binary tree is balanced (i.e., the difference in height between the left and right subtrees is at most 1 for every node).
* Function’s algorithm:
1. If the root is NULL, return 1 (an empty tree is considered balanced).
2. Recursively calculate the maximum depth of the left subtree.
3. Recursively calculate the maximum depth of the right subtree.
4. Check if the absolute difference between the depths of the left and right subtrees is at most 1, and if the left and right subtrees are also balanced.
5. Return 1 if the conditions for a balanced tree are met, otherwise return 0.
*************************************/

int isBalanced(struct TreeNode* root)
{
  int leftDepth;
  int rightDepth;

  if (!root) return 1;

  leftDepth = maxDepth(root->left);
  rightDepth = maxDepth(root->right);

  return abs(leftDepth - rightDepth) <= 1 && isBalanced(root->left) && isBalanced(root->right);
}

/*************************************
* Each parameter’s type and name:
* input: struct TreeNode* root
* its meaning: pointer to the root of the binary tree
* its range of values: any valid memory address (NULL if the tree is empty)
* output: int
* its meaning: indicates whether the tree is a binary search tree (BST) (1) or not (0)
* Description of what the function does: Checks if the binary tree is a valid binary search tree (BST).
* Function’s algorithm:
1. If the root is NULL, return 1 (an empty tree is considered a valid BST).
2. Check if the data in the left subtree is less than the root node's data.
3. Check if the data in the right subtree is greater than the root node's data.
4. Recursively check if both the left and right subtrees are valid BSTs.
5. Return 1 if all conditions for a valid BST are met, otherwise return 0.
*************************************/

int isBST(struct TreeNode* root)
{
  if (root == NULL) return 1;
  if (root->left != NULL && maxDepth(root->left) > root->data) return 0;
  if (root->right != NULL && minValueBST(root->right) < root->data) return 0;
  if (!isBST(root->left) || !isBST(root->right)) return 0;
  return 1;
}

/*************************************
* Each parameter’s type and name:
* input: struct TreeNode* root
* its meaning: pointer to the root of the binary tree
* its range of values: any valid memory address (NULL if the tree is empty)
* output: None
* Description of what the function does: Prints the nodes of the binary tree in an in-order traversal, indicating levels with line breaks.
* Function’s algorithm:
1. Initialize static variables callDepth and firstPrint to keep track of the depth of recursive calls and the first print operation, respectively.
2. If the root is not NULL:
    a. If it's the first print operation, reset callDepth to 0.
    b. Increment callDepth.
    c. Recursively call printTree for the left subtree.
    d. Print the data of the current node.
    e. Recursively call printTree for the right subtree.
    f. Decrement callDepth.
3. If the callDepth is 0 and it's not the first print operation, print a line break.
*************************************/

void printTree(struct TreeNode* root)
{
  static int callDepth = 0;
  static int firstPrint = 1;

  if (root)
  {
    if (firstPrint)
    {
      firstPrint = 0;
      callDepth = 0;
    }
    callDepth++;
    printTree(root->left);
    printf("%c ", root->data);
    printTree(root->right);
    callDepth--;
  }

  if (callDepth == 0 && !firstPrint)
  {
    printf("\b \n");
    firstPrint = 1;
  }
}

/*************************************
* Each parameter’s type and name:
* input: struct TreeNode* root
* its meaning: pointer to the root of the binary tree
* its range of values: any valid memory address (NULL if the tree is empty)
* output: None
* Description of what the function does: Prints the leaf nodes of the binary tree, indicating levels with line breaks.
* Function’s algorithm:
1. Initialize static variables callDepth and firstPrint to keep track of the depth of recursive calls and the first print operation, respectively.
2. If the root is not NULL:
    a. Increment callDepth.
    b. Recursively call printLeaves for the left subtree.
    c. If the current node is a leaf node (has no left or right children):
        i. If it's not the first leaf node to be printed, print a space.
        ii. Print the data of the current node.
        iii. Update firstPrint to indicate that a leaf node has been printed.
    d. Recursively call printLeaves for the right subtree.
    e. Decrement callDepth.
3. If the callDepth is 0 and it's not the first print operation, print a line break.
*************************************/

void printLeaves(struct TreeNode* root)
{
  static int callDepth = 0;
  static int firstPrint = 1;

  if (root)
  {
    callDepth++;
    printLeaves(root->left);
    if (!root->left && !root->right)
    {
      if (!firstPrint)
      {
	printf(" ");
      }
      printf("%c", root->data);
      firstPrint = 0; 
    }
    printLeaves(root->right);
    callDepth--;
  }

  if (callDepth == 0 && !firstPrint)
  {
    printf(" \n");
    firstPrint = 1;
  }
}

/*************************************
* Each parameter’s type and name:
* input: struct TreeNode* root
* its meaning: pointer to the root of the binary tree
* its range of values: any valid memory address (NULL if the tree is empty)
* output: None
* Description of what the function does: Prints the nodes of the binary tree in a verbose format, including the depth of each node and indicating levels with line breaks.
* Function’s algorithm:
1. Initialize static variables depth and firstPrint to keep track of the depth of recursive calls and the first print operation, respectively.
2. If the root is not NULL:
    a. If it's the first print operation, reset depth to 0.
    b. Increment depth.
    c. Print the data of the current node along with its depth.
    d. Recursively call printTreeVerbose for the left subtree.
    e. Recursively call printTreeVerbose for the right subtree.
    f. Decrement depth.
3. If the depth is 0 and it's not the first print operation, print a line break.
*************************************/

void printTreeVerbose(struct TreeNode* root)
{
  static int depth = 0;
  static int firstPrint = 1;

  if (root)
  {
    if (firstPrint)
    {
      firstPrint = 0;
      depth = 0;
    }
    depth++;
    printf("(%c,%d) ", root->data, depth);
    printTreeVerbose(root->left);
    printTreeVerbose(root->right);
    depth--;
  }

  if (depth == 0 && !firstPrint)
  {
    printf("\b \n");
    firstPrint = 1;
  }
}

/*************************************
* Each parameter’s type and name:
* input: struct TreeNode* root
* its meaning: pointer to the root of the binary tree
* its range of values: any valid memory address (NULL if the tree is empty)
* output: None
* Description of what the function does: Frees the memory allocated for all nodes in the binary tree.
* Function’s algorithm:
1. If the root is not NULL:
    a. Recursively call freeTree to free the memory of the left subtree.
    b. Recursively call freeTree to free the memory of the right subtree.
    c. Free the memory of the current node.
*************************************/

void freeTree(struct TreeNode* root)
{
  if (root)
  {
    freeTree(root->left);
    freeTree(root->right);
    free(root);
  }
}
