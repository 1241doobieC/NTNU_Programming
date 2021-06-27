#include<stdio.h>
#include<stdint.h>

int main()
{	
	int32_t year_normal=365,year_special=366;
	int32_t a=0,b=0,c=0,d=0;
	int32_t normal_year[12]={31 , 28, 31 , 30 , 31, 30, 31, 31, 30, 31, 30, 31};
	int32_t special_year[12]={31 , 29, 31 , 30 , 31, 30, 31, 31, 30, 31, 30, 31};
	int32_t duration_01 = 0;
	int32_t duration_02 = 0;
	int32_t sy,sm,sd,ey,em,ed;
	printf("Date Format: YYYY/MM/DD \n");
	printf("Start Date: ");
	int32_t rec = scanf("%d/%d/%d", &sy,&sm,&sd);
	if(sy < 0 || sm<1 || sm >12 || sd <1 || sd>31 || rec!=3)
	{
		printf("\nWrong Input or Format. \n");
		printf("Year starts from 0000/01/01. \n");
		printf("Month must be between 1-12. \n");
		printf("Day must be  between 1-31 and reasonable.\n");
		return 0;
	}
//First Year
	if(sy == 0)
	{
		for(int32_t i =0 ; i < (sm-1); i++)
		{
			duration_01 = duration_01 + normal_year[i];
		}
		duration_01 = duration_01 + sd;
	}
//After First Year
	else
	{
		for(int32_t i =sy; i > 0; i--)
		{
			if((i % 4 ==0 && i % 100 !=0) || (i % 400 ==0) ) a++;
			else b++;
		}
		printf("Special: %d, normal: %d \n", a, b);
		duration_01 = (a * year_special) + (b * year_normal);
		
		if(( sy % 4 ==0 && sy % 100 !=0) || (sy % 400 == 0)) //special year
		{
			for(int32_t i=0; i<(sm - 1); i++)
				{
					duration_01= duration_01 +  special_year[i];
				}
				duration_01= duration_01 -366;
			
		}
		else  
		{
			for(int32_t i=0; i<(sm - 1); i++)
				{
					duration_01= duration_01 +  normal_year[i];
				}
				duration_01= duration_01 -365;
		};
		duration_01 = duration_01 + sd;	
	}
	printf("Total days: %d \n",duration_01);
	
	
//=========================================================================


	printf("End   Date: ");
	int32_t rec02= scanf("%d/%d/%d" , &ey,&em,&ed);
	if(ey < 0 || em<1 || em >12 || ed <1 || ed>31 || rec02 !=3)
	{
		printf("\nWrong Input or Format. \n");
		printf("Year starts from 0000/01/01. \n");
		printf("Month must be between 1-12. \n");
		printf("Day must be  between 1-31 and reasonable.\n");
		printf("Start day must be earlier than end day. \n");
		return 0;
	}
//First Year
	if(ey == 0)
	{
		for(int32_t i =0 ; i < (em-1); i++)
		{
			duration_02 = duration_02 + normal_year[i];
		}
		duration_02 = duration_02 + ed;
	}
//After First Year
	else
	{
		for(int32_t i =ey; i > 0; i--)
		{
			if((i % 4 ==0 && i % 100 !=0) || (i % 400 ==0) ) c++;
			else d++;
		}
		printf("Special: %d, normal: %d \n", c, d);
		duration_02 = (c * year_special) + (d * year_normal);
		
		if(( ey % 4 ==0 && ey % 100 !=0)|| (ey % 400 ==0)) //special year
		{
			for(int32_t i=0; i<(em-1); i++)
				{
					duration_02= duration_02 +  special_year[i];
				}
				duration_02= duration_02 -366;
		}
		else  
		{
			for(int32_t i=0; i<(em-1); i++)
				{
					duration_02= duration_02 +  normal_year[i];
				}
				duration_02= duration_02-365;
		};
		duration_02= duration_02 + ed ;
	}
	printf("Total days: %d \n",duration_02);
	int32_t durations;
	if(duration_01 > duration_02)
	{
		printf("Start date must be earlier than end date. \n");
		return 0;
	}
	else if(duration_01 - duration_02 ==0)
	{
	printf("Duration : 0 Day(s). It is same day. \n");
	}
	else
	{
		durations= duration_02 - duration_01;
		printf("Duration: %d Day(s). \n", durations);
	}
		return 0;
}
