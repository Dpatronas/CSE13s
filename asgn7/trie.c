#include "trie.h"
#include "code.h"
#include <stdio.h> 
#include <stdlib.h> 

// starts off tree with one node
// with "code.h" EMPTY_CODE
TrieNode *trie_create(void) {

	// allocate memory for one node
	return trie_node_create(EMPTY_CODE);

}

TrieNode *trie_node_create(uint16_t index) {

	// allocate memory for the new TriNode node 
	TrieNode * nn = calloc( 1, sizeof(TrieNode));
	if (!nn) {
		printf("bad calloc of trie_node_create!");
		exit(1);
	}

	//set all children in nn to NULL
	for (uint32_t i = 0; i < 256; i++) {
		nn->children[i] = NULL;
	}

	// set the field for the node index
	nn->code = index;
	return nn;

}

//will return null if the child doesnt exist
//otherwise will return pointer to trinode child
TrieNode *trie_step(TrieNode *n, uint8_t sym) {

	//debugging tool
	if ( n->children[sym] == NULL ) {
		printf("NULL child");
    return NULL;
	}

	return n->children[sym];

}

void trie_reset(TrieNode *root) {

	if (!root) {
		exit(1);
	}
	for (int i = 0; i < 256; i++) {
		if(root->children[i]) {
			trie_delete(root->children[i]);
		}
  }
}

void trie_node_delete(TrieNode *n) {
	//delete the node
	free(n);

}


// pass the n node of the tree
// delete bottom of the tree up
void trie_delete(TrieNode *n) {

	// check the root node exists
	if (!n) {
		printf("no root to delete..");
		return;
	}

	// rescursively delete the children from the bottom up the tree
	for (int i = 0 ; i < 256; i++) {
		trie_delete(n->children[i]);
	}
	// delete the node itself
	trie_node_delete(n);

}
