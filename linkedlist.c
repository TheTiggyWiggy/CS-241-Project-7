/*************************************
* Tanner Wagner
* Professor Haugh
* CS 241
* Group 3RW
*
* This file is meant to contain all the
* code necessary to implement 
* linkedlist.h. To use it, simply
* compile it with the gcc and Wall 
* flags. From there you can run it 
* with a makefile like listtest.c
*
*************************************/

#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

/*************************************
* Each parameter’s type and name:
* input: char data
* its meaning: represents the data to be stored in the new node
* its range of values: any valid character
* output: None
* Function’s return value: struct ListNode*
* its meaning: pointer to the newly created node
* Description of what the function does: Creates a new node with the given data and returns a pointer to it.
* Function’s algorithm:
1. Allocate memory for a new node using malloc.
2. If memory allocation is successful (newNode is not NULL):
    a. Set the data of the new node to the given data.
    b. Set the next pointer of the new node to NULL.
3. Return a pointer to the newly created node (newNode).
*************************************/

struct ListNode* createNode(char data)
{
  struct ListNode* newNode = malloc(sizeof(struct ListNode));

  if (newNode)
  {
    newNode->data = data;
    newNode->next = NULL;
  }

  return newNode;
}

/*************************************
* Each parameter’s type and name:
* input: struct ListNode* head
* its meaning: pointer to the head of the linked list
* its range of values: any valid memory address (NULL if the list is empty)
* input: char data
* its meaning: represents the data to be inserted into the linked list
* its range of values: any valid character
* output: struct ListNode*
* its meaning: pointer to the head of the modified linked list
* Description of what the function does: Inserts a new node with the given data into the linked list while maintaining ascending order based on data.
* Function’s algorithm:
1. Create a new node with the given data using the createNode function.
2. If the list is empty or the data to be inserted is less than or equal to the data in the current head node:
    a. Set the next pointer of the new node to the current head.
    b. Return a pointer to the new node as the new head.
3. Initialize a current pointer to the head.
4. Traverse the list while the next node exists and the data in the next node is less than the given data:
    a. Move the current pointer to the next node.
5. Set the next pointer of the new node to the next node of the current node.
6. Set the next pointer of the current node to the new node.
7. Return a pointer to the head of the list.
*************************************/

struct ListNode* insertSorted(struct ListNode* head, char data)
{
  struct ListNode* newNode = createNode(data);
  struct ListNode* current;
  
  if (!head || data <= head->data)
  {
    newNode->next = head;
    return newNode;
  }

  current = head;

  while (current->next && current->next->data < data)
  {
    current = current->next;
  }

  newNode->next = current->next;
  current->next = newNode;

  return head;
}

/*************************************
* Each parameter’s type and name:
* input: struct ListNode** headRef
* its meaning: pointer to a pointer to the head of the linked list
* its range of values: any valid memory address (NULL if the list is empty)
* input: char data
* its meaning: represents the data of the node to be removed from the linked list
* its range of values: any valid character
* output: int
* its meaning: indicates whether the removal operation was successful (1) or not (0)
* Description of what the function does: Removes the first occurrence of a node with the given data from the linked list.
* Function’s algorithm:
1. Initialize pointers current and prev.
2. Traverse the list:
    a. If the data of the current node matches the given data:
        i. If the previous node exists (not the head):
            - Update the next pointer of the previous node to skip the current node.
        ii. If the previous node does not exist (current node is the head):
            - Update the head pointer to skip the current node.
        iii. Free the memory of the current node.
        iv. Return 1 to indicate successful removal.
    b. Update prev to the current node and move current to the next node.
3. If no node with the given data is found, return 0 to indicate failure.
*************************************/

int removeItem(struct ListNode** headRef, char data)
{
  struct ListNode* current = *headRef;
  struct ListNode* prev = NULL;

  while (current)
  {
    if (current->data == data)
    {
      if (prev)
      {
	prev->next = current->next;
      }
      else
      {
	*headRef = current->next;
      }
      free(current);
      return 1;
    }
    prev = current;
    current = current->next;
  }

  return 0;
}

/*************************************
* Each parameter’s type and name:
* input: struct ListNode* head
* its meaning: pointer to the head of the stack
* its range of values: any valid memory address (NULL if the stack is empty)
* input: char data
* its meaning: represents the data to be pushed onto the stack
* its range of values: any valid character
* output: struct ListNode*
* its meaning: pointer to the new head of the stack after pushing the data
* Description of what the function does: Pushes a new node with the given data onto the stack.
* Function’s algorithm:
1. Create a new node with the given data using the createNode function.
2. Set the next pointer of the new node to the current head of the stack.
3. Return a pointer to the new node as the new head of the stack.
*************************************/

