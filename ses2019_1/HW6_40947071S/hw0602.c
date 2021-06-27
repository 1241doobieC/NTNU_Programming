#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#define FALSE 0
#define TRUE 1
#include "check_funs.h"

// void show_result();
int main()
{
  int32_t state=1,num=0,position=0;
  int32_t array[10]= {0}, back_up[10]={0}, back_up_num=0;
  int32_t count_state=0;
  while (state != FALSE)
  {
    printf("input:" );
    scanf(" %d", &num);
    if(num == 0)
    {
      state = FALSE;
      break;
    }
    else if (num==-1)
    {
      if (position == 0)
      {
        //Do Nothing
      }
      else
      {
        back_up[back_up_num]= array[position-1];
        back_up_num++;
        array[position-1]=0; //previous item become 0
        /*
          0 1 2 3 4  5  6
          1 2 3 4 5 -1 -2
          1 2 3 4
        */
        array[position]=-1; //currently item become -1
        position--;
      }
    }
    else if (num == -2)
    {
      if(array[position+1] != -1 )
      {
        //Do nothing
      }
      else
      {
        array[position]= back_up[back_up_num-1];
        back_up[back_up_num-1]=0;
        back_up_num--;
        position++;
      }
    }
    else
    {
      if (position > 9)
      {
        position = 9;
        array[0]=0;
        int32_t cha = 0;
        for (int32_t i = 1; i < 10; i++)
        {
          int32_t tem = array[i];
          array[cha] = tem;
          cha++;
        }
      }
      array[position]= num;
      position++;
    }

    if (count_state < 10)
    {
      count_state++;
    }
    else
    {
      count_state=10;
    }
  }
  int32_t count=0;
  show_result();
  for (int32_t i = 0; i < 10; i++)
  {
    if (array[i] !=0 && array[i] != -1)
    {
      printf("%d ", array[i]);
    }
    else if (array[i] == -1 ||  array[i]== -2 )
    {
      count++;
    }
  }
//=============
  printf("\n");

  return 0;
}

// void show_result()
// {
//   printf("Result: ");
// }
