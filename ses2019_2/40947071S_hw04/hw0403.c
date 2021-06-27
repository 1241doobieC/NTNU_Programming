#include <stdio.h>
#include "myprintf.h"

int main()
{
    myprintf("I have %d pens, %i phones and %d euro.", -100, 0, 9999);
    printf("\n");
    myprintf("I have %x pens, %X phones." , 32, 45);
    printf("\n");
    char givenS[99] = "Money comes from STOCK!"; 
    myprintf("%s" , givenS);
    printf("\n");
    return 0;
}