struct ListNode* pushStack(struct ListNode* head, char data)
{
  struct ListNode* newNode = createNode(data);

  newNode->next = head;

  return newNode;
}

/*************************************
* Each parameter’s type and name:
* input: struct ListNode** headRef
* its meaning: pointer to a pointer to the head of the stack
* its range of values: any valid memory address (NULL if the stack is empty)
* output: char
* its meaning: the data popped from the stack
* its range of values: any valid character
* Description of what the function does: Pops the top element from the stack and returns its data.
* Function’s algorithm:
1. Initialize pointers temp and data.
2. Check if headRef is NULL or if the stack is empty.
    - If so, return '\0' indicating failure.
3. Set temp to point to the current head of the stack.
4. Store the data of the top node in the variable data.
5. Update the head of the stack to point to the next node.
6. Free the memory of the top node.
7. Return the data that was popped from the stack.
*************************************/

char popStack(struct ListNode** headRef)
{
  struct ListNode* temp;
  char data;
  
  if (!headRef || !*headRef)
  {
    return '\0';
  }

  temp = *headRef;
  data = temp->data;
  *headRef = temp->next;

  free(temp);

  return data;
}

/*************************************
* Each parameter’s type and name:
* input: struct ListNode* head
* its meaning: pointer to the head of the linked list
* its range of values: any valid memory address (NULL if the list is empty)
* output: int
* its meaning: the length of the linked list
* Description of what the function does: Calculates and returns the length of the linked list.
* Function’s algorithm:
1. Initialize count to 0.
2. Traverse the list:
    a. Increment count.
    b. Move head to the next node.
3. Return the final count, which represents the length of the linked list.
*************************************/

int listLength(struct ListNode* head)
{
  int count = 0;

  while (head)
  {
    count++;
    head = head->next;
  }

  return count;
}

/*************************************
* Each parameter’s type and name:
* input: struct ListNode* head
* its meaning: pointer to the head of the linked list
* its range of values: any valid memory address (NULL if the list is empty)
* output: None
* Description of what the function does: Prints the data stored in each node of the linked list, separated by commas, and ends with a newline character.
* Function’s algorithm:
1. Traverse the list:
    a. Print the data of the current node.
    b. If the next node exists:
        - Print a comma and a space.
    c. Move head to the next node.
2. Print a newline character to end the output.
*************************************/

void printList(struct ListNode* head)
{
  while (head)
  {
    printf("%c", head->data);
    if (head->next)
    {
      printf(", ");
    }
    head = head->next;
  }

  printf("\n");
}

/*************************************
* Each parameter’s type and name:
* input: struct ListNode* head
* its meaning: pointer to the head of the linked list
* its range of values: any valid memory address (NULL if the list is empty)
* output: None
* Description of what the function does: Frees the memory allocated for all nodes in the linked list.
* Function’s algorithm:
1. Initialize a temporary pointer temp.
2. Traverse the list:
    a. Set temp to point to the current node.
    b. Move head to the next node.
    c. Free the memory of the current node using temp.
3. Repeat steps 2 until all nodes in the list have been freed.
*************************************/

void freeList(struct ListNode* head)
{
  struct ListNode* temp;

  while (head)
  {
    temp = head;
    head = head->next;
    free(temp);
  }
}

/*************************************
* Each parameter’s type and name:
* input: struct ListNode** headRef
* its meaning: pointer to a pointer to the head of the linked list
* its range of values: any valid memory address (NULL if the list is empty)
* output: None
* Description of what the function does: Reverses the order of nodes in the linked list.
* Function’s algorithm:
1. Initialize pointers prev, current, and next.
2. Set current to point to the head of the list.
3. While current is not NULL:
    a. Set next to point to the next node of current.
    b. Reverse the next pointer of current to point to the previous node (prev).
    c. Move prev to point to the current node.
    d. Move current to point to the next node (next).
4. Update the head pointer to point to the new first node of the reversed list (prev).
*************************************/

void reverseList(struct ListNode** headRef)
{
  struct ListNode* prev = NULL;
  struct ListNode* current = *headRef;
  struct ListNode* next = NULL;

  while (current)
  {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }

  *headRef = prev;
}
