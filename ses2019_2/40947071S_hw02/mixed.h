#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define TRUE (1)
#define FALSE (0)
#define INVALID (-1)
#define VALID (0)


typedef struct _sMixedNumber
{
  int32_t number;
  int32_t numerator;
  int32_t denominator;
}__attribute__((packed)) sMixedNumber ;

//GCD
int32_t gcd(int32_t number1, int32_t number2);
//LCM
int lcm(int m, int n);
//simplfy
void simplfy(sMixedNumber *pNumber);
void check(sMixedNumber *a);
// return -1 if invalid; otherwise , return 0.
int mixed_set( sMixedNumber *pNumber , int32_t a, int32_t b,int32_t c);
// in the form of (a,b,c)
int mixed_print( const sMixedNumber number);
//pNumber = r1 + r2
void mixed_add( sMixedNumber *pNumber , const sMixedNumber r1,const sMixedNumber r2);
//pNumber = r1 - r2
void mixed_sub( sMixedNumber *pNumber , const sMixedNumber r1,const sMixedNumber r2);
// pNumber = r1 * r2
void mixed_mul( sMixedNumber *pNumber , const sMixedNumber r1,const sMixedNumber r2);
//pNumber = r1 / r2
void mixed_div( sMixedNumber *pNumber , const sMixedNumber r1,const sMixedNumber r2);
