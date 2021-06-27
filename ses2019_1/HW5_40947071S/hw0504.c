#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include"hw05_CHECK_FILES.h"
// void trans_into_regre(double a[][2], int32_t);

int main()
{
  int point_num=0;
  printf("Please enter the point number:");
  scanf(" %d", &point_num);
  double point[point_num][2];
  for (int32_t i = 0; i < point_num; i++)
  {
    printf("Please enter point %d: ", i+1);
    scanf("%lf %lf", &point[i][0] , &point[i][1] );
  }

  trans_into_regre(point, point_num);

  return 0;
}
// void trans_into_regre(double point[][2], int32_t point_num)
// {
//   double t=0, y=0, b1=0, b0=0;  //First
//   double tixyi=0, tixti=0, yixyi=0;
//   double t1_t[point_num], y1_y[point_num] ;
//   for (int32_t i = 0; i < point_num; i++)
//   {
//     t1_t[i]=0;
//     y1_y[i]=0;
//   }
//   for (int32_t i = 0; i < point_num; i++)
//   {
//     t += point[i][0];
//   }
//   for (size_t i = 0; i < point_num; i++)
//   {
//     y += point[i][1];
//   }
//   y = y / point_num;
//   t = t / point_num;
//
//   for (int32_t i = 0; i < point_num; i++)
//   {
//     t1_t[i] = point[i][0] - t;
//     y1_y[i] = point[i][1] - y;
//   }
//   //Ti * Yi
//   for (int32_t i = 0; i < point_num; i++)
//   {
//     tixyi += (t1_t[i] * y1_y[i]);
//     tixti += (t1_t[i] * t1_t[i]);
//     yixyi += (y1_y[i] * y1_y[i]);
//   }
//   // printf("Ti * Yi ==> %.2lf\n", tixyi );
//   // printf("Ti * Ti ==> %.2lf\n", tixti );
//   // printf("Yi * Yi ==> %.2lf\n", yixyi );
//   b1 = tixyi / tixti ;
//   // printf("b1: %.2lf, t:%.2lf \n",b1, t);
//   b0 = y - (b1 * t);
//   printf("Regression Equation: y = %.2lf x + %.2lf\n", b1, b0 );
// }
