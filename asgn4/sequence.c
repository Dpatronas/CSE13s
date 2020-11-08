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

//function to find the fibs
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

//function to convert int to character and perform
//base change on the decimal # input to desired base input
//fills the string from left to right
char* buildstring(char str[], int from_decimal, int to_base) 
{ 
    int index = 0;  // Initialize index of result 
  
    // dividing number it by base and taking remainder 
    while (from_decimal > 0) 
    { 
      //store the decimal MOD base
      int temp = from_decimal % to_base;

      //check if this char is a digit char number
      if (temp >= 0 && temp <= 9) {
        //fill string index with value
        str[index++] = (char)(temp + '0'); 
      }
      //otherwise its hexa
      else {
        //fill string index with letter
        str[index++] = (char)(temp - 10 + 'A'); 
      }
      //divide the decimal by the new base and continue
      from_decimal /= to_base; 
    } 
    //add ghe null terminating char
    str[index] = '\0'; 
  
    return str; 
}

//function to determine if character string is pally
bool isPalindrome(char str[]) {
  //assume true
  bool res = 1;
  //the end of the string excluding null term
  int end = strlen(str) -1;

  //test half the string comparing values on each end
  for (int start = 0; start <= (strlen(str)/2); start++) {

    //if start != end element
    if (str[start] != str[(end)]) {
      //if no match, set to false
      res = 0;
    }
    //decrement the end element
    end--;
  }
  //return the bool
  return res;
}

//print the character string
void printstring( char str[]) {
  int sleng = strlen(str);
  for (int i = 0; i < sleng; i++) {
    printf("%c", str[i]);
  }
  printf("\n");

}

void test_pali( int length, BitVector *v) {
  //10 cstrings allocated for base 2, base 9, base 10, and base 10+16 = 26=(P)
  char *str_bin = (char *)malloc(10 * sizeof(char));
  char *str_nine = (char *)malloc(10 * sizeof(char));
  char *str_dec = (char *)malloc(10 * sizeof(char));
  char *str_Patr = (char *)malloc(10 * sizeof(char));

  //Primes start at 2
  int i = 2;

  printf("Base  2\n---- --\n");
  //binary palindrome test
  while ( i < length ) {
    if (bv_get_bit(v,i) == 1) {

      //make the char string using binary
      buildstring(str_bin, i, 2);

      //check if its a palindrome 
      if ( isPalindrome(str_bin) ) {
        printf("%d = ");
        printstring(str_bin);
      }
    }
    i++; 
  }

  printf("\nBase  9\n---- --\n");
  //reset the index
  i = 2;
  //base nine palindrome test
  while ( i < length ) {
    if (bv_get_bit(v,i) == 1) {

      //make the char string using base nine
      buildstring(str_nine, i, 9);

      //check if its a palindrome 
      if ( isPalindrome(str_nine) ) {
        printf("%d = ");
        printstring(str_nine);
      }
    }
    i++; 
  }

  //reset the index
  i = 2;
  printf("\nBase 10\n---- --\n");
  //base decimal palindrome test
  while ( i < length ) {
    if (bv_get_bit(v,i) == 1) {

      //make the char string using decimal
      buildstring(str_dec, i, 10);

      //check if its a palindrome 
      if ( isPalindrome(str_dec) ) {
        printf("%d = ");
        printstring(str_dec);
      }
    }
    i++; 
  }

  //reset the index
  i = 2;
  printf("\nBase 26\n---- --\n");
  //Last name base palindrome test ((P)16+10=26)
  while ( i < length ) {
    if (bv_get_bit(v,i) == 1) {

      //make the string for last name base
      buildstring(str_Patr, i, 26);

      //check if its a palindrome 
      if ( isPalindrome(str_Patr) ) {
        printstring(str_Patr);
      }
    }
    i++; 
  }
  
  //clean up the heap
  free(str_bin);
  free(str_nine);
  free(str_dec);
  free(str_Patr);
  bv_delete(v);

}

//Create the Bitvector
//Sieve the BitVector for primes
//Find the special primes
void primes( int length, BitVector *v ) {

  // the first 3 fibonacci numbers are excluded (0,1,1) since primes start at 2
  //declare and initalize values to 0
  int fib[20] = {0};

  //populate the fib array
  for ( int i = 0; i < 20; i++) {
    fib[i] = fibonacci(i, fib[i-1], fib[i-2]);
  }

  // Similar line of logic for lucas primes (excluding the initial 1)
  int luc[20] = {2,3,4,7,11,18,29,47,76,123,199,322,521,843,1364,2207,3571,5778,9349,15127};

  //the start of our loop for prime numbers within Bitvector
  int i =2;

  while (i < length) {
    if (bv_get_bit(v,i) == 1 ) {
      printf("%d: prime", i);
      
      //cannot be <= 1 since 2^1=1 
      //extra included for variable length tests
      for (int m = 0; m < 15; m++ ) {
        if (mersenne(m) == i ) {
          printf(", mersenne");
          m++;
        }
      }

      //scan 20 lucas numbers
      for ( int l = 0; l < 20; l++ ) {
        if ( luc[l] == i) {
          printf(", lucas");
          l++;
        }
      }

      //scan 20 fibonacci numbers
      for ( int f = 0; f < 20; f++ ) {
        if ( fib[f] == i) {
          printf(", fibonacci");
          f++;
        }
      }
      printf("\n");
    }
    i++; //increment the index
  }

  //clean up the heap
  bv_delete(v);

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

  if (palnPrimes) {
    //print the palindrome of different based primes
    test_pali(length, v);
  }

  return 0;
}
