#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define ANS_LENG 9999

void ini(char a[3],char b[ANS_LENG])
{
  for (int32_t i = 0; i < 3; i++)
  {
    a[i] = 0;
  }
  for (int32_t i = 0; i < ANS_LENG; i++)
  {
    b[i] = 0;
  }
  return;
}

int main()
{
  char space[3]="", ans[ANS_LENG]="";
  char **trash = NULL;
  int32_t num = 0;
  int32_t start = 0;
  ini(space, ans);

  printf("Please enter the hex string:");
  //====================================
  do
  {
    fgets(space, 3, stdin);
    if (strncmp(space, "00", 2) != 0)
    {
      num = (int32_t)strtol(space,trash, 16);  //Base 16 Because of hex
      if(num < 32 || num > 126)
      {
        // printf("ASCII num is:%d \n", num);
        // printf("%s\n", space);
        printf("Invalid Input \n");
        return 0;
      }
      else
      {
        ans[start] = num;
        start++;
        num = 0;
      }
    }
  }
  while(strncmp(space, "00", 2) != 0);
  //====================================
  printf("%s", ans);
  printf("\n");
  return 0;
}
