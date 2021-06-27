#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef union {
  double d;
  struct {
    unsigned long mantissa: 52;
    unsigned long exponent: 11;
    unsigned long sign;
  }__attribute__((packed)) iEE;
}__attribute__((packed)) Dou_stru ;
// Prints the binary representation
void printBin(int64_t n, int64_t i);

int main(){
  double input = 0;
  printf("Please enter a floating -point number (double precision): ");
  scanf("%lf", &input);

  Dou_stru answer, tmp;
  answer.d = input;
  tmp.d = input;

  //Sign
  if (input <= 0)  {
    printf("Sign: 1\n");
    tmp.iEE.sign = 1;
  }
  else {
    printf("Sign: 0\n");
    tmp.iEE.sign = 0;
  }
  //============================================
  //Expo
  printf("Exponent: ");
  printBin(answer.iEE.exponent, 11);
  printf("\n");

  //fra
  printf("Fraction: ");
  printBin(answer.iEE.mantissa, 52);
  printf("\n");
  //tmp for mantissa
  unsigned long tmp_m = answer.iEE.mantissa;
  int32_t manti[52]={0};
  for (int32_t i = 0; tmp_m >= 1 ; i++) {
    manti[i] =tmp_m % 2;
    tmp_m /= 2;
  }

  //Total
  printf("%.4lf = (-1)^%d * (1", input, (int32_t)tmp.iEE.sign);
    for(int i=51; i>=0 ;i--){
        if(manti[i] == 1){
            printf(" + 2^%d",(51-i+1)*-1);
        }
    }
    printf(") * 2^(%d-1023)\n",(int32_t)tmp.iEE.exponent);
  return 0;
}

void printBin(int64_t n, int64_t i)
{
    // Prints the binary representation
    int32_t k = 0;
    for (k = i-1; k >= 0; k--) {

        if ((n >> k) & 1) printf("1");
        else printf("0");
      }
}
