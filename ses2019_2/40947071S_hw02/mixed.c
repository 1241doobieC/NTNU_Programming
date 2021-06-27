#include "mixed.h"

//GCD
int gcd(int n1, int n2) {
    if (n2 != 0)
        return gcd(n2, n1 % n2);
    else
        return n1;
}
//LCM
int lcm(int m, int n) {
    return m * n / gcd(m, n);
}
void check(sMixedNumber *pNumber)  //Only Make it into fake fraction
{
  if (pNumber->number < 0)
  pNumber->numerator = pNumber->number * pNumber->denominator - pNumber->numerator;
  else
  pNumber->numerator = pNumber->number * pNumber->denominator + pNumber->numerator;

  pNumber->number = 0;
  return;
}
//mixed_set
int mixed_set( sMixedNumber *pNumber , int32_t a, int32_t b,int32_t c){
  int32_t flag = VALID;
  if (b >= c || c ==0 || (a!=0 && b <0)) {
    flag = INVALID;
  }else{
    pNumber->number = a;
    pNumber->numerator = b;
    pNumber->denominator = c;
  }

  return flag;
  // return -1 if invalid; otherwise , return 0.
}
//mixed_print ==> in the form of (a,b,c)
int mixed_print( const sMixedNumber s_number){
  printf("Form: (%d, %d, %d)\n", s_number.number, s_number.numerator, s_number.denominator);
  return 0;
}
//Simplfy
void simplfy(sMixedNumber *pNumber)
{
  int32_t a = 0;
  int32_t b = pNumber->numerator;
  int32_t c = pNumber->denominator;

  int32_t gcd_n = gcd(b, c);
  if (gcd_n != 1) {
    b /= gcd_n;
    c /= gcd_n;
    pNumber->numerator = b;
    pNumber->denominator = c;
  }
  pNumber->number = b / c;
  pNumber->numerator = b % c;

  if(pNumber->numerator < 0 && pNumber->number != 0) pNumber->numerator *= (-1);
  if (pNumber->denominator < 0 &&pNumber->number != 0) pNumber->denominator *= (-1);
  return;
}

//pNumber = r1 + r2
void mixed_add( sMixedNumber *pNumber , const sMixedNumber r1,const sMixedNumber r2)
{
  sMixedNumber r1_temp = r1;
  sMixedNumber r2_temp = r2;
  check(&r1_temp);
  check(&r2_temp);

  if (r1_temp.number < 0) r1_temp.numerator = r1_temp.number * r1_temp.denominator - r1_temp.numerator;
  else r1_temp.numerator = r1_temp.number * r1_temp.denominator + r1_temp.numerator;
  if (r2_temp.number < 0) r2_temp.numerator = r2_temp.number * r2_temp.denominator - r2_temp.numerator;
  else r2_temp.numerator = r2_temp.number * r2_temp.denominator + r2_temp.numerator;

  pNumber -> number = 0;
  pNumber -> denominator = r1_temp.denominator * r2_temp.denominator;
  pNumber -> numerator = r1_temp.denominator * r2_temp.numerator + r1_temp.numerator * r2_temp.denominator;

  simplfy(pNumber);
  return;
}

//pNumber = r1 - r2
void mixed_sub( sMixedNumber *pNumber , const sMixedNumber r1,const sMixedNumber r2)
{
  sMixedNumber r1_temp = r1;
  sMixedNumber r2_temp = r2;
  check(&r1_temp);
  check(&r2_temp);
  // printf("r1_temp.numerator:%d, r2_temp.numerator:%d\n",r1_temp.numerator,r2_temp.numerator);
  int32_t lcm_n = lcm(r1_temp.denominator, r2_temp.denominator);
  // printf("lcm:%d\n", lcm_n);
  if(r1_temp.denominator == r2_temp.denominator){
    pNumber -> numerator = r1_temp.numerator - r2_temp.numerator;
    pNumber -> denominator = r1_temp.denominator;
  }else{
    int32_t a = 0, b = 0, an = 0, bn = 0;
    a = r1_temp.denominator;
    b = r2_temp.denominator;
    an = r1_temp.numerator;
    bn = r2_temp.numerator;
    pNumber -> denominator = lcm_n;
    // printf("r1_temp.denominator:%d, r2_temp.denominator:%d\n",r1_temp.denominator,r2_temp.denominator);
    // printf("r1_temp.numerator:%d, r2_temp.numerator:%d\n",r1_temp.numerator,r2_temp.numerator);
    // printf("pNumber -> denominator:%d \n",pNumber -> denominator);
    a = a * (lcm_n / b);
    b = b * (lcm_n / a);
    // printf("Before==> an: %d, bn:%d\n",an, bn);
    an *= (lcm_n / r1_temp.denominator);
    bn *= (lcm_n / r2_temp.denominator);
    pNumber-> numerator = an - bn;
    // printf("After==> an: %d, bn:%d\n",an, bn);
    // printf("pNumber-> numerator: %d\n",pNumber-> numerator);
    pNumber-> denominator = lcm_n;
  }
  simplfy(pNumber);
  return;
}

// pNumber = r1 * r2
void mixed_mul( sMixedNumber *pNumber , const sMixedNumber r1,const sMixedNumber r2)
{
  sMixedNumber r1_temp = r1;
  sMixedNumber r2_temp = r2;
  check(&r1_temp);
  check(&r2_temp);

  pNumber-> denominator = r1_temp.denominator * r2_temp.denominator;
  pNumber-> numerator = r1_temp.numerator * r2_temp.numerator;
  simplfy(pNumber);
  return;
}

//pNumber = r1 / r2
void mixed_div( sMixedNumber *pNumber , const sMixedNumber r1,const sMixedNumber r2)
{
  sMixedNumber r1_temp = r1;
  sMixedNumber r2_temp = r2;
  check(&r1_temp);
  check(&r2_temp);

  pNumber-> denominator = r1_temp.denominator * r2_temp.numerator;
  pNumber-> numerator = r1_temp.numerator * r2_temp.denominator;
  simplfy(pNumber);
  return;
}
