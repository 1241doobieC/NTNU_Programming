#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include"check_file.h"


//hw0401
  void show_roman(int32_t num)
  {

    int32_t value_a[6]={1000,500,100,50,10,5};
    int32_t value_b[6]={900,400,90,40,9,4};
    char list_a[]={'M','D','C','L', 'X', 'V'};
    char list_b[6][3]={"CM", "CD", "XC", "XL", "IX", "IV"};

    while (num > 0) {
      for (int32_t i = 0; i < 6; i++) {
          if (num - value_a[i] >= 0) {
            printf("%c", list_a[i] );
            num = num - value_a[i];
            break;
          }  // End of If
          else{
            if (num - value_b[i] >=0) {
              printf("%c%c", list_b[i][0],list_b[i][1]);
              num = num - value_b[i];
              break;
            }
          } // End of Else

          if (num > 0 && num <= 3) {
            printf("I");
            num = num - 1;
            break;
          }
      }  //End of For
    }  //End of While
    printf("\n");


}

//hw0402-1
void move(int32_t num, char A, char B, char C)
{
  if (num==1)
  {
    printf("Move Disk 1 to rod %c \n",B );
  }
  else
  {
    move(num-1 , A, C, B);
    printf("Move Disk %d to rod %c \n",num, B );
    move(num-1, C, B, A);
  }
}
//hw0402-2
void for_loop_move(int32_t num)
{
  int A[21] = {21, 0};
  int B[21] = {21, 0};
  int C[21] = {21, 0};
  int A_top = num;
  int B_top = 0;
  int C_top = 0;
  for (int load = 1; load <= num; load++) {
    A[load] = num - load + 1;
  }
  if (num % 2 == 0) { // even number
    while (1) {

      // A<=>C

      if (A[A_top] < C[C_top]) { // A=>C
        C[C_top + 1] = A[A_top];
        printf("move disk %d to rod 3\n", A[A_top]);
        A[A_top] = 0;
        A_top--;
        C_top++;
      } else { // C=>A
        A[A_top + 1] = C[C_top];
        printf("move disk %d to rod 1\n", C[C_top]);
        C[C_top] = 0;
        C_top--;
        A_top++;
      }
      if (B[num] == 1) {
        break;
      }
      if (A[A_top] < B[B_top]) { // A=>B
        B[B_top + 1] = A[A_top];
        printf("move disk %d to rod 2\n", A[A_top]);
        A[A_top] = 0;
        A_top--;
        B_top++;
      } else { // B=>A
        A[A_top + 1] = B[B_top];
        printf("move disk %d to rod 1\n", B[B_top]);
        B[B_top] = 0;
        B_top--;
        A_top++;
      }
      if (B[num] == 1) {
        break;
      }
      if (C[C_top] < B[B_top]) { // C=>B
        B[B_top + 1] = C[C_top];
        printf("move disk %d to rod 2\n", C[C_top]);
        C[C_top] = 0;
        C_top--;
        B_top++;
      } else { // B=>C
        C[C_top + 1] = B[B_top];
        printf("move disk %d to rod 3\n", B[B_top]);
        B[B_top] = 0;
        B_top--;
        C_top++;
      }
      if (B[num] == 1) {
        break;
      }
    }
  } else {
    while (1) {
      if (A[A_top] < B[B_top]) { // A=>B
        B[B_top + 1] = A[A_top];
        printf("move disk %d to rod 2\n", A[A_top]);
        A[A_top] = 0;
        A_top--;
        B_top++;
      } else { // B=>A
        A[A_top + 1] = B[B_top];
        printf("move disk %d to rod 1\n", B[B_top]);
        B[B_top] = 0;
        B_top--;
        A_top++;
      }
      if (B[num] == 1) {
        break;
      }
      if (A[A_top] < C[C_top]) { // A=>C
        C[C_top + 1] = A[A_top];
        printf("move disk %d to rod 3\n", A[A_top]);
        A[A_top] = 0;
        A_top--;
        C_top++;
      } else { // C=>A
        A[A_top + 1] = C[C_top];
        printf("move disk %d to rod 1\n", C[C_top]);
        C[C_top] = 0;
        C_top--;
        A_top++;
      }
      if (B[num] == 1) {
        break;
      }
      if (C[C_top] < B[B_top]) { // C=>B
        B[B_top + 1] = C[C_top];
        printf("move disk %d to rod 2\n", C[C_top]);
        C[C_top] = 0;
        C_top--;
        B_top++;
      } else { // B=>C
        C[C_top + 1] = B[B_top];
        printf("move disk %d to rod 3\n", B[B_top]);
        B[B_top] = 0;
        B_top--;
        C_top++;
      }
      if (B[num] == 1) {
        break;
      }
    }
  }
}
//hw0403
double trans(double value_of_k)
  {
    //initialize the value we need
    double final=1;
    double k=value_of_k;
    double start=1, a= 1;
    double sum=0;
    for (size_t i = 0; i < k; i++) {
        start *= a;
        a++;
      final +=(1/start);
    }

    return final;
  }

//hw0404
double equivalent_r(double r, double n)
  {
    double ans=0;
    double combine=0;
    combine = r + r;

    if (n == 1)
    {
      return r * 2;
    }
    else
    {
      for (size_t i = 1; i < n; i++)
      {
          combine= ((combine * r )/ (combine +r))+r;
      }
    }
    ans = combine;

    return ans;
  }

//hw0405
void create_array(int32_t card[4])
{
  srand(time(0));
  int32_t i,j;
  for ( i = 0; i < 4; i++)
  {
      do
      {
        card[i]= rand() % 10;
        for ( j = 0; j < i; j++)
        {
          if (card[i] == card[j])
          {
            break;
          }
        }
      } while(i != j);
  }
}
int32_t compare_num(int32_t array[4], int32_t card[4], int32_t flag)
{

   if (flag == 1)
   {
     return 0;
   }
   else
   {
     /*
      *
      *Compare two sets of array   ==> card[i] and array[i]
      *
      */
     int32_t wrong_position_but_right_number=0, right_position_and_number=0;
     for (int32_t i = 0; i < 4; i++)
     {
       if (card[i] == array[i]) right_position_and_number++;
       for (int32_t j = 0; j < 4; j++)
       {
         if (card[i] == array[j])
         {
           if (card[i] == array[i]) {
             continue;
           }
           wrong_position_but_right_number++;
         }
       }
     }
     if (wrong_position_but_right_number<0)
     {
       wrong_position_but_right_number=0;
     }
     if (right_position_and_number==4) {
       printf("\033[33m\tResponse: Bingo, Congratulation! \n\033[0m");
       flag =1;
     }
     else if (flag==0) {
       printf("\033[35m\tResponse: %dA%dB \n\033[0m",right_position_and_number, wrong_position_but_right_number);
     }
   }
 return flag;
}
