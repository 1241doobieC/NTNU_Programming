#include "bignum.h"

int32_t set( sBigNum *pNum, char *str ){
  int32_t leng = strlen(str);

  //check
  for (int32_t i = 0; i < leng; i++) {
    if ((str[i] >'9' && str[i]<'0')&& str[i]!= '-') return 0;
    if (i!=0 && (str[i]<'0' || str[i] > '9'|| str[i] =='-')) return 0;
  }

  if (str[0] == '-') { //negative
    pNum -> sign = -1;
    if (str[1] == '0'){
      printf("First digit could NOT be 0. \n");
       return 0;
     }
    for (int32_t i = 1; i < leng ; i++) {
      pNum -> value[i] = str[i]-'0';
    }
  }
  else if(str[0]>1 || str[0] <= 9){ //positive
    pNum -> sign = 1;
    if (str[0] == '0'){
      printf("First digit could NOT be 0. \n");
      return 0;
    }
    for (int32_t i = 0; i < leng; i++) {
      pNum -> value[i] = str[i]-'0';
    }
  }

  if (str[0] == '-') {
    pNum -> length = leng - 1;
    pNum -> digit = leng - 1;
  }
  else {
    pNum -> length = leng ;
    pNum -> digit = leng;
  }


  return 1;
}

void print( const sBigNum num ){
  sBigNum temp = num;

  if (temp.sign == -1) {
    printf("-" );
    for (int32_t i = 1; i <= temp.length; i++) {
      printf("%d", temp.value[i] );
    }
  }
  else if (temp.sign ==1){
    for (int32_t i = 0; i < temp.length; i++) {
      printf("%d", temp.value[i] );
    }
  }
  printf("\n");
}

int32_t compare( const sBigNum num01 , const sBigNum num02 )
{
  sBigNum temp1 = num01, temp2 = num02;
  if (temp1.sign > temp2.sign) return 1;
  else if (temp1.sign < temp2.sign) return -1;
  else if (temp1.sign == 1 && temp2.sign == 1) {
    //length compare
    if (temp1.length > temp2.length) return 1;
    else if(temp1.length < temp2.length) return -1;
    else{
      for (int32_t i = 0; i < temp1.length; i++) {
        if (temp1.value[i] > temp2.value[i]) return 1;
        else if(temp1.value[i] < temp2.value[i]) return -1;
      }
      if(temp1.value[temp1.length-1] == temp2.value[temp1.length-1]) return 0;
    }
  }
  else{  //negative
    if (temp1.length > temp2.length) return -1;
    else if(temp1.length < temp2.length) return 1;
    else{
      for (int32_t i = 0; i < temp1.length; i++) {
        if (temp1.value[i] > temp2.value[i]) return -1;
        else if(temp1.value[i] < temp2.value[i]) return 1;
      }
      if(temp1.value[temp1.length-1] == temp2.value[temp1.length-1]) return 0;
    }
  }
}

int32_t digits( const sBigNum num ){
  sBigNum temp = num;
  return temp.digit;
}

