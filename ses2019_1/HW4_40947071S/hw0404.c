#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include"check_file.h"
// double equivalent_r(double, double);
int main()
{
  double r=0, n=0;
  double ans=0;
  // Check Validity
  printf("Please enter the resistance(1-100): ");
  scanf(" %le", &r);
  if (r<1 || r>100) {
    printf("Invalid Input! \n");
    return 0;
  }
  printf("Please enter n(1-100): ");
  scanf("%le",&n );
  if (n<1 || n>100) {
    printf("Invalid Input! \n");
    return 0;
  }

  printf("Ans: %.30f \n", equivalent_r(r,n));
  return 0;
}
