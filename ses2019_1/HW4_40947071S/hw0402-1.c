#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include"check_file.h"

int main()
{
  int32_t num=0;
  printf("Please enter the disk number: ");
  scanf("%d", &num );
  if (num > 20 || num < 0)
  {
  printf("Invalid Input.\n");
  return 0;
  }
  //printf("%d\n", num );
  move(num, '1', '2', '3');
  return 0;
}
