#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// variable declarations static scope
typedef enum faceim { LEFT, RIGHT, CENTER, PASS } faces;
static faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS};
static const char *names[] = {
    "Happy",  "Sleepy", "Sneezy",        "Dopey",      "Bashful",
    "Grumpy", "Doc",    "Mirror Mirror", "Snow White", "Wicked Queen"};
static int players, pot, pos, seed = 0;

// returns the position to the left of the current player (pos)
int left(int pos, int players) { return ((pos + players - 1) % players); }

// returns the position to the right of the current player (pos)
int right(int pos, int players) { return ((pos + players + 1) % players); }

// function to generate a new random number between 0 and 5
int roll() { return rand() % 6; }

// checks the players in the game
int checkplayers(int *pbalance, int numplayers) {
  players = 0; // reset player count
  for (int i = 0; i < numplayers; i++) {
    if (*pbalance > 0) {
      players++; // count players with money
      pbalance++;
    }
  }
  return players;
}

// Output / Input for variable assignment of seed and players
void start() {
  printf("Random seed:\n");
  scanf("%ud", &seed);
  srand(seed);
  printf("How Many Players?:");
  scanf("%ud", &players);
}

int main(void) {
  int temp, maxroll = 0;
  start();
  // allocate and initialize players balance values to 3
  int pbalance[10];
  for (int i = 0; i < players; i++) {
    pbalance[i] = 3;
  }

  // win condition: be the last player with money
  while (checkplayers(pbalance, players) > 0) {
    if (pbalance[pos] > 0) { // if current pos player is in the game
      printf("%s rolls...", names[pos]);
      maxroll = 0;

      while ((pbalance[pos] > 0) && (maxroll < 3)) {
        temp = roll();
        switch (die[temp]) {
        case (0): // player lands on LEFT
          printf(" gives $1 to %s", names[left(pos, players)]);
          pbalance[pos]--;
          pbalance[left(pos, players)]++;
          maxroll++;
          break;
        case (1): // player lands on RIGHT
          printf(" gives $1 to %s", names[right(pos, players)]);
          pbalance[pos]--;
          pbalance[right(pos, players)]++;
          maxroll++;
          break;
        case (2): // player lands on CENTER
          printf(" puts $1 in the pot");
          pbalance[pos]--;
          pot++;
          maxroll++;
          break;
        case (3): // player lands on PASS
          printf(" gets a pass");
          maxroll++;
          break;
        default:
          printf("Bad case!");
          break;
        }
      }
      printf("\n");
      pos = right(pos, players);
    }
  }
  printf("%s wins the $%d pot with $%d left in the bank!", names[pos], pot,
         pbalance[pos]);
  return 0;
}
