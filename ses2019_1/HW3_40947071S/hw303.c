#include<stdio.h>
#include<stdint.h>

int main()
{
  int32_t num=0;
  printf("Start! \n" );
  printf("Please enter an integer: ");
  scanf("%d", &num);

  if (num < 0) {
    printf("Invalid Input \n");
    return 0;
  }
  int32_t first_int = num;
  int32_t flag=1;
  while (1) {
      if (flag == 1) {
        if (num != 10 && num != 35 && num != 11 && num != 20 && num != 78)
        {
            num = 8591;
        }
        else flag =2;
      }  //flag ==> 1
      if (flag == 2) {
        switch (num) {
          case 35:
          case 10:
          printf("S1 \n");
          printf("Please enter an integer: ");
          scanf("%d", &num);
          if (num != 19 && num!=12 && num !=36) {
            num= 35;
            // flag ==2;
            }
            //else flag =2;
          break;

          case 11:
          printf("S3 \n");
          printf("Please enter an integer: ");
          scanf("%d", &num);
          printf("S4 \n");
          printf("Please enter an integer: ");
          scanf("%d", &num);
          num =12;
          break;

          case 20:
          case 78:
          printf("S5 \n" );
          printf("Please enter an integer: ");
          scanf("%d", &num);
          if (num != 1 && num!=2) {
            printf("Start! \n" );
            printf("Please enter an integer: ");
            scanf("%d", &num);
          //  flag ==1;
          }
        //  else flag ==2 ;
          break;
        }
      } //Flag ==2
      switch (num) {

        case 35:
        case 10:
        printf("S1 \n");
        printf("Please enter an integer: ");
        scanf("%d", &num);
        if (num != 19 && num!=12 && num !=36) {
          num= 35;
          // flag ==2;
          }
          //else flag =2;
        break;

        case 11:
        printf("S3 \n");
        printf("Please enter an integer: ");
        scanf("%d", &num);
        printf("S4 \n");
        printf("Please enter an integer: ");
        scanf("%d", &num);
        num =12;
        break;

        case 20:
        case 78:
        printf("S5 \n" );
        printf("Please enter an integer: ");
        scanf("%d", &num);
        if (num != 1 && num!=2) {
          printf("Start! \n" );
          printf("Please enter an integer: ");
          scanf("%d", &num);
        //  flag ==1;
        }
      //  else flag ==2 ;
        break;


        case 43:
        case 19:
        printf("S2 \n");
        printf("Please enter an integer: ");
        scanf("%d", &num);
        if (num != 43 && num!=99) {
          printf("Start! \n" );
          printf("Please enter an integer: ");
          scanf("%d", &num);
        }
        break;

        case 99:
        printf("Final! \n" );
        printf("Please enter an integer: ");
        scanf("%d", &num);
        num =99;
        break;

        case 12:
        case 36:
        printf("S6 \n");
        printf("Please enter an integer: ");
        scanf("%d", &num);
        if (num != 108) {
          printf("S5! \n" );
          printf("Please enter an integer: ");
          scanf("%d", &num);
          num = 20;
        }
        break;

        case 1:
        printf("S4 \n");
        printf("Please enter an integer: ");
        scanf("%d", &num);
        num =12;
        break;

        case 2:
        num = 12;
        break;

        case 108:
        num = 99;
        break;

        default:

      // printf("Start! \n");
        printf("Please enter an integer: ");
        scanf("%d", &num);
      /*  if (num != 10 && num != 35 && num != 35 && num != 11 && num != 20 && num != 78) {
          printf("Start! \n");
          printf("Please enter an integer: ");
          scanf("%d", &num);
          num = first_int;
          flag ==1;
        }*//*else
        flag ==2;*/
        break;

        case 8591:
        printf("Start! \n");
        printf("Please enter an integer: ");
        scanf("%d", &num);
        if (num == 10 || num == 35 || num == 35 || num == 11 || num == 20 || num == 78) {
          //num = first_int;
           flag ==2;
        }
        break;
      }
}
  return 0;
}
