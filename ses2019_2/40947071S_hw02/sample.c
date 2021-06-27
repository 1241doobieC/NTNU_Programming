#include <stdio.h>
#include <stdint.h>
#include "bignum.h"
int main()
{
  sBigNum a, b;
  set( &a, "24" );
  set( &b, "365" );
  print( a );
  print( b );

  if( compare( a, b ) == 1 ){
    printf( "a is greater than b. Return Value is:%d\n", compare( a, b ) );
    }
  else if( compare( a, b ) == 0 ){
    printf( "a is equal to b.\n" );
    }
  else{
    printf( "a is smaller than b. Return Value is:%d\n", compare( a, b ) );
  }

  printf("Digit of a: %d\n",digits(a));
  printf("Digit of b: %d\n",digits(b));

  sBigNum ans, q, r;
  printf("Add: ");
  add( &ans, a, b );
  print( ans );
  printf("\n");
  //
  // subtract( &ans, a, b );
  // print( ans );
  //
  printf("Mult: ");
  multiply( &ans, a, b );
  print( ans );
  printf("\n");
  //
  // divide( &q, &r, a, b );
  // print( q );
  // print( r );
  //
  // power( &ans, 20, 10 );
  // print( ans );
  //
  // combine( &ans, 20, 10 );
  // print( ans );

  return 0;
}
