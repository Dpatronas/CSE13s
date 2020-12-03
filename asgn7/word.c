#include "word.h"
#include "code.h"
#include <stdio.h> 

Word *word_create(uint8_t *syms, uint64_t len) {

	//allocate space for word and symbols array
	Word *w = (Word *)malloc(sizeof (Word));
	w->syms = (Word *)malloc(sizeof(uint8_t));

	//check if they malloc'd ok
	if ( (!w) || (!w->syms) ) {
		printf("bad malloc of word_create or w_syms");
		exit(1);
	}

	//set length
	w->len = len;
	//set symbols
	for (uint64_t i = 0; i < len; i++) {
		w->syms[i] = syms[i];
		//OR memcpy//
		//memcpy( malloc(strlen(w->sym[i])+1), sym[i]);
	}

}

//make a new word:
//using original word + appended symbol
//make sure there is a length to transfer symbols
//otherwise fill that empty word during append
Word *word_append_sym(Word *w, uint8_t sym) {

	Word * neww = (Word)malloc(sizeof(Word));
	//check malloc'd
	if (!neww) {
		printf("bad malloc of neww word_append)!");
		exit(1);
	}

	//check if w is empty!
	if ( w->len == 0 ) {
		neww->sym[0] = sym;
		neww->len = 1;
		return neww;
	}

	//new word length set
	neww->len = w->len+1;
	//set symbols
	for (uint64_t i = 0; i < len; i++) {
		w->syms[i] = syms[i];
		//OR memcpy//
		//memcpy( malloc(strlen(w->sym[i])+1), sym[i]);
	}
	//the last element of new word is the appended symbol
	neww->sym[ neww->len-1 ] = sym;
	//return the newly appended symbol
	return neww;
}

void word_delete(Word *w) {

	//free syms in w
	for (uint64_t i = 0; i < len; i++) {
		free(w->sym[i]);
	}
	//free w
	free(w);

}

WordTable *wt_create(void) {

	//malloc the wordtable using code.h
	//callc to initialize WordTable at predefined size
	WordTable *wt = calloc(MAX_CODE, sizeof(Word));
	if (!wt) {
		printf("bad calloc of wt_create!");
		exit(1);
	}
	//initialize wt with an empty word length = 0
	wt[EMPTY_CODE] = word_create (00000, 0);
	return wt;
}

void wt_reset(WordTable *wt) {

	for ( int i = STARTCODE; i < MAX_CODE; i++) {
		if (wt[i]) {
			//delete word at index of wordtable
			word_delete( wt[i]);
		}
	}
}

void wt_delete(WordTable *wt) {

	//free the words in word table
	//must use uin32_t
	for (uint32_t i = 0; i < MAX_CODE; i++) {
		if (wt[i]) {
			word_delete(wt[i])
		}
	}
	//free the wt itself
	free(wt);

}
