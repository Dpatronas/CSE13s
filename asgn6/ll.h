#ifndef __LL_H__
#define __LL_H__

#ifndef NIL
#define NIL (void *)0
#endif

#include "hatspeak.h" //using HatterSpeak struct
#include <stdbool.h>
#include <string.h>

//If flag is set, ListNode that are queried (ll_lookup) are moved to the front
extern bool move_to_front;
//The number of links
static int links = 0;
static int ll_length = 0;

typedef struct ListNode ListNode;

//	Struct definition of a ListNode
// gs:		HatterSpeak struct containing oldspeak 
//			         and its HatterSpeak translation
struct ListNode {
	HatterSpeak *gs;  //the pointer to data to exist in the Linked List
	ListNode *next;   //the pointer to next LL node
};

//	Constructor for a ListNode
// gs:		HatterSpeak struct containing oldspeak and its HatterSpeak translation
ListNode *ll_node_create( struct HatterSpeak *gs);

//	Destructor for a ListNode
// n:		The ListNode to free
void ll_node_delete(ListNode *n);

//	Destructor for a Linked List of ListNodes
// head:	the head of the linked list
void ll_delete(ListNode *head);

//	Creates and inserts a ListNode into a linked list
// head:	The head of the linked list to insert in
// gs:		HatterSpeak struct
ListNode *ll_insert(ListNode **head, struct HatterSpeak *gs);

//	Searches for a specific key in a linked list
// Returns the ListNode if found and NULL otherwise
// head:	The head of the linked list to search in
// key:		The key to search for
ListNode *ll_lookup(ListNode **head, char *key);

//debugging tools
void ll_print(ListNode *head);

void ll_node_print( ListNode *head );

#endif
