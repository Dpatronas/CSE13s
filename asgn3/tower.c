#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define OPTIONS "nsr :"

//default the number of disks to 5
int static disks =  5;

//power function (from my assignment 2)
double Pow (double base, int power) {
    //the minimum return result will be one (if power = 0, base = 1)
    double res = 1;
    //iterate through from [0,power)
    for ( int i = 0; i < power; i++) {
        //result = base * base * base * ... (where you multiple n bases determiend by the power)
        //example 2^3: result = 2 * 2 * 2 (3 bases)
        res *= base;
    }
    return res;
}

//recursive function for the tower
void recursive_tower(int n, char initial, char goal, char extra) 
{ 
    //if were looking at the top disk
    if (n == 1) 
    {
      //move the top into the desired peg based on the current function call configuration
      printf("\nMove disk 1 from peg %c to peg %c", initial, goal); 
      return; 
    } 
    //otherwise deal with the n-1 stack of disks (second to bottom)
    //move stack into the extra peg
    //so extra peg = the goal peg in this case
    recursive_tower(n-1, initial, extra, goal);

    //print between the moves
    printf("\nMove disk %d from peg %c to peg %c", n, initial, goal); 

    //once the stack of discs has all moved into the extra peg
    //move the disks from extra peg into the goal peg using the original peg
    //so source peg = the extra peg in this case
    recursive_tower(n-1, extra, goal, initial);
}

//prints information between moves
void display(Stack *s1, Stack *s2) {
    printf("\nMove disk %d from peg %c to peg %c", s_peek(s1), s1->name, s2->name);
}

//compares values at the top of each peg
//if no disk exists in peg the value is set to n+1 (for precedence in determining move)
//decides which direction the disk will move
void compare(Stack *s1, Stack *s2, int *c1, int *c2) {
  //if the first peg has no disks it has value empty = n+1
  //disk n < disk n-1 (empty) always causes a move to occur into empty peg
  int empty = disks+1;  //empty = disks+1

  if ( s_empty(s1)) {
    //derefence c1 pointer to hold value of empty
    *c1 = empty;
  }
  else  if (s_empty(s2)) {
    *c2 = empty;
  }
  else {
    *c1 = s_peek(s1);
    *c2 = s_peek(s2);
  }
}

