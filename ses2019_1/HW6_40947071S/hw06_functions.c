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

//HW0602
void show_result()
{
  printf("Result: ");
}

//HW0603
void rotate(double *x, double *y, double theta)
{
  double hhh = (theta / 180) * M_PI;  //radian
  double x_p = cos(hhh) * (*x) - (sin(hhh) * (*y));
  double y_p = sin(hhh) * (*x) + (cos(hhh) * (*y));
  if (y_p < 0 && y_p > -0.00005)
  {
    y_p = 0;
  }
  if (x_p < 0 && x_p > -0.00005)
  {
    x_p = 0;
  }
  printf("%.3f %.3f \n",x_p , y_p );
  return;
}

//HW0604
void show_plane(int32_t aaa, int32_t bbb, int32_t ccc, int32_t ddd)
{
//================================
  if(aaa == 0)
  {
    // Do nothing
  }
  else if(aaa == 1)
  {
    printf("x ");
  }
  else if(aaa == -1)
  {
    printf("-x ");
  }
  else if (aaa != 1)
  {
    printf("%dx", aaa);
  }
  /*
    **Finished**
  */
//================================
  if(bbb == 0 && aaa == 0)
  {
    // Do nothing
  }
  else if (bbb == -1 && aaa != 0)
  {
    printf(" + (-y)");
  }
  else if (bbb < 0 && aaa != 0)
  {
    printf(" + (%d)y", bbb);
  }
  else if (bbb < 0 && aaa == 0 && bbb == -1)
  {
    printf("(-y) ");
  }
  else if (bbb < 0 && aaa == 0)
  {
    printf("(%d)y", bbb);
  }
  else if (bbb > 0 && aaa == 0 && bbb != 1)
  {
    printf("%dy", bbb);
  }
  else if (bbb == 1 && aaa == 0)
  {
    printf("y");
  }
  else if (bbb == 0 && aaa != 0)
  {

  }
  else if (bbb != 1 && aaa!= 0)// b>0 && a !=0
  {
    printf(" + %dy", bbb);
  }
  else if (bbb == 1 && aaa != 0)
  {
    printf("+ y ");
  }
  //================================
  if(ccc == 0 && bbb == 0 && aaa == 0)
  {
    // Do nothing
  }
  else if (ccc < 0 && (aaa != 0 || bbb != 0))
  {
    printf(" + (%d)z", ccc);
  }
  else if (ccc > 0 && (aaa != 0 || bbb != 0))
  {
    printf(" + %dz", ccc);
  }
  else if (ccc < 0 && (aaa == 0 && bbb == 0))
  {
    printf("(%d)z", ccc);
  }
  else if (ccc > 0 && (aaa == 0 && bbb == 0))
  {
    printf("%dz", ccc);
  }
  //================================
  if (ddd > 0)
  {
    printf(" + %d", ddd);
  }
  else if(ddd < 0)
  {
    printf("+ (%d)", ddd);
  }
  else
  {
    //Do nothing
  }
  //================================
  if (aaa == 0 && bbb == 0 && ccc == 0 && ddd == 0)
  {
    printf("0 = 0\n");
  }
  else printf(" = 0 \n");
}
void project(double *x, double *y, double *z, int32_t a, int32_t b, int32_t c, int32_t d)
{
  double remain = 0 - d;
  double t = (remain - (a * (*x)) - (b * (*y)) - (c * (*z))) / ((a * a) + (b * b) + (c * c));
  *x = *x + (a * t);
  *y = *y + (b * t);
  *z = *z + (c * t);
  return;
}

//HW0605
int32_t check_valid(const uint8_t player[13])
{
  for(int32_t i = 0;i < 13;i++)
  {
      for(int32_t j = i + 1;j < 13;j++)
      {
          if(player[i] == player[j])
          {
              return 0;
          }
      }
      if(player[i] > 52 || player[i] < 1)
      {
          return 0;
      }
  }
  return 1;
}
void print_card(const uint8_t player[13])
{
    for(int32_t i = 0;i < 13;i++)
    {
        printf("%2d ",player[i]);
    }
    printf("\n");
}

int32_t sort_card(uint8_t player[13], int32_t ( * compare)( int32_t a, int32_t b ))
{
  int32_t tmp = 0;
  for(int32_t i = 0 ;i < 13; i++)
  {
      for(int32_t j = i + 1; j < 13; j++)
      {
        if(compare(player[i],player[j]))
        {
          tmp = player[i];
          player[i] = player[j];
          player[j] = tmp;
        }
      }
  }
}
int32_t func01(int32_t a,int32_t b)
{
    int32_t a_value = (a-1) % 13;
    int32_t b_value = (b-1) % 13;
    int32_t a_suit = (a-1) / 13;
    int32_t b_suit = (b-1) / 13;
    int32_t new_a = 0;
    int32_t new_b = 0;

    if(a_value == 0)a_value = 13;
    if(b_value == 0)b_value = 13;

    a_suit = 3 - a_suit;
    b_suit = 3 - b_suit;

    new_a = a_value * 10 + a_suit;
    new_b = b_value * 10 + b_suit;

    if(new_a < new_b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int32_t func02(int32_t a,int32_t b)
{
    int32_t a_value = (a-1) % 13;
    int32_t b_value = (b-1) % 13;
    int32_t a_suit = (a-1) / 13;
    int32_t b_suit = (b-1) / 13;
    int32_t new_a = 0;
    int32_t new_b = 0;

    if(a_value == 0)a_value = 13;
    if(b_value == 0)b_value = 13;
    if(a_value == 1)a_value = 14;
    if(b_value == 1)b_value = 14;

    a_suit = 3 - a_suit;
    b_suit = 3 - b_suit;

    new_a = a_value * 10 + a_suit;
    new_b = b_value * 10 + b_suit;

    if(new_a < new_b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int32_t func03(int32_t a,int32_t b)
{
    int32_t a_value = (a-1) % 13;
    int32_t b_value = (b-1) % 13;
    int32_t a_suit = (a-1) / 13;
    int32_t b_suit = (b-1) / 13;
    int32_t new_a = 0;
    int32_t new_b = 0;

    if(a_value == 0)a_value = 13;
    if(b_value == 0)b_value = 13;

    a_suit = 3 - a_suit;
    b_suit = 3 - b_suit;

    new_a = a_suit * 13 + a_value + 1;
    new_b = b_suit * 13 + b_value + 1;

    if(new_a < new_b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
