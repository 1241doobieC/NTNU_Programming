#include <stdio.h>
#include <stdint.h>

int main(){

  int32_t num;
  int32_t sum;

  int32_t a;
  int32_t b;
  int32_t c;
  int32_t d;
  int32_t e;

  printf("Please enter a 5-digits integer: ");
  scanf("%d", &num );

  a = num/10000;
  b = (num - a * 10000) / 1000;
  c = (num - a * 10000 - b * 1000) / 100;
  d = (num - a * 10000 - b * 1000 - c * 100) / 10;
  e = (num - a * 10000 - b * 1000 - c * 100 - d * 10);
  sum = a * b * c * d * e;
  printf("Result: %d\n", sum );
  return 0;
}
