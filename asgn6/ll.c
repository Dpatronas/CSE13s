#include "ll.h"       //Linked List

//bool move_to_front;

ListNode *ll_node_create( struct HatterSpeak *gs) {
  //allocate a ListNode on the heap
	ListNode *nn = (ListNode*)malloc(sizeof(ListNode));
  nn->gs = gs;
  nn->next = NULL;
  //return the allocated ListNode
  return nn;
}

//	Destructor for a ListNode
// n:		The ListNode to free
void ll_node_delete(ListNode *n) {
  //free the fields
  free(n->gs->oldspeak);
  if ( n->gs->hatter) {
    free(n->gs->hatter);
  }
  //free the node itself
  free(n);
}

//  Destructor for a Linked List of ListNodes
// head:	the head of the linked list
void ll_delete(ListNode *head) {
  // curr
  // [0]->[1]->[2]
	ListNode *curr_head = head; //temp to save the current head
	ListNode *next = NULL;      //temp ptr to next node

	//while there is a head     curr next
	while(curr_head) {        //[0]->[1]->[2]
		next = curr_head->next; //store the pointer to next node in list
		ll_node_delete(curr_head);  //free the current head   [x]->[1]->[2]
		curr_head = next;	      //jump to next node       free curr next
	}
	//returns null value for the 
	head = NULL;
}

// inserts newnode into the back
//	Creates and inserts a ListNode into a linked list
// head:	The head of the linked list to insert in
// gs:		HatterSpeak struct
ListNode *ll_insert(ListNode **head, struct HatterSpeak *gs) {

  //before inserting, look up if node exists
  if ( ll_lookup (head, gs->oldspeak) ) {
    //printf("\nduplicate found!\n");
    free(gs->oldspeak);
    free(gs->hatter);
    free(gs);
    return *head;
  }

	//create new ListNode
	ListNode *nn = (ListNode*)malloc(sizeof(ListNode));
	//set the nn data field = data ptr
	nn->gs = gs;
  //nn next points to current head
	nn->next = (*head);
	//set head of linked list as nn
	*head = nn;
  //increment the ll_length
  ll_length++;
  //return that newly created ListNode
  return nn;
}

//	Searches for a specific OLDSPEAK word in a linked list
// Returns the ListNode if found and NULL otherwise
// head:	The head of the linked list to search in
// key:		The key to search for (OLDSPEAK word)

//ll_lookup will traverse through the linked list and compare the oldspeak you’re looking for 
//with each node’s hatterspeak struct’s oldspeak
ListNode *ll_lookup(ListNode **head, char *key) {

	ListNode* curr_head = *head;    //temp to save ptr to current head
  ListNode* node_res = NULL;      //default return value is NULL
  char *stored = NULL;            //to hold the oldspeak string in HatterSpeak

  //while there is a head in ll keep traversing LL
  while(curr_head) {
    links+=1;
    
    //the data we are looking for within the current node
    stored = curr_head->gs->oldspeak; 

    //deference and strcomp()
    if ( strcmp( stored, key) == 0 ) {
      //printf("\nstored: %s", stored);
      //printf(" == key found: %s", key);
      //ll_node_print( curr_head );

      node_res = curr_head;
      curr_head = curr_head->next;
    }
    else {
////////printf("\nkey not found in this node\n");
      //if its not found go to the next node in Linked List
      curr_head = curr_head->next;
    }
  }
  //return Null or the ptr to head which the oldspeak was found
  return node_res;
}


void ll_print(ListNode **head) {
  
  ListNode * curr_head = *head;
  while( curr_head ) {

    ll_node_print( &curr_head );
    printf("\n");
    curr_head = curr_head->next;
  }
}
  
void ll_node_print( ListNode **head ) {
  ListNode *curr_head = *head;
  printf("%s", curr_head->gs->oldspeak);

  if ( curr_head->gs->hatter ) {
    printf(" -> %s", curr_head->gs->hatter);
  }
}
