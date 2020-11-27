#include "hatspeak.h"

HatterSpeak * hs_create(char *oldspeak, char *hatter) {

  HatterSpeak *hs = (HatterSpeak *)malloc(sizeof(HatterSpeak));
  
  if(!hs) {               //check if hs allocated
    printf("bad hs struct malloc");
  }

  //malloc + copy string
  hs->oldspeak = strndup( oldspeak, strlen(oldspeak));
 
  if ( !hs->oldspeak) {  //check if oldspeak allocated
    printf("bad oldspeak field malloc");
  }
  
  //if a hatterspeak is passed into function (non null)
  if (hatter) {
    //malloc + copy string
    hs->hatter = strndup( hatter, strlen(hatter));

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
