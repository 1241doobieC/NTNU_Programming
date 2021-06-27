#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include <math.h>
#define FALSE 0
#define TRUE 1
#include "check_funs.h"

// void rotate(double *a, double *b, double theta);

int main()
{
  double a=0, b=0;
  double theta=0;
  printf("Please enter a point:");
  scanf("%lf %lf", &a, &b );
  double *x=&a, *y=&b;
  printf("Please enter theta(0-360): ");
  scanf(" %lf",  &theta);
  while (theta > 360 || theta < 0)
  {
    printf("Invalid Input.\n");
    printf("Please enter theta(0-360): ");
    scanf(" %lf",  &theta);
  }
  theta = 360 - theta;
  rotate(x, y, theta);
  //printf("\n");
  return 0;
}

// void rotate(double *x, double *y, double theta)
// {
//   double hhh = (theta / 180) * M_PI;  //radian
//   double x_p = cos(hhh) * (*x) - (sin(hhh) * (*y));
//   double y_p = sin(hhh) * (*x) + (cos(hhh) * (*y));
//   if (y_p < 0 && y_p > -0.00005)
//   {
//     y_p = 0;
//   }
//   if (x_p < 0 && x_p > -0.00005)
//   {
//     x_p = 0;
//   }
//   printf("%.3f %.3f \n",x_p , y_p );
//   return;
// }
