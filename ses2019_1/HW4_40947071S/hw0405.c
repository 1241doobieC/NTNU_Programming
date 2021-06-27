#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include"check_file.h"

int main(){

  int32_t card[4]={0};
  create_array(card);

  printf("Bull and Cows game: \n");
  //main Function
  int32_t right=0;
  int32_t round=1;
  int32_t guess=0;
  int32_t array[4]={0};

  while (right==0)
  {
    printf("Round %d >>> \n", round );
    printf("\tYour guess: " );
    scanf("%d", &guess );

    //Check Validity
    int32_t digit=0;
      if (guess < 0)
      {
        printf("\033[31m\tResponse: Invalid Input! \n\033[0m");
        return 0;
      }
      for (int32_t i = 0; i < 4; i++)
      {
        array[i]= guess % 10;
        guess /=10;
        digit++;
      }
      if (guess != 0) {
        printf("\033[31m\tResponse: Invalid Input(Over 4 digits)! \n\033[0m");
        return 0;
      }
        //Check if repeat
        int32_t abc=0;
        for (int32_t i = 0; i < 4; i++)
        {
          for (int32_t j = 0; j < i; j++)
          {
             if (array[i] == array[j])
             {
               printf("\033[31m\tResponse: Invalid guess! \n\033[0m");
               abc=1;
               break;
             }
          }
          if (abc!=0)
          {
            break;
          }
        }
        //Exchange the number
        int32_t exchange_num=3;
        for (int32_t i = 0; i < 2; i++) {
          int32_t tem= array[i];
          array[i]= array[exchange_num];
          array[exchange_num]=tem;
          exchange_num--;
        }

        //compare_num(array, card, abc);
        right = compare_num(array, card, abc);
        round++;
  }


  return 0;
 }

