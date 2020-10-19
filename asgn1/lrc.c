#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// variable declarations static scope
typedef enum faceim { LEFT, RIGHT, CENTER, PASS } faces;
static faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS};
<<<<<<< HEAD
static const char *names[] = {
    "Happy",  "Sleepy", "Sneezy",        "Dopey",      "Bashful",
    "Grumpy", "Doc",    "Mirror Mirror", "Snow White", "Wicked Queen"};

// returns the position to the left of the current player (pos)
int left(int pos, int players) { return ((pos + players - 1) % players); }

// returns the position to the right of the current player (pos)
int right(int pos, int players) { return ((pos + players + 1) % players); }

// function to generate a new random number between 0 and 5
int roll() { return rand() % 6; }

// checks the players in the game
int get_active_players_count(int balance[], int max_players) {
  int num_active_players = 0;

  for (int i = 0; i < max_players; i++) {
    if (balance[i] > 0) {
      num_active_players++; // count players with money
    }
=======
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
    }
    pbalance++;
>>>>>>> 8fca24ad23f34b473d6db11e48d7d04d1311a555
  }
  return num_active_players;
}

<<<<<<< HEAD
int winner(int balance[], int max_players) {
  int last_element = 0;
  int count = 0;
  for (int i = 0; i < max_players; i++) {
    if (balance[i] > 0) {
      last_element = i;
      count++;
    }
  }
  if (count == 1) {
    return last_element;
  } else {
    return -1;
  }
}

int main(void) {
  int players_count, pot, pos, seed;

  pot = pos = 0;

=======
// Output / Input for variable assignment of seed and players
void start() {
>>>>>>> 8fca24ad23f34b473d6db11e48d7d04d1311a555
  printf("Random seed:\n");
  scanf("%ud", &seed);
  srand(2020);

  printf("how many players?:");
  scanf("%ud", &players_count);

<<<<<<< HEAD
  // allocate and initialize players balance values to 3
  int balance[10] = {0};
  for (int i = 0; i < players_count; i++) {
    balance[i] = 3;
  }

  while (1) {
    int active_players = get_active_players_count(balance, players_count);
    // find the winner (last player with money)
    if (active_players == 1) {
      pos = winner(balance, players_count);
      break;
    }
    if (balance[pos] > 0) { // if current pos player is in the game
      printf("%s rolls...", names[pos]);

      int maxroll = 0;

      while ((balance[pos] > 0) && (maxroll++ < 3)) {
        int temp = roll();

        switch (die[temp]) {
        case LEFT: {
          int left_player = left(pos, players_count);
          printf(" gives $1 to %s", names[left_player]);
          balance[pos]--;
          balance[left_player]++;
          break;
        }

        case RIGHT: {
          int right_player = left(pos, players_count);
          printf(" gives $1 to %s", names[right_player]);
          balance[pos]--;
          balance[right_player]++;
          break;
        }

        case CENTER: {
          printf(" puts $1 in the pot");
          balance[pos]--;
          pot++;
          break;
        }

        case PASS:
          printf(" gets a pass");
          break;

        default:
          break;
=======
  int main(void) {
    int temp, maxroll = 0;
    start();
    // allocate and initialize players balance values to 3
    int pbalance[10];
    for (int i = 0; i < players; i++) {
      pbalance[i] = 3;
    }

    // win condition: be the last player with money
    while (checkplayers(pbalance, players) > 1) {

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
>>>>>>> 8fca24ad23f34b473d6db11e48d7d04d1311a555
        }
      }
      printf("\n");
    }
    // next player
    pos = right(pos, players_count);
  }
<<<<<<< HEAD
  printf("%s wins the $%d pot with $%d left in the bank!", names[pos], pot,
         balance[pos]);

=======
    printf("%s wins the $%d pot with $%d left in the bank!", names[pos], pot,
           pbalance[pos]);
>>>>>>> 8fca24ad23f34b473d6db11e48d7d04d1311a555
  return 0;
}
