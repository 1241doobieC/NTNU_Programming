#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>

void show_integer(uint8_t *a);
void show_change(uint8_t *num, int32_t *posi);
int main()
{
  int64_t num=0;
  int32_t position=0, flag=1, new_v=0, state=1; //0==>true
  printf("Please enter an integer: ");
  scanf(" %ld", &num);
  printf("The integer: %ld\n", num );
  uint8_t *num_ptr= (uint8_t *) &num;
  show_integer(num_ptr);
  while (state != 0)
  {
    flag = 1;
    while (flag!=0)  //Check Validity
    {
      printf("Please enter the position(1-8, 0:End): ");
      scanf(" %d", &position);
      if (position > 8 || position < 0)      printf("Invalid Input. \n");
      else      flag = 0;
    }
    if(position == 0)
    {
      state = 0;
      break;
    }
    else
    {
      flag = 1;
    }
    while (flag != 0)
    {
      printf("Please enter the new value(0-255): ");
      scanf("%d", &new_v );
      if (new_v > 255 || new_v < 0)   printf("Invalid Input.\n");
      else flag = 0;
    }
    printf("The integer: %d\n", new_v);
    *(num_ptr+(position-1))= new_v;
    show_integer(num_ptr);
  }
  return 0;
}
void show_integer(uint8_t *num)
{
  int32_t a=7;
  for (int32_t i = 0; i < 8; i++)
  {
    printf("(%d) 0x%02X",i+1, *(num+i) );
    a--;
  }
  printf("\n");
  return;
}
