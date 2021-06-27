#include <stdio.h>
#include <stdint.h>

int main()
{

  int32_t card01,card02,card03,card04,card05;
  printf("Please enter 5 cards: ");
  scanf("%d%d%d%d%d", &card01, &card02, &card03, &card04, &card05);
  int32_t card[]={card01, card02, card03, card04, card05};
  int32_t max;
  int32_t result=0;
  //For Straight
  int32_t same_color=0;
  int32_t different_color=0;
  int32_t remain=0;
  //New Beginning
  int32_t remain01=0;
  int32_t quo=0;
  int32_t three=0;
  if (
    card01 < 1 || card01 > 52 ||card02<1||card02>52 || card03<1||card03>52
    ||card04<1 || card04>52 || card05<1 || card05>52
    ) {
    printf("Card Number can not be greater than 52 or smaller than 0. \n");
    return 0;
  }
  else if
//=====If Condiction=====
  (
    card01 == card02  || card01 == card03 || card01 == card04 || card01 == card05
    || card02 == card03 || card02 == card04 || card02 == card05
    || card03 == card04 || card03 == card05
    || card04 == card05
  )
//=====If Condiction=====
  {
    printf("Card number can not be same! \n" );
    return 0;
  }
// =====Main Function=====
  else
  {
//===sort from small number
    for (int32_t i = 0; i < 5; i++) {
      for (int32_t j = 0; j < i; j++) {
        if (card[j]>card[i]) {
          /* code */
          max= card[j];
          card[j]=card[i];
          card[i]=max;
        }
      }
    }
//===sort from small number
  }

/*
Straight
*/
  for (int32_t i = 0; i < 5; i++) {
    for (int32_t j = 0; j < (i); j++) {
      /* code */
      if (card[i]-card[j]==1) {
        result = 2;
      }
      else result =99;
    }
  }
  if (card[0] % 13 !=0 && card[1] % 13 !=0 && card[2] % 13 !=0 &&
    card[3] % 13 !=0 && card[4] % 13 !=0 )
    {
      result= 1;
      for (int32_t i = 0; i < 5; i++) {
        for (int32_t j = 0; j < (i); j++) {
          /* code */
          if (card[i]-card[j]==1) {
            result = 2;
          }
          else {result =99;
          break;}
        }
      }
    }
    for (int32_t i = 0; i < 5; i++) {
      same_color = same_color + (card[i] / 13);
      remain = remain + (card[i] % 13);
    }
    for (int32_t i = 0; i < 5; i++) {
      if (((same_color>2 && same_color<=5) && ((remain)<= 10))
      || ((same_color>7 && same_color<=10) && ((remain)<= 10))
      || ((same_color>12 && same_color<=15) && ((remain)<= 10))
      || ((same_color>17 && same_color<=20) && ((remain)<= 10))) {
        result = 99;
      }
    }

  for (int32_t i = 0; i < 5; i++) {
    for (int32_t j = 0; j < i; j++) {
        for (int32_t k = 0; k < j; k++) {
          if (card[i] % 13 == card[j]%13 == card[k] % 13) {
            result=5; //Three of a kind
            for (int32_t l = 0; l < k; l++) {
                for (int32_t m = 0; m < l; m++) {
                  if (card[i]%13 != card[j]%13 && card[i]%13 != card[k]%13 && card[i]%13 != card[l]%13 && card[i]%13 != card[m]%13 &&
                      card[j]%13 != card[k]%13 && card[j]%13 != card[l]%13 && card[j]%13 != card[m]%13 &&
                      card[k]%13 != card[l]%13 && card[k]%13 != card[m]%13 &&
                      card[l]%13 != card[m]%13){
                          result=99; //default
                  }
                  if (card[i] % 13 == card[j]%13 == card[k] % 13 == card[l] %13 ||
                      card[i] % 13 == card[j]%13 == card[k] % 13 == card[m] %13 ||
                      card[i] % 13 == card[j]%13 == card[l] % 13 == card[m] %13 ||
                      card[i] % 13 == card[k]%13 == card[l] % 13 == card[m] %13 ||
                      card[j] % 13 == card[k]%13 == card[l] % 13 == card[m] %13 ) {
                        result=6;//Four of a Kind.
                  }
                }

            }
          }
        }
    }
  }
  for (int32_t i = 0; i < 5; i++) {
    for (int32_t j = 0; j < i; j++) {
      if (card[j] % 13 == card[i]%13) {
        remain01++;
      }
      if (remain01 ==1) {
        result = 3;
      }
      else if (remain01==2) {
        result = 4;
      }
    }
  }


  switch (result) {
  /*  case 0:
    printf("Nothing. \n ");
    break;*/
    case 1:
    printf("Straight flush. \n");
    break;
    case 2:
    printf("Straight. \n");
    break;
    case 3:
    printf("One Pair. \n");
    break;
    case 4:
    printf("Two pairs.\n" );
    break;
    case 5:
    printf("Three of a Kind.\n" );
    break;
    case 6:
    printf("Four of a Kind.\n" );
    break;
    case 7:
    printf("Full House. \n");
    default:
    printf("High Card.\n");
    break;
  }
  return 0;
}
