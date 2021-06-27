#include<stdio.h>
#include<stdint.h>

int main()
{
  double a, b ,c;
  printf("Please enter a quadratic polynomial (ax^2 + bx +c): ");
  scanf("%lf %lf %lf",&a,&b,&c );
  if (a==0) {
    printf("Invalid input. \n");
    return 0;
  }
  if (a == 1 && b==0 && c==0 ) {
    printf("The polynomial is  x^2. \n");
  }
  else if (a == 1 && b==0 && c==1) {
    printf("The polynomial is  x^2+ (%.2lf). \n", c);
  }
  else if (a == 1 && b==1 && c==0) {
    printf("The polynomial is  x^2+ x. \n");
  }
  else if (a == 1 && b==1 && c!=0 && c>0) {
    printf("The polynomial is  x^2+ x +(%.2lf). \n", c);
  }
  else if(a ==1 && b!=0 && c==0)  printf("The polynomial is  x^2 + (%.2lfx). \n",b);
  else if(a !=0 && b==0 && c==0)  printf("The polynomial is  %.2lfx^2. \n",a);
  else if(a !=0 && b==0 && c!=0)  printf("The polynomial is  %.2lfx^2 + (%.2lf). \n",a,c);
  else if(a !=0 && b!=0 && c==0)  printf("The polynomial is  %.2lfx^2 + (%.2lfx). \n",a,b);
  else   printf("The polynomial is  %.2fx^2+ (%.2fx) +(%.2f). \n",a, b, c);

  int32_t s=0, t=0;
  double intergral;
  printf("Please enter the inverval [a,b]: ");
  scanf( "%d %d",&s, &t);
   while (getchar()!= '\n');
  if (s == t || s >t) {
    printf("(a could not be same to b) OR (a could not be greater than b.)\n");
    return 0;
  }
  intergral = ((a/3.0) *t*t*t +  (b/2.0)*t*t + c*t) -
              ((a/3.0) *s*s*s + (b/2.0)*s*s + c *s);
  printf("The intergral is: %.8lf\n", intergral );

  double sum=0;

  for (int32_t i = 2; i <= 65536; i*=2) {
    sum =0;
    double g= (t-s) /(double) i;
    for (int32_t j = 0; j < i; j++) {
      double x= s+(g*j);
      sum += ((a*x*x) + (b * x) +c) * g;
    }
    printf("The Riemann sum of n=%d:  %.8lf\n",i,  sum);
  }
  return 0;
}
