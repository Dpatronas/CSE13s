//main = hatterspeak.c

#include "bf.h"     //bloom filter
#include "ll.h"     //linked list
#include "hash.h"   //hash table
#include "parser.h" //parser
#include <regex.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>

//////////////////////////////////////////////////////////////

//validate words
#define REG "[a-zA-z0-9_]+(('|-)[a-zA-Z0-9_]*)*"

//getopt / optargs
#define OPTIONS "shmb:f:"

//externs
bool move_to_front;
int seeks;
int links;
int ll_length;

//global triggers for getopt
bool error_letter = 0;
bool trans_letter = 0;

//////////////////////////////////////////////////////////////

//function to convert string characters to lower case
void to_low ( char str[] ) {
  char letter;
  for (uint32_t i = 0; i < strlen(str); i++) {
    letter = str[i];
    str[i] = tolower(letter);
  }
}

//
//function to read the oldspeak txt
//populates the bloomfilter with oldspeak
//creates hatterspeak struc for each word without a translation
//populates the hashtable with hatterspeak struct
//
void read_oldspeak_txt ( BloomFilter *bf, HashTable *ht ) {

  FILE *os_txt = fopen("oldspeak.txt", "r");
  //check if file opened ok
  if (!(os_txt )) {
    perror("file opening error");
    exit(1);
  }

  //read the oldspeak file
  char oldspeak[100];    //a place to store the words
  int words_forbid_os = 0;  //# words read and stored

  while ( fscanf( os_txt, "%s\n", oldspeak ) != EOF) {

    to_low(oldspeak);
    bf_insert(bf, oldspeak );
    words_forbid_os++;

    //make a struct for each oldspeak word and set the hatterspeak to NULL
    HatterSpeak * new_hs = hs_create( oldspeak , NULL );

    //insert the new struct into the hashtable
    ht_insert( ht, new_hs );
  }
  fclose(os_txt);
}

//
//function to read the hatterspeak txt
//populates the bloomfilter with oldspeak
//creates hatterspeak struc for each word WITH a translation
//populates the hashtable with hatterspeak struct
//
void read_hatterspeak_txt( BloomFilter *bf, HashTable *ht ) {

  char old[100];          //first part of the word is oldspeak
  char hatt[100];         //second part of the word is hatterspeak tranlation
  int words_hatter = 0;

  FILE *hs_txt = fopen("hatterspeak.txt", "r");
  if (!(hs_txt )) {
    perror("file opening error");
    exit(1);
  }

  while (fscanf(hs_txt, "%s %s\n", old, hatt) != EOF) {

    to_low(old);   
    to_low(hatt);
    words_hatter++;
    
    bf_insert(bf, old);
    HatterSpeak * new_hs2 = hs_create(old, hatt);
    ht_insert( ht, new_hs2);

  }
  fclose(hs_txt);

}

