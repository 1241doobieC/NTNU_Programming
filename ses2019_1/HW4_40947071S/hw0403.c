#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include"check_file.h"

int main()
{
  double k=0;
  printf("k-th order Taylor polynomial for e\n");
  printf("Please enter k: " );
  scanf("%lf", &k);
  if (k<0) {
    printf("Invalid Input!\n");
    return 0;
  }

  printf("e: %.20f \n",trans(k) );
  return 0;
}
