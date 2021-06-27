#include <stdio.h>
#include <stdint.h>

int main(){
	
	/*
	(b * b - (4 * a *c))
	*/
	
	float a;
	float b;
	float c;
	
	float process;
	
	printf("Please enter a quadratic polynomial (a, b, c): ");
	 scanf("%f %f %f", &a, &b,&c);
	//int ret = scanf("%f %f %f", &a, &b,&c);
	
	/* if(ret != 3)
		{
		setbuf(stdin, NULL);
		printf("Wrong Format. \n");
		
		return 0;
		}
	else 
		{
		return 3;
		}
		*/
	
	process = ((b * b) - (4 * a * c));
	if(a == 0)
	{
	printf("Wrong Input. \n");
	printf("\'a\' must not be equal to 0. \n");
	return 0;
	}
		else if(process > 0)
			{
			printf("Two distinct real roots. \n");
			}
		else if (process == 0)
			{
			printf("One real root. \n");
			}
		else
			{
			printf("No real root! \n");
			} 
	
	return 0;
}
