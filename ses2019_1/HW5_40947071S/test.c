#include<stdio.h>
#include<stdint.h>
int32_t p(int32_t, int32_t);
int main()
{
  int32_t a=0, b=0;
  printf("Please enter a and b: \n");
  scanf("%d %d", &a, &b);
  p(a, b);

  printf("\n %d\n",p(a, b) );
  return 0;
}
int32_t p(int i, int N)
{
  return (i < N && printf("%d \n", i) && !p(i+1, N))
          || printf("%d \n", i);
}
