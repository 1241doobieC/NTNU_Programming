#include <stdio.h>
#include "myprintf.h"


void myprintf(char *format, ...)
{
    int32_t         num = 0;
    char            *s = NULL;
    va_list         arg;
    va_start(arg, format);
    while (*format)
    {
        if (*format != '%')
        {
            putchar(*format);
            format++;
        }
        else
        {
            format++;
            switch(*format)
            {
                case 'd':
                case 'i':
                    num = va_arg(arg, int32_t);
                    if (num < 0) 
                    {
                        fputc('-' , stdout);
                        num = num * (-1);
                    }
                    parseInt(num);
                    format++;
                break;
                case 'x':
                case 'X':
                    num = va_arg(arg, uint32_t);
                    parseHex(num);
                    format++;
                break;
                case 's':
                    s = va_arg(arg, char*);
                    for (int32_t i = 0; i < strlen(s); i++)
                    {
                       fputc(s[i], stdout);
                    }
                    format++;
                break;
            }
        }
    }
    
    va_end(arg);
    
}
int32_t parseInt(int32_t num)
{
    int32_t         a = num;
    int32_t         zero = 0;
    int32_t         count = 0;
    int32_t         temp[32] = {0};

    // printf("\nNumber is %d\n", num);
    if (num == 0)
    {
        fputc('0' , stdout);
        return zero;
    } 
    while (a != 0)
    {
        a /= 10;
        count++;
    }
    a = num;
    for (int32_t i = count - 1; i >= 0; i--)
    {
        temp[i] = a % 10;
        a /= 10;
    }
    for (int32_t i = 0; i < count; i++)
    {
       char cc = temp[i] + '0';
       fputc((int32_t)cc, stdout);
    }
    return 1;
}

int32_t parseHex(int32_t num)
{
    int32_t         a = num;
    int32_t         count = 0;
    // int32_t         temp[16] = {0};
    char            charValue[32] = {0};
    if (a == 0)
    {
       fputc('0', stdout);
       return 1;
    }else{
        while(a != 0)
        {
            a /= 16;
            count++;
        }
        a = num;
        for (int32_t i = count - 1; i >= 0; i--)
        {
            if (a % 16 > 9)
            {
               int32_t ran = a % 16;
               ran = ran - 9;
               switch(ran){
                   case 1:
                    charValue[i] = 'A';
                   break;
                   case 2:
                    charValue[i] = 'B';
                   break;
                   case 3:
                    charValue[i] = 'C';
                   break;
                   case 4:
                    charValue[i] = 'D';
                   break;
                   case 5:
                    charValue[i] = 'E';
                   break;
                   case 6:
                    charValue[i] = 'F';
                   break;
               }
               a /= 16;
            }
            else
            {
                int32_t ran = a % 16;
                charValue[i] = ran + '0';
                a /= 16;
            }
            
        }
        for (int32_t i = 0; i < count; i++)
        {
            fputc((int32_t)charValue[i], stdout);
        }
        
        return 1;
    }
}