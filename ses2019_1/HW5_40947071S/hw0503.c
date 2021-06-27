#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include"hw05_CHECK_FILES.h"

// void printf_p1_array(int32_t a[], size_t);
// void printf_p2_array(int32_t a[], size_t);
// void calculate_sum(int32_t a[], int32_t b[], size_t, size_t);
// void calculate_minus(int32_t a[], int32_t b[], size_t, size_t);
// void calculate_times(int32_t a[], int32_t b[], size_t, size_t);
int main()
{
  int32_t p1_degree=0,p2_degree=0;
//================p1==================
  printf("Please enter p1 degree: ");
  scanf(" %d", &p1_degree );
  if (p1_degree<0) {  //Block P1's degree
    printf("P1's degree could not be smaller than 0. \n");
    return 0;
  }
  int32_t p1[p1_degree+1];
  printf("Please enter p1 coeffiecients: ");
  for (size_t i = 0; i <= p1_degree; i++) {
    scanf("%d", &p1[i] );
  }
  if (p1[0] == 0 && p1_degree!=0) {  //First coeiecient could not be equal to 0.
    printf("First coeffiecients could not be equal to 0 when degree!=0.\n");
    return 0;
  }
//================p2==================
  printf("Please enter p2 degree: ");
  scanf(" %d", &p2_degree );
  if (p2_degree<0) {  //Block P2's degree
    printf("P2's degree could not be smaller than 0. \n");
    return 0;
  }
  int32_t p2[p2_degree+1];
  printf("Please enter p2 coeffiecients: ");
  for (size_t i = 0; i <= p2_degree; i++) {
    scanf("%d", &p2[i] );
  }
  if (p2[0] == 0 && p2_degree!=0) { //First coeiecient could not be equal to 0.
    printf("First coeffiecients could not be equal to 0 when degree!=0.\n");
    return 0;
  }
//========Print coeffiecients==========
  int32_t a=p1_degree+1;  //a==> array_size

  if (p1_degree==0 && p2_degree==0)
  {
    printf("P1: %d\n", p1[0] );
    printf("P2: %d\n", p2[0] );
    printf("P1 + P2: %2d \n", p1[0] + p2[0] );
    printf("P1 - P2: %2d \n", p1[0] - p2[0] );
    printf("P1 * P2: %2d \n", p1[0] * p2[0] );
  }
  else if (p1_degree==0 &&p1[0]==0&&p2_degree!=0)
  {
    a=p2_degree+1;
    printf("P1: 0\n");
    printf_p2_array(p2,a);
    printf("P1 + P2: ");
    printf_p2_array(p2,a);
    printf("P1 - P2: ");
    for (size_t i = 0; i <= p2_degree; i++)
    {
      if (p2[i] != 0)
      {
        p2[i]= p2[i] * (-1);
      }
    }
    printf_p2_array(p2, a);
    printf("P1 * P2: 0\n");
  }
  else if (p2_degree==0 &&p2[0]==0&&p1_degree!=0)
  {
    a=p1_degree+1;
    printf_p1_array(p1,a);
    printf("P2: 0\n");
    printf("P1 + P2: ");
    printf_p1_array(p1,a);
    printf("P1 - P2: ");
    for (size_t i = 0; i <= p1_degree; i++)
    {
      if (p1[i] != 0)
      {
        p1[i]= p1[i] * (-1);
      }
    }
    printf_p1_array(p1, a);
    printf("P1 * P2: 0\n");
  }
  else //where real functions are...
  {
    int32_t size_a=p1_degree+1, size_b=p2_degree+1;
    printf("P1: ");
    printf_p1_array(p1,a);  //a==>array_size
    a=p2_degree+1;
    printf("P2: ");
    printf_p2_array(p2,a);
    printf("P1 + P2 : ");
    calculate_sum(p1,p2,size_a,size_b);
    printf("P1 - P2 : " );
    calculate_minus(p1,p2,size_a,size_b);
    printf("P1 * P2 : " );
    calculate_times(p1,p2,size_a,size_b);
    a=0;
  }
  return 0;
}
//
// void printf_p1_array(int32_t p1[], size_t size)
// {
//   int32_t coeiecient_numbers = size-1;
//   int32_t p1_degree= size - 1;
//   if(p1[0]>0 && p1[0]!=1)  //First coeiecient
//   {
//     printf("%dx^%d", p1[0],coeiecient_numbers);
//   }
//   else if (p1[0]>0 && p1[0]==1)
//   {
//     printf("x^%d",coeiecient_numbers);
//   }
//   else if (p1[0]<0 && p1[0]!=(-1))
//   {
//     printf("%dx^%d", p1[0],coeiecient_numbers);
//   }
//   else if (p1[0]<0 && p1[0]==(-1))
//   {
//     printf("-x^%d", coeiecient_numbers);
//   }
//   coeiecient_numbers=coeiecient_numbers-1;
// //===============================================
// //Second Starts from here
//   for (size_t i = 1; i <= p1_degree+1; i++)
//   {
//     if (coeiecient_numbers>1)
//     {
//       if (p1[i]>0 && p1[i]!=1)
//       {
//         printf(" + %dx^%d", p1[i],coeiecient_numbers);
//       }
//       else if (p1[i]>0 && p1[i]==1)
//       {
//         printf(" + x^%d",coeiecient_numbers);
//       }
//       else if(p1[i]<0 && p1[i]!=(-1))
//       {
//         printf(" + (%d)x^%d", p1[i],coeiecient_numbers);
//       }
//       else if(p1[i]<0 && p1[i]==(-1))
//       {
//         printf(" + (-x)^%d",coeiecient_numbers);
//       }
//       else if (p1[i]==0)
//       {
//         //Do nothing
//       }
//     }
//     else if (coeiecient_numbers==1)
//     {
//       if (p1[p1_degree-1]!=1 &&p1[p1_degree-1]>0)
//       {
//         printf(" + %dx", p1[p1_degree-1]);
//       }
//       else if(p1[p1_degree-1]==1)
//       {
//         printf(" + x");
//       }
//       else if(p1[p1_degree-1]==(-1))
//       {
//         printf("- x");
//       }
//       else if (p1[p1_degree-1]!=(-1) &&p1[p1_degree-1]<0)
//       {
//         printf(" + (%d)x", p1[p1_degree-1]);
//       }
//       else if (p1[p1_degree-1]==0)
//       {
//         //Do nothing
//       }
//     }
//     else if (coeiecient_numbers==0) //Constant number
//     {
//       if (p1[p1_degree]>0 && p1[p1_degree]!=1)
//       {
//         printf(" + %d \n", p1[p1_degree] );
//       }
//       else if (p1[p1_degree]==1)
//       {
//         printf(" + 1 \n");
//       }
//       else if (p1[p1_degree]==(-1))
//       {
//         printf(" - 1 \n");
//       }
//       else if (p1[p1_degree]!=(-1) && p1[p1_degree]<0)
//       {
//         printf(" + (%d) \n", p1[p1_degree] );
//       }
//       else if (p1[p1_degree]==0)
//       {
//         printf("\n");  //Do nothing
//       }
//     }
//     coeiecient_numbers--;
//   }
// }
//
// void printf_p2_array(int32_t p2[], size_t size)
// {
//   int32_t coeiecient_numbers = size-1;
//   int32_t p2_degree= size - 1;
//   if(p2[0]>0 && p2[0]!=1)  //First coeiecient
//   {
//     printf("%dx^%d", p2[0],coeiecient_numbers);
//   }
//   else if (p2[0]>0 && p2[0]==1)
//   {
//     printf("x^%d",coeiecient_numbers);
//   }
//   else if (p2[0]<0 && p2[0]!=(-1))
//   {
//     printf("%dx^%d", p2[0],coeiecient_numbers);
//   }
//   else if (p2[0]<0 && p2[0]==(-1))
//   {
//     printf("-x^%d", coeiecient_numbers);
//   }
//   coeiecient_numbers=coeiecient_numbers-1;
// //===============================================
// //Second Starts from here
//   for (size_t i = 1; i <= p2_degree+1; i++)
//   {
//     if (coeiecient_numbers>1)
//     {
//       if (p2[i]>0 && p2[i]!=1)
//       {
//         if (p2[0] == 0)
//         {
//           printf("%dx^%d", p2[i],coeiecient_numbers);
//         }
//         printf(" + %dx^%d", p2[i],coeiecient_numbers);
//       }
//       else if (p2[i]>0 && p2[i]==1)
//       {
//         if (p2[0] == 0)
//         {
//           printf("x^%d",coeiecient_numbers);
//         }
//         printf(" + x^%d",coeiecient_numbers);
//       }
//       else if(p2[i]<0 && p2[i]!=(-1))
//       {
//         if (p2[0] == 0)
//         {
//           printf("(%d)x^%d", p2[i],coeiecient_numbers);
//         }
//         printf(" + (%d)x^%d", p2[i],coeiecient_numbers);
//       }
//       else if(p2[i]<0 && p2[i]==(-1))
//       {
//         if (p2[0] == 0)
//         {
//           printf("(-x)^%d",coeiecient_numbers);
//         }
//         printf(" + (-x)^%d",coeiecient_numbers);
//       }
//       else if (p2[i]==0)
//       {
//         //Do nothing
//       }
//     }
//     else if (coeiecient_numbers==1)
//     {
//       if (p2[p2_degree-1]!=1 &&p2[p2_degree-1]>0)
//       {
//         printf(" + %dx", p2[p2_degree-1]);
//       }
//       else if(p2[p2_degree-1]==1)
//       {
//         printf(" + x");
//       }
//       else if(p2[p2_degree-1]==(-1))
//       {
//         printf(" - x");
//       }
//       else if (p2[p2_degree-1]!=(-1) &&p2[p2_degree-1]<0)
//       {
//         printf(" + (%d)x", p2[p2_degree-1]);
//       }
//       else if (p2[p2_degree-1]==0)
//       {
//         //Do nothing
//       }
//     }
//     else if (coeiecient_numbers==0) //Constant number
//     {
//       if (p2[p2_degree]>0 && p2[p2_degree]!=1)
//       {
//         printf(" + %d ", p2[p2_degree] );
//       }
//       else if (p2[p2_degree]==1)
//       {
//         printf(" + 1 ");
//       }
//       else if (p2[p2_degree]==(-1))
//       {
//         printf(" - 1 ");
//       }
//       else if (p2[p2_degree]!=(-1) && p2[p2_degree]<0)
//       {
//         printf(" + (%d) ", p2[p2_degree] );
//       }
//       else if (p2[p2_degree]==0)
//       {
//         //printf("");  //Do nothing
//       }
//     }
//     coeiecient_numbers--;
//   }
//
//   int32_t check=0;
//   for (size_t i = 0; i < p2_degree; i++)
//   {
//     if (p2[i] == 0)
//     {
//       check++;
//     }
//   }
//   if (check == (size-1))
//   {
//     printf("0");
//   }
//   printf("\n");
// }
//
// void calculate_sum(int32_t p1[], int32_t p2[], size_t size_a, size_t size_b)
// {
//   int32_t p1_degree= size_a-1, p2_degree= size_b-1;
//   int32_t combine_size=0;
// //initialize a combine-array
//   if (p1_degree > p2_degree)
//   {
//     combine_size= p1_degree+1;
//   }
//   else if (p1_degree <= p2_degree)
//   {
//     combine_size= p2_degree+1;
//   }
//   int32_t combine[combine_size], difference=0;
// //===Main functions===
//   if (p2_degree == p1_degree)
//   {
//     for (size_t i = 0; i < combine_size; i++)
//     {
//       combine[i]= p1[i]+p2[i];
//     }
//     printf_p2_array(combine, combine_size);
//   }
//   else
//   {
//     if (p1_degree>p2_degree)
//     {
//       difference= p1_degree - p2_degree;
//       for (size_t i = 0; i < combine_size; i++)
//       {
//         combine[i] = p1[i];  //i==size_a
//       }
//       for (size_t i = difference; i < combine_size; i++)
//       {
//         combine[i] += p2[i-difference];
//       }
//     }
//     else
//     {
//       difference= p2_degree - p1_degree;
//       for (size_t i = 0; i < combine_size; i++)
//       {
//         combine[i] = p2[i];  //i==size_a
//       }
//       for (size_t i = difference; i < combine_size; i++)
//       {
//         combine[i] += p1[i-difference];
//       }
//     }
//     printf_p2_array(combine, combine_size);
//   }
// }
//
// void calculate_minus(int32_t p1[], int32_t p2[], size_t size_a, size_t size_b)
// {
//   int32_t p1_degree= size_a-1, p2_degree= size_b-1;
//   int32_t combine_size=0;
// //initialize a combine-array
//   if (p1_degree > p2_degree)
//   {
//     combine_size= p1_degree+1;
//   }
//   else if (p1_degree <= p2_degree)
//   {
//     combine_size= p2_degree+1;
//   }
//   int32_t combine[combine_size], difference=0;
// //Main functions
//   if (p2_degree == p1_degree)
//   {
//     for (size_t i = 0; i < combine_size; i++)
//     {
//       combine[i]= p1[i]-p2[i];
//     }
//     printf_p2_array(combine, combine_size);
//   }
//   else if(p1_degree > p2_degree)
//   {
//     difference= p1_degree-p2_degree;
//     for (size_t i = 0; i < combine_size; i++)
//     {
//       combine[i]= p1[i];
//     }
//     for (size_t i = difference; i < combine_size; i++)
//     {
//       combine[i]-= p2[i-difference];
//     }
//     printf_p2_array(combine, combine_size);
//   }
//   else
//   {
//     difference= p2_degree-p1_degree;
//     for (size_t i = difference; i < combine_size; i++)
//     {
//       combine[i]= p1[i-difference];
//     }
//     for (size_t i = 0; i < difference; i++)
//     {
//       combine[i]=0;
//     }
//     for (size_t i = 0; i < combine_size; i++)
//     {
//       combine[i] -=p2[i];
//     }
//     printf_p2_array(combine, combine_size);
//   }
// }
//
// void calculate_times(int32_t p1[], int32_t p2[], size_t size_a, size_t size_b)
// {
// //=================Prepare=======================
//   int32_t p1_degree= size_a-1, p2_degree= size_b-1;
//   int32_t combine_size=0;
//   if (p1_degree == p2_degree)
//   {
//     combine_size = (p1_degree * 2)+1;
//   }
//   else  //decide how much size
//   {
//     combine_size = p1_degree + p2_degree +1;
//   }
//   int32_t combine[combine_size],k=0, m=0;
//   for (size_t i = 0; i < combine_size; i++)
//   {
//     combine[i]=0;
//   }
//
// //=================Main=======================
//   if (p1_degree == p2_degree)
//   {
//     combine[0]=p1[0] * p2[0];  //4
//
//     for (size_t i = 1; i < p2_degree+1; i++)
//     {
//       m=i;  //m=0,1,2
//       for (size_t j=0; j <=i; j++)
//       {
//         combine[i]+=(p1[k] * p2[m]);
//         k++;
//         m--;
//       }
//       k=0;
//     }
//     k=1,m=p2_degree;
//     int32_t check =0;
//     for (size_t i = 0; i < combine_size-(p2_degree+1) ; i++)
//     {
//       for (size_t j = p2_degree; j >i; j--)
//       {
//         combine[i+size_a] = combine[i+size_a] + (p1[k] * p2[m]);
//         m--;
//         k++;
//       }
//       m=p2_degree;
//       k=2+i;
//     }
//     printf_p2_array(combine, combine_size);
//   }
//   else
//   {
//     if (p1_degree > p2_degree)
//     {
//         int32_t k=0,start = 0, end=0,times=0;
//         int32_t body=p2_degree;
// //================HEAD=================
//         for (int32_t i = 0; i < p2_degree; i++)
//         {
//           start=0;
//           end=i;
//           for (int32_t j = 0; j <= i; j++)
//           {
//             combine[i] += (p1[start] * p2[end]);
//             start++;
//             end--;
//           }
//         }
// //================BODY=================
//         start=0;
//         end=0;
//         for (int32_t i = 0; i < combine_size - (2 * p2_degree); i++)
//         {
//           start = 0+i;
//           end = p2_degree;  //body= p2_degree
//           for (int32_t j = 0; j < p2_degree+1; j++)
//           {
//             combine[body] += (p1[start] * p2[end]);
//             end--;
//             start++;
//           }
//           start= i; //final ==> 3
//           body++;// 4 5 6
//         }
//         // printf_p2_array(combine, combine_size);
// //===============Footer================
//         start= start + 1;
//         end=p2_degree;
//         int32_t footer_coe=start;  //footer==>3
//         for (int32_t i = 0; i < p2_degree; i++)
//         {
//           // printf("\n\nBefore start++, start: %d \n", start );
//           // printf("Before body++, body: %d \n", body );
//           for (int32_t j = p2_degree; j > i ; j--)
//           {
//             combine[body] += (p1[start] * p2[j]);
//             start++;
//           }
//           start = footer_coe +1;
//           footer_coe++; //footer ==> 4 5 6
//           body++;
//         }
//     }
//     else   //p2_degree > p1_degree
//     {
//       int32_t k=0,start = 0, end=0,times=0;
//       int32_t body=p1_degree;
// //================HEAD=================
//       for (int32_t i = 0; i < p1_degree; i++)
//       {
//         start=0;
//         end=i;
//         for (int32_t j = 0; j <= i; j++)
//         {
//           combine[i] += (p1[start] * p2[end]);
//           start++;
//           end--;
//         }
//       }
// //================BODY=================
//       start=0;
//       end=0;
//       int32_t cons=0;
//       for (int32_t i = 0; i < combine_size - (2 * p1_degree); i++)
//       {
//         start = 0;
//         end = p1_degree+cons;  //body= p1_degree
//         for (int32_t j = 0; j < p1_degree+1; j++)
//         {
//           combine[body] += (p1[start] * p2[end]);
//           end--;
//           start++;
//         }
//         cons++;
//         body++;// 4 5 6
//       }
// //===============Footer================
//       start=1;
//       int32_t footer_coe=start;  //footer==>1
//       body= combine_size - p1_degree;
//       for (int32_t i = 0; i < p1_degree; i++)
//       {
//         end=p2_degree;
//         for (int32_t j = p1_degree; j > i ; j--)
//         {
//           combine[body] += (p1[start] * p2[end]);
//           start++;
//           end--;
//         }
//         start = footer_coe +1;
//         footer_coe++; //footer ==> 4 5 6
//         body++;
//       }
//     }
//     printf_p2_array(combine, combine_size);
//   }
// }
