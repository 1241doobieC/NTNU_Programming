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
// void show_plane(int32_t, int32_t, int32_t, int32_t);
// void project(double *x, double *y, double *z, int32_t a, int32_t b, int32_t c, int32_t d);
int main()
{
  int32_t a=0, b=0, c=0, d=0;
  printf("Please enter the plane: " );
  scanf("%d %d %d %d", &a, &b, &c, &d );
  if(d != 0 && (a == 0 && b == 0 && c == 0))
  {
    printf("%d = 0 ", d );
    printf("Wrong Input.\n");
  }
  else if (a == 0 && b == 0 && c == 0 && d == 0)
  {
    printf("0 = 0\n");
    printf("Invalid Input.\n");
  }
  else
  {
    printf("The plane is ");
    show_plane(a,b,c,d);
    double xx=0, yy=0, zz=0;
    printf("Please enter the point: ");
    scanf("%lf %lf %lf", &xx, &yy, &zz);
    double *x=&xx, *y=&yy, *z=&zz;
    project(x, y, z, a, b, c, d);
    printf("The projection is (%.2lf , %.2lf, %.2lf)\n",*x, *y , *z);
  }

  return 0;
}
//
// void show_plane(int32_t a, int32_t b, int32_t c, int32_t d)
// {
// //================================
//   if(a == 0)
//   {
//     // Do nothing
//   }
//   else if(a == 1)
//   {
//     printf("x ");
//   }
//   else if(a == -1)
//   {
//     printf("-x ");
//   }
//   else if (a != 1)
//   {
//     printf("%dx", a);
//   }
//   /*
//     **Finished**
//   */
// //================================
//   if(b == 0 && a == 0)
//   {
//     // Do nothing
//   }
//   else if (b == -1 && a != 0)
//   {
//     printf(" + (-y)");
//   }
//   else if (b < 0 && a != 0)
//   {
//     printf(" + (%d)y", b);
//   }
//   else if (b < 0 && a == 0 && b == -1)
//   {
//     printf("(-y) ");
//   }
//   else if (b < 0 && a == 0)
//   {
//     printf("(%d)y", b);
//   }
//   else if (b > 0 && a == 0 && b != 1)
//   {
//     printf("%dy", b);
//   }
//   else if (b == 1 && a == 0)
//   {
//     printf("y");
//   }
//   else if (b == 0 && a != 0)
//   {
//
//   }
//   else if (b != 1 && a!= 0)// b>0 && a !=0
//   {
//     printf(" + %dy", b);
//   }
//   else if (b == 1 && a != 0)
//   {
//     printf("+ y ");
//   }
//   //================================
//   if(c == 0 && b == 0 && a == 0)
//   {
//     // Do nothing
//   }
//   else if (c < 0 && (a != 0 || b != 0))
//   {
//     printf(" + (%d)z", c);
//   }
//   else if (c > 0 && (a != 0 || b != 0))
//   {
//     printf(" + %dz", c);
//   }
//   else if (c < 0 && (a == 0 && b == 0))
//   {
//     printf("(%d)z", c);
//   }
//   else if (c > 0 && (a == 0 && b == 0))
//   {
//     printf("%dz", c);
//   }
//   //================================
// /*  {
//     // Do nothing
//   }
//   else if (d < 0 && (a != 0 || b != 0 || c !=0))
//   {
//     printf(" + (%d)", d);
//   }
//   else if (d > 0 && (a != 0 || b != 0 || c !=0))
//   {
//     printf(" + %d", d);
//   }
//   else
//   printf(" %d", d); */
//   if (d > 0)
//   {
//     printf(" + %d", d);
//   }
//   else if(d < 0)
//   {
//     printf("+ (%d)", d);
//   }
//   else
//   {
//     //Do nothing
//   }
//   //================================
//   if (a == 0 && b == 0 && c == 0 && d == 0)
//   {
//     printf("0 = 0\n");
//   }
//   else printf(" = 0 \n");
// }
// void project(double *x, double *y, double *z, int32_t a, int32_t b, int32_t c, int32_t d)
// {
//   double remain = 0 - d;
//   double t = (remain - (a * (*x)) - (b * (*y)) - (c * (*z))) / ((a * a) + (b * b) + (c * c));
//   *x = *x + (a * t);
//   *y = *y + (b * t);
//   *z = *z + (c * t);
//   return;
// }
