#include<stdio.h>
#include<stdint.h>

int main()
{
  int32_t num=0;
  int32_t array[10];
  int32_t digit=0;
  printf("Please enter a natural number: ");
  scanf( " %d", &num );

//=========Checking Formular=========
  if (num < 0) {
    printf("Invalid input. \n");
    return 0;
  }
  for (int32_t i = 0; i < 10; i++) {
      array[i]=num % 10;
      num = num/10;
      digit++;
      if (num == 0) {
        break;
      }
  }
  if (array[0] == 0) {
    printf("Last digit could not be 0 which will not become a valid input. \n");
    return 0;
  }
//=========Checking Formular=========

  int32_t count = digit / 2;
  int32_t last = digit;
  if (digit % 2 == 0) {
    //Even
    if (count == 2) {
      int32_t tem = array[1];
      array[1]=array[2];
      array[2]= tem;
    }
    else{
        for (int32_t i = 1; i < count; i++) {
          int32_t tem = array[last-2];
          array[last-2] = array[i];
          array[i]=tem;
          last--;
        }
    }
  }
  else{
    //Odd
    if (count == 1) {

    }
    else{
      for (int32_t i = 1; i < count; i++) {
        int32_t tem = array[last-2];
        array[last-2] = array[i];
        array[i]=tem;
        last--;
      }
    }
  }

  for (int32_t i = 0; i < digit; i++) {
    printf("%d",array[i] );
  }
  printf("\n");
  return 0;
}
