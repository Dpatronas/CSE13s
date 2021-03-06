#ifndef __HASH_H__
#define __HASH_H__

#ifndef NIL
#define NIL (void *)0
#endif

#include "hatspeak.h" //hs struct
#include "ll.h"       //linked list
#include "speck.h"    //for hash()
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

extern int seeks;

//	Struct  definition  for a HashTable
// chaining linked lists
// salt:		The salt of the HashTable (used for hashing)
// length:		The maximum number of entries in the HashTable
// heads:		An array of linked list heads
typedef struct HashTable {
  uint64_t salt[2];
  uint32_t length;
  ListNode **heads;
} HashTable;

//	Constructor for a HashTable.
// length:		Length of the HashTable.
// salt:		Salt for the HashTable.
HashTable *ht_create(uint32_t length);

// Destructor for a HashTable
// ht:			The HashTable
void ht_delete(HashTable *ht);

// Returns a number of entries in a hash table
// h:			The HashTable
uint32_t ht_count(HashTable *h);

// Search hashtable for a key
// returns the ListNode if found and returns NULL otherwise
// This should call the ll_lookup() function
// ht:     the HashTable
// key:    key to search for
ListNode *ht_lookup(HashTable *ht, char *key);

// First creates a new ListNode from HatterSpeak
// created ListNode is then inserted into a HashTable
// This should call the ll_insert() function
// ht:			The HashTable
// gs:			The HatterSpeak to add to the HashTable
void ht_insert(HashTable *ht, struct HatterSpeak *gs);

#endif
