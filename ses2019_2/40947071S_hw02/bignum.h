#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct _sBigNum{
  int32_t value[9999];
  int32_t length;
  int32_t sign;
  int32_t digit;
  long total;
} sBigNum;

void print( const sBigNum num );

int32_t set( sBigNum *pNum, char *str );

int32_t compare( const sBigNum num01 , const sBigNum num02 );

int32_t digits( const sBigNum num );

void add( sBigNum *pResult ,const sBigNum num01 , const sBigNum num02 );
//
// void subtract( sBigNum *pResult , const sBigNum num01 , const sBigNum num02 );
//
void multiply( sBigNum *pResult , const sBigNum num01 , const sBigNum num02 );
//
// void divide( sBigNum *pQuotient , sBigNum *pRemainder , const sBigNum num01 , const sBigNum num02 );
//
// int32_t power( sBigNum *pResult , int32_t n, int32_t k );
//
// int32_t combine( sBigNum *pResult , int32_t n, int32_t k );
