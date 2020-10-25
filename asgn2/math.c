#include <getopt.h>
#include <math.h>
#include <stdio.h>

#define OPTIONS "sctea :"

#define EPSILON 0.00000000001
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
// Calculates: base^power
double Pow(double base, int power) {
  double total = 1;
  for (int i = 0; i < power; i++) {
    total *= base;
  }
  return total;
}

// Calculates: x!
double Fact(double x) {
  if ((x == 0) || (x == 1)) {
    return 1;
  } else {
    double sum = 1;
    while (x > 1) {
      sum *= x;
      x--;
    }
    return sum;
  }
}

// Finds the linear approximation of exponential number
// Using the MacLaurin Series
//(x^0/0! + x^1/1! + x^2/2! + x^3/3! + ...)
double Exp(double x) {
  // 0th term: x^0/1 = 1
  if (x == 0) {
    return 1;
  }
  // nth term > 0th term
  else {
    int n = 2;             // n = term (we start at 2nd)
    double result = 1 + x; // Account for 0th and 1st term initially
    double difference = 1; // set diff > 1 to proc the while loop

    // while ( |(n) - (n-1)| > threshold ), continue adding terms to increase
    // precision
    while (difference > EPSILON) {
      double first = result; // store the value before calculation (n-1)
      result += (Pow(x, n) / Fact(n)); // calulate the current term value
      double second = result;          // store the value after calculating (n)
      difference =
          (fabs(first - second)); // determine the difference between two terms
      n++;                        // incremenet the n term
    }
    return result;
  }
}

// Horners Equation
double Sin(double x) {
  double numerator = 0;
  double denominator = 0;
  double x_Sqr = Pow(x, 2);
  numerator =
      (x * ((((x_Sqr * (52785432 - (479249 * x_Sqr))) - 1640635920) * x_Sqr) +
            11511339840));

  denominator = ((((((18361 * x_Sqr) + 3177720) * x_Sqr) + 277920720) * x_Sqr) +
                 11511339840);
  return numerator / denominator;
}

// Horners Equation
double Cos(double x) {
  double numerator = 0;
  double denominator = 0;
  double x_Sqr = Pow(x, 2);

  numerator =
      ((x_Sqr * (1075032 - (14615 * x_Sqr)) - 18471600) * x_Sqr) + 39251520;
  denominator = ((((127 * x_Sqr) + 1154160) * x_Sqr) + 39251520);

  return numerator / denominator;
}
double Tan(double x) { return sin(x) / cos(x); }

// test exponential function
void exp_test() {
  printf("%s \t%s \t%s \t%s \n", "x     ", " Exp    ", " Library",
         " Difference");
  printf("%s \t%s \t%s \t%s \n", "-", " ---", "         -------",
         " ----------");

  for (double i = 0; i < 9; i += 0.1) {
    // difference = my_Function - math_Function
    double diff = (Exp(i) - exp(i));
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", i, Exp(i), exp(i), diff);
  }
  printf("\n");
}

// test sin function
void sin_test() {
  printf("%s \t%s \t%s \t%s \n", "x     ", " Sin    ", " Library",
         " Difference");
  printf("%s \t%s \t%s \t%s \n", "-", " ---", "         -------",
         " ----------");

  for (double i = -2 * M_PI; i <= (2 * M_PI); i += M_PI / 16) { //[-2pi,2pi)
    // difference = my_Function - math_Function
    double diff = (Sin(i) - sin(i));
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", i, Sin(i), sin(i), diff);
  }
  printf("\n");
}

// test cos function
void cos_test() {
  printf("%s \t%s \t%s \t%s \n", "x     ", " Cos    ", " Library",
         " Difference");
  printf("%s \t%s \t%s \t%s \n", "-", " ---", "         -------",
         " ----------");

  for (double i = -2 * M_PI; i <= (2 * M_PI); i += M_PI / 16) { //[-2pi,2pi)
    // difference = my_Function - math_Function
    double diff = (Cos(i) - cos(i));
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", i, Cos(i), cos(i), diff);
  }
  printf("\n");
}

// test tan function
void tan_test() {

  printf("%s \t%s \t%s \t%s \n", "x     ", " Tan    ", " Library",
         " Difference");
  printf("%s \t%s \t%s \t%s \n", "-", " ---", "         -------",
         " ----------");

  for (double i = -M_PI / 3; i <= M_PI / 3; i += M_PI / 16) {
    // difference = my_Function - math_Function
    double diff = (Tan(i) - tan(i));
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", i, Tan(i), tan(i), diff);
  }
  printf("\n");
}

int main(int argc, char **argv) {
  int c = 0;
  while ((c = getopt(argc, argv, OPTIONS)) != -1) {

    switch (c) {

    // test the sin
    case 's':
      sin_test();
      break;
    // test the cos
    case 'c':
      cos_test();
      break;
    // test the tan
    case 't':
      tan_test();
      break;
    // test the cos
    case 'e':
      exp_test();
      break;
    // test all
    case 'a':
      sin_test();
      cos_test();
      tan_test();
      exp_test();
      break;
    }
  }
  if (argc == 1) {
    puts("Error: no arguments supplied!");
    return -1;
  }
  return 0;
}
