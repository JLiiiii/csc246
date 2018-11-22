#include <stdio.h>
#include <stdlib.h>

// Make a short name for a Node.
typedef struct Node Node;

// Node to build our list from.
struct Node {
  // Value in our list
  int val;
  
  // Pointer to the next node.
  Node *next;
};

// Representation for a list, with a head and a tail pointer.
typedef struct {
  // Head pointer for the list.
  Node *head;
  
  // Pointer to the last node in the list, or null if the list
  // is empty.
  Node *tail;
} List;

// Recursive quicksort.
void sort( List *list ) {
  // ...
	if ( !list->head )
		return;
	List *smaller = ( List * )malloc( sizeof( List ) );
    List *goe = ( List * )malloc( sizeof( List ) );

    while ( list->head && list->head->next )
    {
	    if ( list->head->next->val < list->head->val )
	    {
	      if ( smaller->tail )
	      {
	        smaller->tail->next = list->head->next;
	      }
	      else
	        smaller->head = list->head->next;
	      smaller->tail = list->head->next;
	    }
	    else
	    {
	      if ( goe->tail )
	      {
	    	  goe->tail->next = list->head->next;
	      }
	      else
	      {
	        goe->head = list->head->next;
	      }
	      goe->head = list->head->next;
	    }
	    list->head->next = list->head->next->next;
    }
	sort( smaller );
	sort( goe );

	if ( smaller->tail )
		smaller->tail->next = list->head;
	else
		smaller->tail = list->head;
	list->head->next = goe->head;

	if ( smaller->head )
		list->head = smaller->head;
	else
		list->head = smaller->tail;

}

int main( int argc, char *argv[] )
{
  int n = 10;
  if ( argc >= 2 )
    if ( argc > 2 || sscanf( argv[ 1 ], "%d", &n ) != 1 ||
         n < 0 ) {
      fprintf( stderr, "usage: array <n>\n" );
      exit( EXIT_FAILURE );
    }
  
  // Representaton for the list.
  List list = { NULL, NULL };

  // Pointer to the null pointer at the end of our list, so we can grow
  // the list front-to-back;
  for ( int i = 0; i < n; i++ ) {
    // Make a node containing a random value.
    Node *n = (Node *) malloc( sizeof( struct Node ) );
    *n = (Node) { rand(), NULL };

    // Link it in at the tail end of the list.
    if ( list.tail )
      list.tail->next = n;
    else
      list.head = n;
    list.tail = n;
  }

  sort( &list );

  // Print the sorted items.
  for ( Node *n = list.head; n; n = n->next )
    printf( "%d\n", n->val );

  // Free memory for the list.
  while ( list.head ) {
    Node *n = list.head;
    list.head = n->next;
    free( n );
  }

  return 0;
}
