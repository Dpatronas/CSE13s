#include "hatspeak.h"

#define strdup(s) strcpy(malloc(strlen(s) + 1), s)

HatterSpeak * hs_create(char *oldspeak, char *hatter) {

  HatterSpeak *hs = (HatterSpeak *)malloc(sizeof(HatterSpeak));
  
  if(!hs) {               //check if hs allocated
    printf("bad hs struct malloc");
  }

  //malloc + copy string
  hs->oldspeak = strdup( oldspeak );
 
  if ( !hs->oldspeak) {  //check if oldspeak allocated
    printf("bad oldspeak field malloc");
  }
  
  //if a hatterspeak is passed into function (non null)
  if (hatter) {
    //malloc + copy string
    hs->hatter = strdup( hatter );

    if ( !hs->oldspeak) {  //check if oldspeak allocated
      printf("bad oldspeak field malloc");
    }
  }
  //if !hatterspeak, set it to NULL
  else {
    hs->hatter = NULL;
  }
  return hs;
}

void hs_delete(HatterSpeak *hs) {
  free(hs->oldspeak);
  free(hs->hatter);
  free(hs);
}

