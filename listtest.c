/*************************************
* Tanner Wagner
* Professor Haugh
* CS 241
* Group 3RW
*
* This file is meant to act as a 
* makefile for linkedlist.c
* To use it, simply compile it with 
* all its other dependencies and then
* run ./listtest.
*
*************************************/

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

/*************************************
* Function Name: main
* Parameters:
*   - argc: [input] [number of command-line arguments] [integer >= 0]
*   - argv: [input] [array of command-line arguments] [array of strings]
* Return Value: integer (return status of the program)
* Description: 
*     The main function serves as the entry point for the program execution. It initializes
*     variables, performs operations on linked lists, and prints the results. Specifically,
*     it populates a linked list and a stack with characters, manipulates them, and then
*     prints their contents and sizes.
* Algorithm:
*     1. Initialize variables: i, n (integer), c (character), head (ListNode pointer),
*        and stack (ListNode pointer) to NULL.
*     2. Print "empty list:" followed by printing the contents of the empty list.
*     3. Populate the linked list and stack with characters using insertSorted and pushStack.
*     4. Print "filled list:" followed by printing the contents of the list and its length.
*     5. Print "filled stack:" followed by printing the contents of the stack and its size.
*     6. Remove items from the list and print a message if an item was not found.
*     7. Print "list after removes:" followed by printing the modified list and its length.
*     8. Pop items from the stack and print them.
*     9. Print "stack after pops:" followed by printing the modified stack and its size.
*    10. Reverse the list.
*    11. Print "list after reverse:" followed by printing the reversed list.
*    12. Free the memory allocated for the list and stack.
*    13. Return 0 to indicate successful execution.
*************************************/

int main(int argc, char** argv)
{
  int i, n;
  char c;
  struct ListNode* head = NULL;
  struct ListNode* stack = NULL;

  printf("empty list: ");
  printList(head);

  for(i = 0; i < 23; ++i)
  {
    c = (i*17+11) % 23 + 'A';
    head = insertSorted(head, c);
    stack = pushStack(stack, c);
  }

  printf("filled list: ");
  printList(head);
  printf("list length = %d\n", listLength(head));

  printf("filled stack: ");
  printList(stack);
  printf("stack size = %d\n", listLength(stack));

  for(i = -4; i < 25; i+=4)
  {
    c = 'A' + i;
    n = removeItem(&head, c);
    if(!n) printf("remove did not find %c\n", c);
  }

  printf("list after removes: ");
  printList(head);
  printf("list length = %d\n", listLength(head));

  for(i = 0; i < 5; ++i)
  {
    printf("pop: %c\n", popStack(&stack));
  }

  printf("stack after pops: ");
  printList(stack);
  printf("stack size = %d\n", listLength(stack));

  reverseList(&head);
  printf("list after reverse: ");
  printList(head);

  freeList(head);
  head = NULL;

  freeList(stack);
  stack = NULL;

  return 0;
}
