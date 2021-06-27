#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define DELIM_L 256

/*NO.7*/ char *mystrchr(const char *s, int c);
/*NO.1*/ char *mystrrchr(const char *s, int c);
/*NO.2*/ size_t mystrspn(const char *s, const char *accept);
/*NO.3*/ size_t mystrcspn(const char *s, const char *reject);
/*NO.4*/ char *mystrpbrk(const char *s, const char *accept);
/*NO.5*/ char *mystrstr(const char *haystack , const char *needle);
/*NO.6*/ char *mystrtok(char *str,const char *delim);
// /*NO.6-1*/ int *create_Delim_dic(char *delim);

//======================/*NO.7[DONE]*/ =======================
char *mystrchr(const char *s, int c)
{
  int32_t i = 0;
  for (i; s[i] != '\0'; i++)
  {
    if(s[i] == c)
    {
      return (char *)s + i;
    }
  }
  return NULL;
}
//======================/*NO.1[DONE]*/ =======================
char *mystrrchr(const char *s, int c)
{
  int32_t i = strlen(s)-1;
  for (i ; s[i] != '\0'; i--)
  {
    if (s[i] == c)
    {
      return (char *)s+i;
    }
  }
  return NULL;
}
//======================/*NO.2[DONE]*/ =======================
size_t mystrspn(const char *s, const char *accept)
{
  size_t found = 0;
  int32_t flag = 0 ;
  // printf("Flag: %ld \n", strlen(accept));
  for (int32_t i = 0; s[i] != '\0'; i++)
  {
    for (int32_t j = 0; accept[j] != '\0'; j++)
    {
      if (s[i] == accept[j])
      {
        found++;
        break;
      }
      else
      {
        flag++;
      }
      if(flag == strlen(accept))
      {
        return found;
      }
    }
    flag = 0;
  }

  return found;
}
//======================/*NO.3[DONE]*/ =======================
size_t mystrcspn(const char *str, const char *reject)
{
  size_t found = 0;
  size_t position = 0;
  for (int32_t i = 0; str[i] != '\0'; i++)
  {
    for (size_t j = 0; reject[j] != '\0'; j++)
    {
      if (str[i] == reject[j])
      {
        return position;
      }
    }
    position++;
  }
  return position;
}
//======================/*NO.4[DONE]*/ =======================
char *mystrpbrk(const char *str, const char *accept)
{
  for (int32_t i = 0; str[i] != '\0'; i++)
  {
    for (int32_t j = 0; accept[j] != '\0'; j++)
    {
      if(str[i] == accept[j]) return (char *)&str[i];
    }
  }

  return NULL;
}
//======================/*NO.5[DONE]*/ =======================
char *mystrstr(const char *str , const char *substr)
{
  int32_t length = 0;
  int32_t index = 0;
  int32_t flag = 0;
  while(substr[length] != '\0') length++;
  for (int32_t i = 0; substr[i] != '\0'; i++)
  {
    for (int32_t j = 0; str[j] != '\0'; j++)
    {
      if (substr[i] == str[j])
      {
        // printf("substr[%d]:%c, str[%d]: %c\n",i ,substr[i], j, str[j] );
        flag = flag + 1;
        if (flag == length)
        {
          return (char *)&str[j-1];
        }
        // printf("Flag:%d ,Length:%d\n",flag, length);
        break;
      }
    }
  }
  return NULL;
}
//======================/*NO.6*/ =======================
char *mystrtok(char *str, const char *delim)
{
  static char* record = NULL;
  char* ans = NULL, *check = NULL;
  int32_t isEnd = 1;

  if(record == NULL)
  {
      if(str != NULL) record = str;
      else return NULL;
  }

  ans = record;

  check = mystrpbrk(record,delim);

  if(check == NULL)
  {
      record = NULL;
      return ans;
  }else
  {
      do{
          isEnd = 1;
          *(check) = '\0';
          check++;

          for (int32_t i = 0; delim[i] != '\0'; i++)
          {
            if (*(check) == delim[i])
            {
              isEnd = 0;
              break;
            }
          }
      }while(!isEnd);

      record = check;

      return ans;
  }
}
