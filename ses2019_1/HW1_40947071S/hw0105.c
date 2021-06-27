#include <stdio.h>
#include <stdint.h>

int main(){

  int32_t num;
  printf("Please enter an integer:");
  scanf("%d", &num );
  printf("%08x \n", num);

  
  return 0;
}
