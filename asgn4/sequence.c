#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bv.h"
#include "sieve.h"

#define OPTIONS "spn:"

// My power function (from my assignment 2)
double Pow(double base, int power) {
  // the minimum return result will be one (if power = 0, base = 1)
  double res = 1;
  // iterate through from [0,power)
  for (int i = 0; i < power; i++) {
    // result = base * base * base * ... (where you multiple n bases determiend
    // by the power)  example 2^3: result = 2 * 2 * 2 (3 bases)
    res *= base;
  }
  return res;
}

//Mersenne Formula returns the mersenne number based on the power
int mersenne( int power ) {
  return (Pow(2,power)-1);
}

//function to find the fibs from [2,1000]
int fibonacci( int index, int element1, int element2) {
  if (index == 0) {         //fib[index==0] = 2;
    return 2;
  }
  
  else if ( index == 1) {   //fib[index==1] = 3;
    return 3;
  }

  else {                    //fib[index>1] = (index-1) + (index-2)
    return element1 + element2;
  }
}

//Create the Bitvector
//Sieve the BitVector for primes
//Find the special primes
void primes( int length, BitVector *v ) {

  // Since there is only 14 fibonacci numbers from [2-1000] will use array to store them
  // the first 3 fibonacci numbers are excluded (0,1,1) since primes start at 2
  //declare and initalize values to 0
  int fib[14] = {0};

  //populate the fib array
  for ( int i = 0; i < 14; i++) {
    fib[i] = fibonacci(i, fib[i-1], fib[i-2]);
  }

  // Similar line of logic for lucas primes (excluding the initial 1)
  int luc[14] = {2,3,4,7,11,18,29,47,76,123,199,322,521,843};

  //the start of our loop for prime numbers within Bitvector
  int i =2;

  while (i < length) {
    if (bv_get_bit(v,i) == 1 ) {
      printf("%d: prime", i);
      
      //the mersenne number is between [2,9]
      //cannot be <= 1 since 2^1=1 
      //cannot be >=10 since 2^10 = 1024
      for (int m = 0; m < 10; m++ ) {
        if (mersenne(m) == i ) {
          printf(", mersenne");
          m++;
        }
      }

      //we have only 14 numbers to scan based on the lucas array
      for ( int l = 0; l < 13; l++ ) {
        if ( luc[l] == i) {
          printf(", lucas");
          l++;
        }
      }

      //we have only 14 numbers to scan based on the fib array
      for ( int f = 0; f < 13; f++ ) {
        if ( fib[f] == i) {
          printf(", fibonacci");
          f++;
        }
      }
      printf("\n");
    }
    i++; //increment the index
  }
}

int main(int argc, char **argv) {
  int c = 0;

  //default length
  int length = 1000;  

  //optargs
  bool specPrimes = false;
  bool palnPrimes = false;

  char *input_length = NULL;

  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    // recursive
    case 's':
      specPrimes = true;
      break;

    // stack
    case 'p':
      palnPrimes = true;
      break;

    // input the length
    case 'n':
      input_length = optarg;
      if (atoi(input_length) > 0) {
        length = atoi(input_length); //set length = casted input_length
        break;
      }
      // otherwise dont set anything
      else {
        break;
      }
    }
  }
  
  //create the bitVector and vector array on heap
  BitVector *v = bv_create(length);

  //this will find the primes
  sieve(v);

  // error check the getopt
  if (argc == 1) {
    return -1;
  }

  //if bool T is toggled by getopt
  if (specPrimes) {
    //start the printing of primes and special primes
    primes(length, v);
  }

  return 0;
}
