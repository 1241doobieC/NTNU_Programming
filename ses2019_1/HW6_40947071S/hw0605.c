#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include <math.h>
#define FALSE 0
#define TRUE 1
#include "check_funs.h"
#include "test.h"

int main()
{
  if(check_valid(player1) == 0) printf("Invalid Input : player1\n");
  else if(check_valid(player2) == 0) printf("Invalid Input : player2\n");
  else if(check_valid(player3) == 0) printf("Invalid Input : player3\n");
  else if(check_valid(player4) == 0) printf("Invalid Input : player4\n");
  else
  {
    printf( "Before:\n" );
    print_card( player1 );
    print_card( player2 );
    print_card( player3 );
    print_card( player4 );

    printf( "Type 01:\n" );
    sort_card( player1 , func01 );
    sort_card( player2 , func01 );
    sort_card( player3 , func01 );
    sort_card( player4 , func01 );
    print_card( player1 );
    print_card( player2 );
    print_card( player3 );
    print_card( player4 );

    printf( "Type 02:\n" );
    sort_card( player1 , func02 );
    sort_card( player2 , func02 );
    sort_card( player3 , func02 );
    sort_card( player4 , func02 );
    print_card( player1 );
    print_card( player2 );
    print_card( player3 );
    print_card( player4 );

    printf( "Type 03:\n" );
    sort_card( player1 , func03 );
    sort_card( player2 , func03 );
    sort_card( player3 , func03 );
    sort_card( player4 , func03 );
    print_card( player1 );
    print_card( player2 );
    print_card( player3 );
    print_card( player4 );
  }
  return 0;
}
