#include<stdio.h>
#include<stdint.h>
#include<string.h>
// #include<time.h>
#include<stdlib.h>
#include"test2.h"
#include"hw05_CHECK_FILES.h"

int main()
{

  printf("The matrix is \n");
  for (size_t i = 0; i < 4; i++)
  {
    for (size_t j = 0; j < 4; j++)
    {
      printf("%d ", matrix[i][j] );
    }
    printf("\n");
  }
  printf("\n");
  int32_t ans = calculate_matrix(matrix);
  printf("The determinant is: %d \n", ans );
  return 0;
}
