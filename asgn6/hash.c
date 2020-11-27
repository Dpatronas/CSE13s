#include "hash.h"

int seeks;

//similar to ll
//HashTable : chaining linked lists 
// salt:		The salt of the HashTable (used for hashing)
// length:		The maximum number of entries in the HashTable
// heads:		An array of linked list heads
HashTable *ht_create(uint32_t  length) {
	HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
	if (ht) {
		ht->salt[0] = 0x85ae998311115ae3;
		ht->salt[1] = 0xb6fac2ae33a40089;
		ht->length = length;
		ht->heads = (ListNode **)calloc(length, sizeof(ListNode *));
    if(!ht->heads) {
      printf("Hashtable heads failed to allocate");
      exit(1);
    }
		return ht;
	}
  //if not allocated correctly
	return (HashTable *)NIL;
}

//Destructor for a HashTable
//ht:			The HashTable
void ht_delete(HashTable *ht) {
  //free all the nodes
  for (uint32_t i= 0; i < ht->length; i++) {
    if (ht->heads) {
      free(ht->heads);
    }
  }
  free(ht->heads);
  free(ht);
}

//Returns a number of entries in a hash table
// h:			The HashTable
//count all the elements of all the linked lists number of heads
uint32_t ht_count(HashTable *ht) {
  uint32_t count = 0;
  for (uint32_t i = 0; i < ht->length; i++) {
    if ( ht->heads[i] ) {
      count++;
    }
  }
  return count;
}

//Search hashtable for a key
//returns the ListNode if found and returns NULL otherwise
//This should call the ll_lookup() function
//ht:     the HashTable
//key:    key to search for
ListNode *ht_lookup (HashTable *ht, char *key) {
  
  seeks+= 1;
  ListNode* ret = NULL;
  uint32_t index = ( hash(ht->salt,key) ) % ht->length;

  //addr heads[index], word
  if ( ll_lookup( &ht->heads[index], key) ) {

    ret = ll_lookup( &ht->heads[index], key );
  }
  else  {
////printf("\nHT lookup returning NULL\n");
  }
  return ret;
}

//
//Searches a HashTable for a key
//Returns the ListNode if found and if not, returns NULL
//This should call the ll_lookup() function to ensure its not already present in hashtable
//if there is an oldspeak present handle it!
//ht:			The HashTable
//gs:			The Hatterspeak to add to the HashTable (hash the oldspeak = key)
//
void ht_insert(HashTable *ht, struct HatterSpeak *gs) {
  uint32_t len = ht->length;
  uint32_t index = (hash(ht->salt, gs->oldspeak)) % len;
  ht->heads[index] = ll_insert( &ht->heads[index], gs );
}