int main(int argc, char **argv) {
  
  int c = 0;
  //optarg user inputs
  bool stats = 0;
  bool notMTF = 0;
  char *get_ht_size = NULL;
  char *get_bf_size = NULL;

  //default values
  uint32_t bfsize = 1048576;
  uint32_t htsize = 10000;

//////////////////////////////////////////////////////////////

//getopt while
  while ( (c = getopt(argc, argv, OPTIONS)) != -1) {

    switch (c) {
      //show stats supress text
      case 's':
        stats = 1;
        break;

      //set size of hashtable
      case 'h':
        get_ht_size = optarg;
        if (atoi(get_ht_size) > 0) {
          htsize = atoi(get_ht_size);
        }
        break;

      //set size of  bloomfilter
      case 'f':
        get_bf_size = optarg;
        if (atoi(get_bf_size) > 0) {
          bfsize = atoi(get_bf_size);
        }
        break;

      //toggle move to front
      case 'm':
        move_to_front = 1;
        break;

      //disable move to front
      case 'b':
        notMTF = 1;
        break;
    }
  }

//////////////////////////////////////////////////////////////

////error check the getopt
//  if (argc == 1) {
//    return -1;
//  }

//exit if both -m and -b are selected
  if ( move_to_front && notMTF) {
    printf("Cannot select both -m & -b options! Exitting..");
    exit(1);
  }

//////////////////////////////////////////////////////////////

  //create the two adts
  BloomFilter * bf = bf_create( bfsize);
  HashTable * ht = ht_create( htsize);

  //create linked lists for inputted words
  ListNode *forbidden = NULL;
  ListNode *translatable = NULL;

  //popoulate the bf and ht with txt files
  read_oldspeak_txt( bf, ht );
  read_hatterspeak_txt( bf, ht );
  
  //create and check the regex
  regex_t regx;
  if ( regcomp (&regx, REG, REG_EXTENDED) ) {
    printf("Bad expression");
    exit(1);
  }

  //stores user input strings
  char *input = NULL;
  //keep taking input until EOF or null terminating
  while ((input = next_word(stdin, &regx)) != NULL ) {

    //lower case for uniformity / matching
    to_low(input);

    //check existence of key in bf
    if (bf_probe(bf, input)) {

      //create a node that is set from node of hashtable input key
      ListNode * node = ht_lookup( ht, input);

      //check the node is valid
      if (node) {

        //check if theres a hatterspeak in nodes struct
        if (node->gs->hatter) {

          //create a struct and set fields for the words
          HatterSpeak *trans = hs_create(node->gs->oldspeak, node->gs->hatter);
          //add struct to a ll of translatable words
          translatable = ll_insert( &translatable, trans);
          //proc the condition for letter printing
          trans_letter = 1;
        }

        //if no hatterspeak, then forbidden word
        else {

          //create a forbidden struct set fields 
          HatterSpeak *forb = hs_create(node->gs->oldspeak, node->gs->hatter);
          //add struct to a ll of forbidden words
          forbidden = ll_insert( &forbidden, forb);
          //proc the condition for error printing
          error_letter = 1;
        }
      }
    }
  }

  fclose(stdin);
  Clear_words();

//////////////////////////////////////////////////////////////

  //print the stats report
  if (stats) {
    //# of times the hashtable looks for a key in linked list
    printf("\nSeeks: %d", seeks);

    //number of nodes travered / seeks
    double avg_seek= (double) links /seeks;
    printf("\nAverage Seek Length: %f", avg_seek );

    //sum of linked list length / ht length
    double avg_ll = (double)ll_length / ht->length; 
    printf("\nAverage Linked List Length: %f", (avg_ll) );

    //hashtable load is the total size of ht/ !NULL heads in the ht
    double ht_load = (double) ht->length / ht_count(ht);
    printf("\nHash Table Load: %f%%", ht_load );
    
    //number of set bits in bf / length of bf
    double bf_load = (double) set_bits / bfsize;
    printf("\nBloom Filter Load: %f%%", bf_load );
  }

  //print the letter
  else {

    if( error_letter && trans_letter) {
      printf("Dear Comrade,");
      printf("\n\nYou have chosen to use words that the queen has decreed oldspeak.");
      printf("\nDue to your infraction you will be sent to the dungeon where you will be taught hatterspeak.");
      printf("\n\nYour errors:\n\n");
      ll_print( &forbidden );

      printf("\nAppropriate hatterspeak translations.\n\n");
      ll_print( &translatable );
    }

    else if( error_letter ) {
      printf("\nDear Comrade,");
      printf("\n\nYou have chosen to use words that the queen has decreed oldspeak.");
      printf("\nDue to your infraction you will be sent to the dungeon where you will be taught hatterspeak.");
      printf("\n\nYour errors:\n\n");
      ll_print( &forbidden );
    }

    else if( trans_letter ) {
      printf("Dear Comrade,");
      printf("\n\nThe decree for hatterspeak finds your message lacking. Some of the words that you used are not hatterspeak.");
      printf("\nThe list shows how to turn the oldspeak words into hatterspeak.\n\n");
      ll_print( &translatable );
    }
  }

//////////////////////////////////////////////////////////////

  //no memory leaks plz
  regfree( &regx );
  //ht_delete( ht );          //frees heads array too
  ll_delete( forbidden );
  ll_delete( translatable );
  bf_delete( bf );          //bloom filter and bf itself
  //bv_delete( bf->filter );  //bit vector

  return 0;
}
