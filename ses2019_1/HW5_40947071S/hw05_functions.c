#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include"hw05_CHECK_FILES.h"

//HW0501
void sort_array(int32_t array[], int32_t array_size)
{
  int32_t even=0, odd=0, num=0;
  int32_t temp[array_size];
  for (size_t i = 0; i < array_size; i++)
  {
    temp[i]=0;
  }
  for (size_t i = 0; i < array_size; i++)
  {
    if (array[i] %2 !=0)
    {
      temp[odd]= array[i];
      odd++;
    }
    else
    {
      even++;
    }
  }
  for (size_t i = 0; i < odd; i++)
  {
    for (size_t j = 0; j < i; j++)
    {
      if (temp[i]<temp[j])
      {
        int32_t abc=temp[i];
        temp[i]=temp[j];
        temp[j]=abc;
      }
    }
  }
  num = odd;
  for (size_t i = 0; i < array_size; i++)
  {
    if (array[i] %2 ==0)
    {
      temp[num]= array[i];
      num++;
    }
  }
  for (size_t i = odd; i < array_size; i++)
  {
    for (size_t j = odd; j < i; j++)
    {
      if (temp[i]>temp[j])
      {
        int32_t abc=temp[i];
        temp[i]=temp[j];
        temp[j]=abc;
      }
    }
  }
  for (size_t i = 0; i < array_size; i++)
  {
    array[i]=temp[i];
  }
  return;
}
//====================================================
//HW0502
int32_t calculate_matrix(int32_t matrix[4][4])
{
  int32_t ans=0;
  int32_t m01[3][3], m02[3][3], m03[3][3], m04[3][3];
  for (size_t i = 0; i < 4; i++)  //m01
  {
      for (size_t j = 0; j < 4; j++)
      {
        if (j==3) break;
        m01[i][j]=matrix[i+1][j+1];
      }
  }
  //TEST
  // for (size_t i = 0; i < 3; i++)
  // {
  //   for (size_t j = 0; j < 3; j++)
  //   {
  //     printf("%d ",m01[i][j] );
  //   }
  //   printf("\n");
  // }
  // printf("\n");
  int32_t a=1, b=0;
  for (size_t i = 0; i < 3; i++) //m02
  {
    for (size_t j = 0; j < 3; j++)
    {
      if(b==1) b=2;
      m02[i][j]=matrix[a][b];
      b++;
    }
    b=0;
    a++;
  }
  //TEST02
  // for (size_t i = 0; i < 3; i++)
  // {
  //   for (size_t j = 0; j < 3; j++)
  //   {
  //     printf("%d ",m02[i][j] );
  //   }
  //   printf("\n");
  // }
  // printf("\n");
  a=1;b=0;
  for (size_t i = 0; i < 3; i++) //m03
  {
    for (size_t j = 0; j < 3; j++)
    {
      if(b==2) b=3;
      m03[i][j]=matrix[a][b];
      b++;
    }
    b=0;
    a++;
  }
  //TEST03
  // for (size_t i = 0; i < 3; i++)
  // {
  //   for (size_t j = 0; j < 3; j++)
  //   {
  //     printf("%d ",m03[i][j] );
  //   }
  //   printf("\n");
  // }
  // printf("\n");
  for (size_t i = 0; i < 3; i++)  //m04
  {
      for (size_t j = 0; j < 3; j++)
      {
        m04[i][j]=matrix[i+1][j];
      }
  }
  //TEST
  // for (size_t i = 0; i < 3; i++)
  // {
  //   for (size_t j = 0; j < 3; j++)
  //   {
  //     printf("%d ",m04[i][j] );
  //   }
  //   printf("\n");
  // }
  // printf("\n");
  ans = matrix[0][0] * matrix_3x3(m01) -
        matrix[0][1] * matrix_3x3(m02) +
        matrix[0][2] * matrix_3x3(m03) -
        matrix[0][3] * matrix_3x3(m04) ;
  return ans;
}
int32_t matrix_3x3(int32_t mat[3][3])
{
  int32_t value=0;
  int32_t b01[2][2], b02[2][2], b03[2][2];
  for (size_t i = 0; i < 2; i++) //b01
  {
    for (size_t j = 0; j < 2; j++)
    {
      b01[i][j]=mat[i+1][j+1];
    }
  }
  int32_t a=1, b=0;
  for (size_t i = 0; i < 2; i++)  //b02
  {
    for (size_t j = 0; j < 2; j++)
    {
      b02[i][j]=mat[a][b];
      b=2;
    }
    b=0;
    a++;
  }
  a=1,b=0;
  for (size_t i = 0; i < 2; i++)  //b03
  {
    for (size_t j = 0; j < 2; j++)
    {
      b03[i][j]=mat[a][b];
      b++;
    }
    b=0;
    a++;
  }
  value=mat[0][0]* matrix_2x2(b01)-
        mat[0][1]* matrix_2x2(b02)+
        mat[0][2]* matrix_2x2(b03);
  return value;
}
int32_t matrix_2x2(int32_t c01[2][2])
{
  int32_t trash=0;
  return (c01[0][0] * c01[1][1]) - (c01[1][0] * c01[0][1]);
}
//====================================================
//HW0503
void printf_p1_array(int32_t p1[], size_t size)
{
  int32_t coeiecient_numbers = size-1;
  int32_t p1_degree= size - 1;
  if(p1[0]>0 && p1[0]!=1)  //First coeiecient
  {
    printf("%dx^%d", p1[0],coeiecient_numbers);
  }
  else if (p1[0]>0 && p1[0]==1)
  {
    printf("x^%d",coeiecient_numbers);
  }
  else if (p1[0]<0 && p1[0]!=(-1))
  {
    printf("%dx^%d", p1[0],coeiecient_numbers);
  }
  else if (p1[0]<0 && p1[0]==(-1))
  {
    printf("-x^%d", coeiecient_numbers);
  }
  coeiecient_numbers=coeiecient_numbers-1;
//===============================================
//Second Starts from here
  for (size_t i = 1; i <= p1_degree+1; i++)
  {
    if (coeiecient_numbers>1)
    {
      if (p1[i]>0 && p1[i]!=1)
      {
        printf(" + %dx^%d", p1[i],coeiecient_numbers);
      }
      else if (p1[i]>0 && p1[i]==1)
      {
        printf(" + x^%d",coeiecient_numbers);
      }
      else if(p1[i]<0 && p1[i]!=(-1))
      {
        printf(" + (%d)x^%d", p1[i],coeiecient_numbers);
      }
      else if(p1[i]<0 && p1[i]==(-1))
      {
        printf(" + (-x)^%d",coeiecient_numbers);
      }
      else if (p1[i]==0)
      {
        //Do nothing
      }
    }
    else if (coeiecient_numbers==1)
    {
      if (p1[p1_degree-1]!=1 &&p1[p1_degree-1]>0)
      {
        printf(" + %dx", p1[p1_degree-1]);
      }
      else if(p1[p1_degree-1]==1)
      {
        printf(" + x");
      }
      else if(p1[p1_degree-1]==(-1))
      {
        printf("- x");
      }
      else if (p1[p1_degree-1]!=(-1) &&p1[p1_degree-1]<0)
      {
        printf(" + (%d)x", p1[p1_degree-1]);
      }
      else if (p1[p1_degree-1]==0)
      {
        //Do nothing
      }
    }
    else if (coeiecient_numbers==0) //Constant number
    {
      if (p1[p1_degree]>0 && p1[p1_degree]!=1)
      {
        printf(" + %d \n", p1[p1_degree] );
      }
      else if (p1[p1_degree]==1)
      {
        printf(" + 1 \n");
      }
      else if (p1[p1_degree]==(-1))
      {
        printf(" - 1 \n");
      }
      else if (p1[p1_degree]!=(-1) && p1[p1_degree]<0)
      {
        printf(" + (%d) \n", p1[p1_degree] );
      }
      else if (p1[p1_degree]==0)
      {
        printf("\n");  //Do nothing
      }
    }
    coeiecient_numbers--;
  }
}
void printf_p2_array(int32_t p2[], size_t size)
{
  int32_t coeiecient_numbers = size-1;
  int32_t p2_degree= size - 1;
  if(p2[0]>0 && p2[0]!=1)  //First coeiecient
  {
    printf("%dx^%d", p2[0],coeiecient_numbers);
  }
  else if (p2[0]>0 && p2[0]==1)
  {
    printf("x^%d",coeiecient_numbers);
  }
  else if (p2[0]<0 && p2[0]!=(-1))
  {
    printf("%dx^%d", p2[0],coeiecient_numbers);
  }
  else if (p2[0]<0 && p2[0]==(-1))
  {
    printf("-x^%d", coeiecient_numbers);
  }
  coeiecient_numbers=coeiecient_numbers-1;
//===============================================
//Second Starts from here
  for (size_t i = 1; i <= p2_degree+1; i++)
  {
    if (coeiecient_numbers>1)
    {
      if (p2[i]>0 && p2[i]!=1)
      {
        if (p2[0] == 0)
        {
          printf("%dx^%d", p2[i],coeiecient_numbers);
        }
        printf(" + %dx^%d", p2[i],coeiecient_numbers);
      }
      else if (p2[i]>0 && p2[i]==1)
      {
        if (p2[0] == 0)
        {
          printf("x^%d",coeiecient_numbers);
        }
        printf(" + x^%d",coeiecient_numbers);
      }
      else if(p2[i]<0 && p2[i]!=(-1))
      {
        if (p2[0] == 0)
        {
          printf("(%d)x^%d", p2[i],coeiecient_numbers);
        }
        printf(" + (%d)x^%d", p2[i],coeiecient_numbers);
      }
      else if(p2[i]<0 && p2[i]==(-1))
      {
        if (p2[0] == 0)
        {
          printf("(-x)^%d",coeiecient_numbers);
        }
        printf(" + (-x)^%d",coeiecient_numbers);
      }
      else if (p2[i]==0)
      {
        //Do nothing
      }
    }
    else if (coeiecient_numbers==1)
    {
      if (p2[p2_degree-1]!=1 &&p2[p2_degree-1]>0)
      {
        printf(" + %dx", p2[p2_degree-1]);
      }
      else if(p2[p2_degree-1]==1)
      {
        printf(" + x");
      }
      else if(p2[p2_degree-1]==(-1))
      {
        printf(" - x");
      }
      else if (p2[p2_degree-1]!=(-1) &&p2[p2_degree-1]<0)
      {
        printf(" + (%d)x", p2[p2_degree-1]);
      }
      else if (p2[p2_degree-1]==0)
      {
        //Do nothing
      }
    }
    else if (coeiecient_numbers==0) //Constant number
    {
      if (p2[p2_degree]>0 && p2[p2_degree]!=1)
      {
        printf(" + %d ", p2[p2_degree] );
      }
      else if (p2[p2_degree]==1)
      {
        printf(" + 1 ");
      }
      else if (p2[p2_degree]==(-1))
      {
        printf(" - 1 ");
      }
      else if (p2[p2_degree]!=(-1) && p2[p2_degree]<0)
      {
        printf(" + (%d) ", p2[p2_degree] );
      }
      else if (p2[p2_degree]==0)
      {
        //printf("");  //Do nothing
      }
    }
    coeiecient_numbers--;
  }

  int32_t check=0;
  for (size_t i = 0; i < p2_degree; i++)
  {
    if (p2[i] == 0)
    {
      check++;
    }
  }
  if (check == (size-1))
  {
    printf("0");
  }
  printf("\n");
}
void calculate_sum(int32_t p1[], int32_t p2[], size_t size_a, size_t size_b)
{
  int32_t p1_degree= size_a-1, p2_degree= size_b-1;
  int32_t combine_size=0;
//initialize a combine-array
  if (p1_degree > p2_degree)
  {
    combine_size= p1_degree+1;
  }
  else if (p1_degree <= p2_degree)
  {
    combine_size= p2_degree+1;
  }
  int32_t combine[combine_size], difference=0;
//===Main functions===
  if (p2_degree == p1_degree)
  {
    for (size_t i = 0; i < combine_size; i++)
    {
      combine[i]= p1[i]+p2[i];
    }
    printf_p2_array(combine, combine_size);
  }
  else
  {
    if (p1_degree>p2_degree)
    {
      difference= p1_degree - p2_degree;
      for (size_t i = 0; i < combine_size; i++)
      {
        combine[i] = p1[i];  //i==size_a
      }
      for (size_t i = difference; i < combine_size; i++)
      {
        combine[i] += p2[i-difference];
      }
    }
    else
    {
      difference= p2_degree - p1_degree;
      for (size_t i = 0; i < combine_size; i++)
      {
        combine[i] = p2[i];  //i==size_a
      }
      for (size_t i = difference; i < combine_size; i++)
      {
        combine[i] += p1[i-difference];
      }
    }
    printf_p2_array(combine, combine_size);
  }
}
void calculate_minus(int32_t p1[], int32_t p2[], size_t size_a, size_t size_b)
{
  int32_t p1_degree= size_a-1, p2_degree= size_b-1;
  int32_t combine_size=0;
//initialize a combine-array
  if (p1_degree > p2_degree)
  {
    combine_size= p1_degree+1;
  }
  else if (p1_degree <= p2_degree)
  {
    combine_size= p2_degree+1;
  }
  int32_t combine[combine_size], difference=0;
//Main functions
  if (p2_degree == p1_degree)
  {
    for (size_t i = 0; i < combine_size; i++)
    {
      combine[i]= p1[i]-p2[i];
    }
    printf_p2_array(combine, combine_size);
  }
  else if(p1_degree > p2_degree)
  {
    difference= p1_degree-p2_degree;
    for (size_t i = 0; i < combine_size; i++)
    {
      combine[i]= p1[i];
    }
    for (size_t i = difference; i < combine_size; i++)
    {
      combine[i]-= p2[i-difference];
    }
    printf_p2_array(combine, combine_size);
  }
  else
  {
    difference= p2_degree-p1_degree;
    for (size_t i = difference; i < combine_size; i++)
    {
      combine[i]= p1[i-difference];
    }
    for (size_t i = 0; i < difference; i++)
    {
      combine[i]=0;
    }
    for (size_t i = 0; i < combine_size; i++)
    {
      combine[i] -=p2[i];
    }
    printf_p2_array(combine, combine_size);
  }
}
void calculate_times(int32_t p1[], int32_t p2[], size_t size_a, size_t size_b)
{
//=================Prepare=======================
  int32_t p1_degree= size_a-1, p2_degree= size_b-1;
  int32_t combine_size=0;
  if (p1_degree == p2_degree)
  {
    combine_size = (p1_degree * 2)+1;
  }
  else  //decide how much size
  {
    combine_size = p1_degree + p2_degree +1;
  }
  int32_t combine[combine_size],k=0, m=0;
  for (size_t i = 0; i < combine_size; i++)
  {
    combine[i]=0;
  }

//=================Main=======================
  if (p1_degree == p2_degree)
  {
    combine[0]=p1[0] * p2[0];  //4

    for (size_t i = 1; i < p2_degree+1; i++)
    {
      m=i;  //m=0,1,2
      for (size_t j=0; j <=i; j++)
      {
        combine[i]+=(p1[k] * p2[m]);
        k++;
        m--;
      }
      k=0;
    }
    k=1,m=p2_degree;
    int32_t check =0;
    for (size_t i = 0; i < combine_size-(p2_degree+1) ; i++)
    {
      for (size_t j = p2_degree; j >i; j--)
      {
        combine[i+size_a] = combine[i+size_a] + (p1[k] * p2[m]);
        m--;
        k++;
      }
      m=p2_degree;
      k=2+i;
    }
    printf_p2_array(combine, combine_size);
  }
  else
  {
    if (p1_degree > p2_degree)
    {
        int32_t k=0,start = 0, end=0,times=0;
        int32_t body=p2_degree;
//================HEAD=================
        for (int32_t i = 0; i < p2_degree; i++)
        {
          start=0;
          end=i;
          for (int32_t j = 0; j <= i; j++)
          {
            combine[i] += (p1[start] * p2[end]);
            start++;
            end--;
          }
        }
//================BODY=================
        start=0;
        end=0;
        for (int32_t i = 0; i < combine_size - (2 * p2_degree); i++)
        {
          start = 0+i;
          end = p2_degree;  //body= p2_degree
          for (int32_t j = 0; j < p2_degree+1; j++)
          {
            combine[body] += (p1[start] * p2[end]);
            end--;
            start++;
          }
          start= i; //final ==> 3
          body++;// 4 5 6
        }
        // printf_p2_array(combine, combine_size);
//===============Footer================
        start= start + 1;
        end=p2_degree;
        int32_t footer_coe=start;  //footer==>3
        for (int32_t i = 0; i < p2_degree; i++)
        {
          // printf("\n\nBefore start++, start: %d \n", start );
          // printf("Before body++, body: %d \n", body );
          for (int32_t j = p2_degree; j > i ; j--)
          {
            combine[body] += (p1[start] * p2[j]);
            start++;
          }
          start = footer_coe +1;
          footer_coe++; //footer ==> 4 5 6
          body++;
        }
    }
    else   //p2_degree > p1_degree
    {
      int32_t k=0,start = 0, end=0,times=0;
      int32_t body=p1_degree;
//================HEAD=================
      for (int32_t i = 0; i < p1_degree; i++)
      {
        start=0;
        end=i;
        for (int32_t j = 0; j <= i; j++)
        {
          combine[i] += (p1[start] * p2[end]);
          start++;
          end--;
        }
      }
//================BODY=================
      start=0;
      end=0;
      int32_t cons=0;
      for (int32_t i = 0; i < combine_size - (2 * p1_degree); i++)
      {
        start = 0;
        end = p1_degree+cons;  //body= p1_degree
        for (int32_t j = 0; j < p1_degree+1; j++)
        {
          combine[body] += (p1[start] * p2[end]);
          end--;
          start++;
        }
        cons++;
        body++;// 4 5 6
      }
//===============Footer================
      start=1;
      int32_t footer_coe=start;  //footer==>1
      body= combine_size - p1_degree;
      for (int32_t i = 0; i < p1_degree; i++)
      {
        end=p2_degree;
        for (int32_t j = p1_degree; j > i ; j--)
        {
          combine[body] += (p1[start] * p2[end]);
          start++;
          end--;
        }
        start = footer_coe +1;
        footer_coe++; //footer ==> 4 5 6
        body++;
      }
    }
    printf_p2_array(combine, combine_size);
  }
}
//====================================================
//HW0504
void trans_into_regre(double point[][2], int32_t point_num)
{
  double t=0, y=0, b1=0, b0=0;  //First
  double tixyi=0, tixti=0, yixyi=0;
  double t1_t[point_num], y1_y[point_num] ;
  for (int32_t i = 0; i < point_num; i++)
  {
    t1_t[i]=0;
    y1_y[i]=0;
  }
  for (int32_t i = 0; i < point_num; i++)
  {
    t += point[i][0];
  }
  for (size_t i = 0; i < point_num; i++)
  {
    y += point[i][1];
  }
  y = y / point_num;
  t = t / point_num;

  for (int32_t i = 0; i < point_num; i++)
  {
    t1_t[i] = point[i][0] - t;
    y1_y[i] = point[i][1] - y;
  }
  //Ti * Yi
  for (int32_t i = 0; i < point_num; i++)
  {
    tixyi += (t1_t[i] * y1_y[i]);
    tixti += (t1_t[i] * t1_t[i]);
    yixyi += (y1_y[i] * y1_y[i]);
  }
  b1 = tixyi / tixti ;
  b0 = y - (b1 * t);
  printf("Regression Equation: y = %.2lf x + %.2lf\n", b1, b0 );
}
