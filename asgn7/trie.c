#include "trie.h"
#include "code.h"
#include <stdio.h>
#include <stdlib.h>

// starts off tree with one node using "code.h" EMPTY_CODE
TrieNode *trie_create(void) {

  // allocate memory for one node
  return trie_node_create(EMPTY_CODE);
}

TrieNode *trie_node_create(uint16_t index) {

  // allocate memory for the new TriNode node
  TrieNode *nn = calloc(1, sizeof(TrieNode));
  if (!nn) {
    printf("bad calloc of trie_node_create!");
    exit(1);
  }
  // set all children in nn to NULL
  for (uint32_t i = 0; i < ALPHABET; i++) {
    nn->children[i] = NULL;
  }
  // set the field for the node (code == index == sym)
  nn->code = index;
  return nn;
}

// will return null if the child doesnt exist
// otherwise will return pointer to trinode child
TrieNode *trie_step(TrieNode *n, uint8_t sym) {

  if (n->children[sym] == NULL) {
    return NULL;
  }
  // printf("\nQueried sym %d", sym);
  // printf(" holds: %d", n->children[sym]->code);

  return n->children[sym];
}

void trie_reset(TrieNode *root) {

  if (!root) {
    exit(1);
  }
  for (int i = 0; i < ALPHABET; i++) {
    trie_delete(root->children[i]);
    root->children[i] = NULL;
  }
}

// pass the n node of the tree
// delete bottom of the tree up
void trie_delete(TrieNode *n) {

  // check the root node exists
  if (!n) {
    return;
  }
  // rescursively delete the children from the bottom up the tree
  for (int i = 0; i < ALPHABET; i++) {
    trie_delete(n->children[i]);
    n->children[i] = NULL;
  }
  // delete the node itself
  trie_node_delete(n);
}

void trie_node_delete(TrieNode *n) {
  // delete the node
  Free(n);
}

void Free(TrieNode *ptr) {
  free(ptr);
  ptr = NULL;
}

void trie_print(TrieNode *root) {

  if (!root) {
    printf("Trie root DNE");
    exit(1);
  }
  // print the children in the root
  for (int i = 0; i < ALPHABET; i++) {
    if (root->children[i]) {
      printf("child: %d\n", root->children[i]->code);
      trie_print(root->children[i]);
    }
  }
}