void stack_tower(int disks) {
  int n = disks;    //used to fill the source peg initially
  int cs = 0;       //holds the source value from peek for comparison
  int cg = 0;       //holds goal value from peek for comparison
  int ce = 0;       //holds the extrq value from peek for comparison
  int num_moves = Pow(2,disks) - 1;
  
  //instantiate peg1 (the source peg)
  Stack* source = stack(disks, 'A');

  //push the disks onto the peg1. Note: top starts at 0
  //      item[0] = n, item[1] = n-1 .. where n = disks
  for ( int i = 0; i < disks; i++ ) {
    s_push(source, n);
    n--;
  }

  //instantiate peg 2(The goal peg)
  Stack* goal = stack(0, 'B');

  //instantiate peg 3(The extra peg)
  Stack* extra = stack(0, 'C');
  printf("\n");

  //identify odd number of disks
  //if disk /\  1 ==  true we have an odd number
  if (disks & 1) {
    //number of moves determines the iteration
    for ( int i = 0; i < num_moves; i++ ) {
      //determine which move we are performing by mod the i with 3
      int move = i % 3;
        
      switch (move) {
        //first move in sequence
        //odd: (source<->goal)
        case 0:   
          //comepare values of pegs disk values for source and goal
          compare(goal, source, &cg, &cs);

          //if (source disk < goal disk) or goal peg is empty
          //move from source->goal)
          if (cs < cg ) {       
            display(source, goal);
            //push the valur that is popped from source into the goal
            s_push(goal, s_pop(source));
          }
          //otherwise move from goal->source
          else {
            display(goal, source);
            s_push(source, s_pop(goal));
          }
          break;

        //second move in sequence
        //odd: (source<->extra)
        case 1:
          //compare values from source and extra
          compare(extra, source, &ce, &cs);

          // if source < extra
          if ( cs < ce ) {
            display(source, extra);
            //push value popped from source into the extra peg
            s_push(extra, s_pop(source));
          }
          //otherwise move from extra -> source
          else {
            display(extra, source);
            s_push(source, s_pop(extra));
          }
          break;

        //third move in sequence
        //odd: (goal<->extra)
        case 2:
          //find the appropriate legal move
          compare(extra, goal, &ce, &cg);
          //if goal < extra
          if ( cg < ce) {
            //move goal -> extra
            display(goal, extra);
            //push the value popped from goal  peg into extra peg
            s_push(extra, s_pop(goal));
          }
          //otherwise move from extra -> goal
          else {
            display(extra, goal);
            s_push(goal, s_pop(extra));
          }
          break;
        //default if something goes wrong..
        default: 
          printf("\nBad case!");
          break;
        }
      }
    }
  //if number is not odd it must be even 
  //odd has a different sequence thn even as shown above
  else {
    for ( int i = 0; i < num_moves; i++ ) {
      int move = i % 3;

      switch (move) {
        //first even move (s<->e)
        case 0: 
          //find the appropriate legal move
          compare(extra, source, &ce, &cs);

          if (cs < ce ) {
            //(source->extra)
            display(source, extra);

            //push the valur that is popped from source into the goal
            s_push(extra, s_pop(source));
          }
          //otherwise (extra->source)
          else {
            display(extra, source);
            //(goal->source)push the value that is popped from goal into the source
            s_push(source, s_pop(extra));
          }
          break;

        //second move (source<->goal)
        case 1:

          compare(goal, source, &cg, &cs);
          // if source < goal
            if ( cs < cg ) {
              //move source -> goal
              display(source, goal);
              //move source -> goal
              s_push(goal, s_pop(source));
          }
          //otherwise move goal -> source
          else {
            display(goal, source);
            // pop extra put that value into source
            s_push(source, s_pop(goal));
          }
          break;

        //third move ( extra<->goal)
        case 2:
          compare(goal, extra, &cg, &ce);
          //if extra < goal
          if ( ce < cg) {
            //move extra -> goal
            display(extra, goal);
            s_push(goal, s_pop(extra));
          }
          //otherwise move extra -> goal
          else {
            display(goal, extra);
            s_push(extra, s_pop(goal));
          }
          break;

        default: 
          printf("\nBad case!");
          break;
      }
    }
  }
  //housekeeping the heap
  s_delete(source);
  s_delete(goal);
  s_delete(extra);
  //print the moves
  printf("\n\nNumber of moves: %d", num_moves);
  printf("\n");
}

int main( int argc, char **argv) 
{ 
  int c = 0;
  bool recursion = false;
  bool stackk = false;
  char *input_disks =  NULL;
  int moves = Pow(2, disks) -1;
  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
      //recursive
      case 'r':
       recursion = true;
       break;

      //stack
      case 's':
        stackk = true;
        break;

      //input disks
      case 'n':
        input_disks = optarg;
        if (atoi(input_disks) > 0) {
            disks = atoi(input_disks);  //convert the char to int and set static variable to it
            break;
        }
        //otherwise dont set anything
        else { 
            break;
        }
    }
  }
  //error check
  if (argc == 1) {
    return -1;
  }

  //do the recursive implementation of towers game
  if (recursion == 1) {
    printf("=================================");
    printf("\n--------   RECURSION   ----------");
    printf("\n=================================");
    recursive_tower(disks, 'A', 'B', 'C');
    printf("\n\nNumber of moves: %d", (moves));
  }
  //do that stack implementation of towers game
  if ( stackk == 1 ) {
    printf("================================");
    printf("\n----------   STACKS   ----------");
    printf("\n================================");

    stack_tower(disks);
  }

    return 0;
}
