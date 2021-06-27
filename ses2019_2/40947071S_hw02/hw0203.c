#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef union{
  struct {
  unsigned char b1:1;
  unsigned char b2:1;
  unsigned char b3:1;
  unsigned char b4:1;
  unsigned char b5:1;
  unsigned char b6:1;
  unsigned char b7:1;
  unsigned char b8:1;
  } bits;
  unsigned char byte;
} uByte;

int main()
{
  uByte iByte = {0};
  int32_t input = 0;
  printf("Please enter a byte (0-255):");
  scanf("%hhd", &iByte.byte);
  do {
    printf("Data: %d  %d%d%d%d%d%d%d%d\n", iByte.byte,
                                           iByte.bits.b8,iByte.bits.b7,iByte.bits.b6,
                                           iByte.bits.b5,iByte.bits.b4,iByte.bits.b3,
                                           iByte.bits.b2,iByte.bits.b1);
    // printf("test: %d\n ", iByte.bits.b9);
    printf("Flip bit (1-8, 0: exit): ");
    scanf("%d", &input);
    switch (input)
    {
      case 0:
      printf("Bye\n");
      break;
      case 1:
      iByte.bits.b8 = !iByte.bits.b8;
      break;
      case 2:
      iByte.bits.b7 = !iByte.bits.b7;
      break;
      case 3:
      iByte.bits.b6 = !iByte.bits.b6;
      break;
      case 4:
      iByte.bits.b5 = !iByte.bits.b5;
      break;
      case 5:
      iByte.bits.b4 = !iByte.bits.b4;
      break;
      case 6:
      iByte.bits.b3 = !iByte.bits.b3;
      break;
      case 7:
      iByte.bits.b2 = !iByte.bits.b2;
      break;
      case 8:
      iByte.bits.b1 = !iByte.bits.b1;
      break;
    }
  } while(input != 0);
 return 0;
}
