#include "word.h"

Word *word_create(uint8_t *syms, uint64_t len) {

	Word *w = (Word *)calloc(1, sizeof(Word));
  if ( w == NULL ) {
		printf("ERR: w calloc failed");
		exit(1);
	}

  if(len) {
    w->syms = (uint8_t *)calloc(len, sizeof(uint8_t));
    if ( !w->syms ) {
      printf("ERR: w->syms calloc failed");
      exit(1);
    }
  }

	w->len = len;
  for (uint64_t i = 0; i < len; i++) {
    w->syms[i] = syms[i];
  }

  return w;
}

//make a new word:
//using original word + appended symbol
//make sure there is a length to transfer symbols
//otherwise fill that empty word during append
Word *word_append_sym(Word *w, uint8_t sym) {
	Word *new_word = (Word *)calloc(1, sizeof(Word));
  if ( new_word == NULL ) {
		printf("ERR: new_word calloc failed");
		exit(1);
	}

  new_word->len = w->len + 1;
  new_word->syms = (uint8_t *)calloc(new_word->len, sizeof(uint8_t));
  if ( !new_word->syms ) {
    printf("ERR: new_word->syms calloc failed");
    exit(1);
  }

  for (uint64_t i = 0; i < w->len; i++) {
    new_word->syms[i] = w->syms[i];
  }

  new_word->syms[w->len] = sym;

  return new_word; 
}

void word_delete(Word *w) {
  free(w->syms); w->syms = NULL;
	free(w);
}

WordTable *wt_create(void) {

	WordTable *wt = calloc(MAX_CODE, sizeof(Word));
	if (!wt) {
		printf("ERR: neww calloc wt");
		exit(1);
	}
	//initialize wt with an empty word length = 0
	wt[EMPTY_CODE] = word_create (NULL, 0);
	return wt;
}

void wt_reset(WordTable *wt) {

	for ( uint64_t i = START_CODE; i < MAX_CODE; i++) {
		if (wt[i]) {
			word_delete( wt[i]);
      wt[i] = NULL;
		}
	}
}

void wt_delete(WordTable *wt) {
	wt_reset(wt);
	free(wt);
}

void w_print(Word *w) {
  printf("\n");
  for (uint32_t i = 0; i < w->len; i++) {
    char c = w->syms[i];
    printf("%c", (c) );
  }
  printf("\n");
}
