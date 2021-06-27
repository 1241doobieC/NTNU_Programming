#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include"check_file.h"

int main(){

  int32_t num=0;
  printf("Please enter an integer:");
  scanf("%d", &num );
// Check Validity
  if (num >3000 || num < 0) {
    printf("Invalid Input. \n" );
    return 0;
  }

  show_roman(num);

  return 0;
}
