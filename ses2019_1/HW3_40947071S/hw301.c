#include<stdio.h>
#include<stdint.h>


int main()
{
  int32_t width, height, start=1,b=0;
  printf("Please enter the width: ");
  scanf("%d", &width );
  printf("Please enter the height: " );
  scanf("%d", &height );
  int32_t array[height][width],  total = 1;
  int32_t num_width = width;
  int32_t num_height = height;

  while (start<= width *  height) {
    for (int32_t i = 0; i < num_width-1; i++) {  // First part
      array[b][i+b]=start;
      start++;
      if(start>(width * height)) break;
    }

    for (int32_t i = 0; i < num_height-1; i++) {  //Second part
      array[i+b][num_width-1+b]=start;
      start++;
      if(start>(width * height)) break;
    }

    for (int32_t i = num_width-1; i >= 0; i--) {  //Third part
      array[num_height-1+b][i+b]=start;
      start++;
      if(start>(width * height)) break;
    }
    for (int32_t i = num_height-2; i > 0; i--) {  //Last part
      array[i+b][num_width-(num_width-b)]=start;
      start++;
      if(start>(width * height)) break;
    }
    num_width = num_width -2;
    num_height = num_height -2;
    b++;

  }  //end of loop
  for (int32_t i = 0; i < height; i++) {
    for (int32_t j = 0; j < width; j++) {
        printf("%4d ",array[i][j] );
    }
    printf("\n");
  }

  printf("\n");
  return 0;
  }
