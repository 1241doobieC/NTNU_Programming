#include <stdio.h>
#include <stdint.h>

void max(int32_t a, int32_t b);
int main(void)
{
    int32_t a = 0;
    int32_t b = 0;

    printf("Given a:");
    scanf("%d", &a);
    printf("Given b:");
    scanf("%d", &b);

    max(a,b);
}
void max(int32_t x, int32_t y)
{
    int32_t r = 0;
    r = x ^ ((x ^ y) & -(x < y));
    printf("%d is greater. \n", r);
}