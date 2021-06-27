#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define MAX 4096
#define MIN 1024
#define FALSE 0
#define TRUE 1
int main()
{
  //=====json=====
  printf("Please enter the JSON string: \n");
  char json[MAX] = "";
  fgets(json, MAX, stdin);
  //=====Choice=====
  printf("Choice (0: Exit, 1: Get) :");
  int32_t choice = 0;
  scanf("%d", &choice);
  char c = getchar();
  //=====Key=====
  char key[MIN] = "";
  printf("Key: ");
  fgets(key, MIN, stdin);
  //=====Value=====
  char *value;
  //=====Token=====
  const char mHow[2] = ":";
  const char dHow[2] = ",";
  const char gHow_1[2] = "[";
  const char gHow_2[2] = "]";
  char *token_outside;
  char *token_inside;

  //===============
  while(choice != 0)
  {
    //====================Main====================
    // printf("%s", key);
    token_outside = strtok(json, dHow);
    printf("%s", token_outside);
    char *mystr = (char *)malloc(sizeof(char) * 256);
    // while(token_outside != NULL)
    // {
    //   // {"firstName":"John", "lastName":"Smith", "gender":"Male"}
    //   // printf("%s", token_outside);
    //   // printf("Problem first \n");
    //   // printf("%s \n", key);
    //   mystr = strstr(token_outside, key);
    //   printf("%s ", mystr);
    //   for (int32_t i = 0; mystr[i] != '\0'; i++)
    //   {
    //     printf("Problem second \n");
    //     token_inside = strtok(token_outside, mHow);
    //     printf("%s", token_inside);
    //   }
    //   token_outside = strtok(NULL, dHow);
    // }

    printf("\nThis task is too hard to be accomplished..... \n");
    //====================Main====================
    printf("Choice (0: Exit, 1: Get) :");
    scanf("%d", &choice);
    if(choice == 0)
    {
      printf("Bye!\n");
    }
    free(mystr);
  }
  return 0;
}
