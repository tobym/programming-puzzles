/*
 * Background: http://www.rethinkdb.com/blog/2010/06/will-the-real-programmers-please-stand-up/
 * and http://news.ycombinator.com/item?id=1471988
 *
 * "reverse_ll" function is the actual solution. It reverses the linked list in-place. This took
 * about 8 minutes. (Writing the crappy linkedin-list implementation and test took longer, about
 * 15 minutes).
 *
 * main() returns 0 on pass, and 1 on failure.
 *
 */

#include <stdlib.h>
#include <stdio.h>

// terrible but workable linked_list implementation
struct cell {
  int val;
  struct cell * next;
};
typedef struct cell item;

item * cell_factory(int value)
{
  item * new_cell = (item *)malloc(sizeof(item));
  new_cell->val = value;
  new_cell->next = NULL;
  return new_cell;
}

//-------------------------------
// Reverse a singly-linked list
item * reverse_ll(item * head)
{
  if( head==NULL )
  {
    return NULL;
  }
  else if( head->next==NULL )
  {
    return head;
  }

  item * prev = NULL;
  item * curr = head;
  item * next = NULL;

  while(curr)
  {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  // last node before current pointer became null
  return prev;
}

//-------------------------------

void print_list(item * head)
{
  item * curr = head;
  while(curr)
  {
    printf("%d\n", curr->val);
    curr = curr->next;
  }
}

// Build a linked list and print it out
item * ll_sanity_check()
{
  item * head = cell_factory(0);
  item * tmp = NULL;
  item * curr = head;

  int i;
  for( i=1; i<10; i++)
  {
    tmp = cell_factory(i);
    tmp->next = NULL;
    curr->next = tmp;
    curr = curr->next;
  }

  printf("This should print from 0 to 9\n");
  print_list(head);
  printf("-----------------------------\n");

  return head;
}

// assumes head points to a list that started as 0-9 and was reversed 
// (i.e. tests for a list that goes from 9-0)
int test_reversed(item * head)
{
  item * curr = head;

  int i = 9;
  for( ; i >= 0; i--)
  {
    if( curr->val != i )
    {
      return 1;
    }
    curr = curr->next;
  }

  return 0;
}

int main()
{
  item * head = ll_sanity_check();
  item * reversed = reverse_ll(head);

  printf("This should print from 9 to 0\n");
  print_list(reversed);
  printf("-----------------------------\n");

  return test_reversed(reversed);
}