void add( sBigNum *pResult ,const sBigNum num01 , const sBigNum num02 ){
  sBigNum a1 = num01, a2 = num02;
  int32_t t = 0;

  int count = 1;
//==================================
  if (a1.sign > a2.sign ) { // a1 > 0, a2 < 0
    if (a1.length > a2.length) {
      //a1 - a2
      pResult -> sign = 1;
      pResult -> length = a1.length;
      pResult -> digit = a1.digit;
      t = a2.length;
      // printf("t:%d \n", t);
      for (int32_t i = a1.length - 1; i >= 0; i--) {
        if (a1.value[i] - a2.value[t] >= 0) pResult -> value[i] = a1.value[i] - a2.value[t];
        else {
          printf("Count:%d, t:%d\n", count, t);
          count++;
          a1.value[i] += 10;
          a1.value[i-1] -= 1;
          pResult -> value[i] = a1.value[i] - a2.value[t];
        }
        t--;
        if (t < 0) {
          t = 0;
          a2.value[t] = 0;
        }
      }
      for (int32_t i = 0; i < pResult -> length; i++) {
        if (pResult -> value[i] == 0)
        {
          // printf("here \n");
          for (int32_t j = 1; j < pResult -> length; j++) {
            pResult -> value[j-1] = pResult -> value[j];
          }
          (pResult -> length)--;
        }else break;
      }

    } else if (a1.length < a2.length) {
      //b - a
      pResult -> sign = -1;
      pResult -> length = a2.length;
      pResult -> digit = a2.digit;
      t = a1.length-1;
      for (int32_t i =a2.length; i > 0; i--) {
        if (a2.value[i] - a1.value[t] >= 0){
          pResult -> value[i] = a2.value[i] - a1.value[t];
        }
        else{
          a2.value[i] += 10;
          a2.value[i-1] -= 1;
          pResult -> value[i] = a2.value[i] - a1.value[t];
        }
        t--;
        if (t < 0) {
          t = 0;
          a1.value[t] = 0;
        }
      }
      for (int32_t i = 1; i < pResult -> length; i++) {
        if (pResult -> value[i] == 0)
        {
          printf("Here \n");
          for (int32_t j = 2; j <= pResult -> length; j++) {
            pResult -> value[j-1] = pResult -> value[j];
          }
          (pResult -> length)--;
        }else break;
      }
    }
    else{
      pResult -> sign = 1;
      pResult -> length = 0;
      pResult -> digit = 1;

      pResult -> value[0] = 0;
      printf("%d", pResult -> value[0]);
    }
//==================================
  } else if (a1.sign < a2.sign){  // a1 < 0, a2 > 0
      if (a1.length > a2.length) {
        //-a + b < 0
        pResult -> sign = -1;
        pResult -> length = a1.length;
        pResult -> digit = a1.digit;

        t = a2.length-1;
        printf("t: %d\n", t);
        printf("a1.length =%d, value is %d \n",a1.length , a1.value[a1.digit]);
        for (int32_t i = a1.length; i >= 0; i--) {

          if (a1.value[i] - a2.value[t] >= 0){
            pResult -> value[i] = a1.value[i] - a2.value[t];
          }

          else {
            a1.value[i] += 10;
            a1.value[i-1] -= 1;
            pResult -> value[i] = a1.value[i] - a2.value[t];
          }
          t--;
          if (t < 0) {
            t = 0;
            a2.value[t] = 0;
          }
        }
        for (int32_t i = 1; i < pResult -> length; i++) {
          if (pResult -> value[i] == 0)
          {
            printf("Here \n");
            for (int32_t j = 2; j <= pResult -> length; j++) {
              pResult -> value[j-1] = pResult -> value[j];
            }
            (pResult -> length)--;
          }else break;
        }

      }
      else if (a1.length < a2.length) {
        // b - a  > 0
        pResult -> sign = 1;
        pResult -> length = a2.length;
        pResult -> digit = a2.digit;

        t = a1.length;
        for (int32_t i =a2.length-1; i >= 0; i--) {
          if (a2.value[i] - a1.value[t] >= 0){
            pResult -> value[i] = a2.value[i] - a1.value[t];
            // printf("(greater) t: %d \n", t);
          }
          else{
            a2.value[i] += 10;
            a2.value[i-1] -= 1;
            pResult -> value[i] = a2.value[i] - a1.value[t];
            // printf("(smaller) t: %d \n", t);
          }
          t--;
          if (t < 0) {
            t = 0;
            a1.value[t] = 0;
          }
        }
      }
      else{
        pResult -> sign = 1;
        pResult -> length = 0;
        pResult -> digit = 1;

        pResult -> value[0] = 0;
        printf("%d", pResult -> value[0]);
        }
//==================================
}else{ //(aUb) + || (a && b) -
    if (a1.sign == 1 && a2.sign == 1) { //(aUb) +
      pResult -> sign = 1;
      if(a1.length > a2.length)
      {
        pResult -> length = a1.length;
        pResult -> digit = a1.digit;
        t = a2.length-1;
        int32_t mmm = 0;
        for (int32_t i = a1.length-1; i >= 0 ; i--) {
          if ((a1.value[i] + a2.value[t])< 10) {
            pResult -> value[i] = a1.value[i] + a2.value[t];
          }
          else
          {
            mmm = (a1.value[i] + a2.value[t]) % 10;
            a1.value[i-1] += 1;
            pResult -> value[i] = mmm;
            mmm = 0;
          }
          t--;
        }
      }
      else if(a1.length < a2.length)
      {
        pResult -> length = a2.length;
        pResult -> digit = a2.digit;
        t = a1.length -1;
        int32_t mmm = 0;
        for (int32_t i = a2.length-1; i >= 0 ; i--) {
          if ((a2.value[i] + a1.value[t])< 10) {
            pResult -> value[i] = a2.value[i] + a1.value[t];
          }
          else
          {
            mmm = (a2.value[i] + a1.value[t]) % 10;
            a2.value[i-1] += 1;
            pResult -> value[i] = mmm;
            mmm = 0;
          }
          t--;
        }
      }
      else{
        pResult -> length = a1.length;
        pResult -> digit = a1.digit;
        /*
          length and digit may need one more
        */
        t = a1.length-1;
        int32_t mmm = 0;
        for (int32_t i = a1.length-1; i >= 0 ; i--) {
          if ((a1.value[i] + a2.value[t])< 10) {
            pResult -> value[i] = a1.value[i] + a2.value[t];
          }
          else
          {
            mmm = (a1.value[i] + a2.value[t]) % 10;
            if (i - 1 < 0) {
              // printf("It happens \n");
              pResult -> length += 1;
              pResult -> digit += 1;
              a1.length = a1.length+1;
              a1.digit+=1;
              for (int32_t i = 2; i < pResult -> length; i++) {
                pResult -> value[0] = 1;
                pResult -> value[i-1] = pResult -> value[i];
              }
              break;
            }
            a1.value[i-1] += 1;
            pResult -> value[i] = mmm;
            mmm = 0;
          }
          t--;
        }
      }

  //=====================
    }else{ //(a && b) < 0
      pResult -> sign = -1;
      if (a1.length > a2.length)
      {
        pResult -> length = a1.length;
        pResult -> digit = a1.digit;
        t = a2.length;
        // printf("a2.length-1: %d pResult -> value[a2.length-1]:%d, \n", t,pResult -> value[a2.length-1]);
        int32_t mmm = 0;
        for (int32_t i = a1.length; i >= 0 ; i--) {
          if ((a1.value[i] + a2.value[t])< 10) {
            pResult -> value[i] = a1.value[i] + a2.value[t];
            // printf("More than 10 %d\n",i);
          }
          else
          {
            // printf("Less than 10 %d\n",i);
            mmm = (a1.value[i] + a2.value[t]) % 10;
            a1.value[i-1] += 1;
            pResult -> value[i] = mmm;
            mmm = 0;
          }
          t--;
        }
      }
      else if (a1.length < a2.length)
      {
        pResult -> length = a2.length;
        pResult -> digit = a2.digit;
        t = a1.length;
        int32_t mmm = 0;
        for (int32_t i = a2.length; i >= 0 ; i--) {
          if ((a2.value[i] + a1.value[t])< 10) {
            pResult -> value[i] = a2.value[i] + a1.value[t];
          }
          else
          {
            // printf("Less than 10 %d\n",i);
            mmm = (a2.value[i] + a1.value[t]) % 10;
            a2.value[i-1] += 1;
            pResult -> value[i] = mmm;
            mmm = 0;
          }
          t--;
        }
      }
      else
      {
        pResult -> length = a2.length;
        pResult -> digit = a2.digit;
        t = a1.length;
        int32_t mmm = 0;
        for (int32_t i = a2.length; i >= 0 ; i--) {
          if ((a2.value[i] + a1.value[t])< 10) {
            pResult -> value[i] = a2.value[i] + a1.value[t];
          }
          else
          {
            // printf("Less than 10 %d\n",i);
            mmm = (a2.value[i] + a1.value[t]) % 10;
            if (i - 2 < 0) {
              // printf("It happens \n");
              pResult -> length += 1;
              pResult -> digit += 1;
              a2.length = a2.length+1;
              a2.digit+=1;
              for (int32_t i = 2; i < pResult -> length; i++) {
                pResult -> value[1] = 1;
                pResult -> value[i-1] = pResult -> value[i];
              }
              break;
            }
            a2.value[i-1] += 1;
            pResult -> value[i] = mmm;
            mmm = 0;
            // printf("i = %d \n", i);
          }
          t--;
        }
      }
    }
  }

  return;
}

void multiply( sBigNum *pResult , const sBigNum num01 , const sBigNum num02 )
{
  sBigNum temp = num01;
  sBigNum a1 = num01, a2 = num02;
  if (a1.sign == 1 && a2.sign == 1) {
    pResult -> sign = 1;
    int64_t a2_count = 0;
    int32_t base = 1;
    int32_t position = a2.digit-1;
    for (int64_t i = 0; i < a2.digit; i++) {
      a2_count += a2.value[position] * base;
      position--;
      base *=10;
    }
    while (a2_count != 0) {
      add(pResult , a1, a1);
      
      a2_count--;
    }

  }
  else if (a1.sign == -1 && a2.sign == -1 ) {
    pResult -> sign = 1;
  }
  else
  {
    pResult -> sign = -1;
  }
}
