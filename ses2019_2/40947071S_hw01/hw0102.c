#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define MAX 4096
#define MIN 1024
#define RED "\e[1;91m"
#define BLUE "\e[1;94m"
#define RESET "\e[m"

char *replace(char *ori_Text, char *key, char *new);
void sheissePrint(char array[MAX], char key_array[MIN]);

int main()
{
  char *ori_Text = (char *) malloc(1024);
  // char *copy_Text = (char *) malloc(1024);
  char *key = (char *) malloc(128);
  char *new = (char *) malloc(128);
  printf("Please enter the original text:\n");
  fgets(ori_Text,MAX,stdin);

  printf("Keyword:\n");
  fgets(key, MIN, stdin);
  key[strlen(key)-1]='\0';
  printf("New Word:\n");
  fgets(new, MIN, stdin);

  printf("\n");
  //=================================

  printf("Before:\n");
  for (int32_t i = 0; ori_Text[i] != '\0'; i++)
  {
    if(strncmp(&ori_Text[i],key,strlen(key)) == 0)
    {
      printf(BLUE"%.*s"RESET, (int32_t)strlen(key),&ori_Text[i]);
      i +=strlen(key)-1;
    }
    else
    {
      printf("%c", ori_Text[i]);
    }
  }

  if (strlen(key) > 0 && key[strlen(key)-1] == '\n')
  {
    key[strlen(key)-1] = 0;
  }
  if (strlen(new) > 0 && new[strlen(new)-1] == '\n')
  {
    new[strlen(new)-1] = 0;
  }
  char *copy_Text = replace(ori_Text, key, new);


  printf("After:\n");
  for (int32_t i = 0; copy_Text[i] != '\0'; i++)
  {
      if(strncmp(&copy_Text[i],new,strlen(key)) == 0)
      {
        printf(RED"%.*s"RESET, (int32_t)strlen(new),&copy_Text[i]);
        i +=strlen(new)-1;
        // printf("ori_Text[%d] = %c, key[%d] = %c \n", i,ori_Text[i], i, key[i]);
      }
      else
      {
        printf("%c", copy_Text[i]);
        // printf("ori_Text[%d] = %c, key[%d] = %c \n", i,ori_Text[i], i, key[i]);
      }
  }
  free(ori_Text);
  // free(copy_Text);
  free(key);
  free(new);
  // printf("\n");
  return 0;
}

//==============================================================
char *replace(char *ori_Text, char *key, char *new)
{
  // char *test = "Happy Holidays.";
  int32_t key_l = strlen(key);
  int32_t new_l = strlen(new);
  int32_t length = strlen(ori_Text)+1;
  int32_t test = 0;
  int gap = 0; //delta x
  //=============================================
  char* real_Text = (char *)malloc(sizeof(char) * length);
  strncpy(real_Text, ori_Text, length);
  // printf("===had been copied===\n");

  char* Text = ori_Text;
  char* location = strstr(Text, key);
  // printf("\n\nSomething might be wrong here:%lu \n\n", location);
  while (location != NULL)
  {
    gap += (location - Text);
    real_Text[gap] = '\0';

    length += (new_l - key_l);

    real_Text = (char *)realloc(real_Text, length * sizeof(char));
    strcat(real_Text, new);
    gap += new_l;

    Text = location + key_l;
    strcat(real_Text, Text);

    location = strstr(Text, key);
  }
  return real_Text;
}

//==============================================================
void sheissePrint(char array[MAX], char key_array[MIN])
{
  char key[MIN]="";
  char text[MAX]="";
  for (int32_t i = 0; i < MIN; i++)
  {
    key[i] = key_array[i];
  }
  for (int32_t i = 0; i < MAX; i++)
  {
    text[i] = array[i];
  }
  text[strlen(text)] = '\0';
  key[strlen(key)] = '\0';
  printf("After:\n");
  for (int32_t i = 0; i < strlen(text); i++){
    if (strncmp(&text[i], key , strlen(key)) == 0)
    {
      printf(RED"%.*s"RESET, (int32_t)strlen(key),&text[i]);
      i +=strlen(key)-1;
    }
    else
    {
      // printf("%c", text[i]);
      printf("text[%d] = %c, key[%d] = %c \n", i,text[i], i, key[i]);
    }
  }
  // printf("\n");
}
