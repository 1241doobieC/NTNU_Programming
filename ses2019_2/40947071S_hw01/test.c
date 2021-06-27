#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int main(void)
{

  FILE* file = NULL;
  file = fopen("PleaseOpenMe.txt", "r");

  if (file == NULL)
  {
    printf("Error(Strerror): %s \n", strerror(errno));
    perror("Error(perror)");
  }
}
