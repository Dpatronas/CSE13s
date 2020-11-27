#ifndef __HATSPEAK_H__
#define __HATSPEAK_H__

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//struct definition for HatterSpeak
// oldspeak: will always exist
// hatterspeak: may not exist aka NULL which == a forbidden word
typedef struct HatterSpeak {
  char *oldspeak;
  char *hatter;
}
HatterSpeak;

//Constructor for HatterSpeak
//oldspeak will be defined always
//hatterspeak may be null
HatterSpeak * hs_create(char *oldspeak, char *hatter);

//destructor

#endif
