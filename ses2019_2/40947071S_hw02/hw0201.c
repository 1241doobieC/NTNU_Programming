#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "mixed.h"
#define TRUE (1)
#define FALSE (0)
#define INVALID (-1)
#define VALID (0)

int main(){
  sMixedNumber test_01 = {0};
  sMixedNumber test_02 = {0};

  sMixedNumber a1 = {0, -1, 2};
  sMixedNumber a2 = {1, 2, 3};
  int32_t a = a1.number;
  int32_t b = a1.numerator;
  int32_t c = a1.denominator;
  int32_t x = a2.number, y = a2.numerator, z = a2.denominator;
  int32_t x_part = mixed_set(&test_01, a, b, c);
  int32_t y_part = mixed_set(&test_02, x, y, z);
  if (x_part == INVALID || y_part == INVALID) printf("Invalid Input.\n");
  else
  {
    mixed_print(test_01);
    mixed_print(test_02);
    sMixedNumber final ={0};

    printf("Add: \n");
    mixed_add(&final,test_01, test_02);
    mixed_print(final);

    printf("Sub: \n");
    mixed_sub( &final,test_01, test_02);
    mixed_print(final);

    printf("Mul: \n");
    mixed_mul( &final,test_01, test_02);
    mixed_print(final);

    printf("Div: \n");
    mixed_div( &final,test_01, test_02);
    mixed_print(final);
  }
  return 0;
}
