#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include"test.h"
#include"hw05_CHECK_FILES.h"

int main()
{

  printf("Before :\n");
  // printf("%d\n", array_size );
  for (size_t i = 0; i < array_size; i++) {
    printf("%d ", array[i] );
  }
  printf("\n");

  sort_array(array, array_size);

  printf("After :\n");
  for (size_t i = 0; i < array_size; i++) {
    printf("%d ", array[i] );
  }
  printf("\n");

  return 0;
}
