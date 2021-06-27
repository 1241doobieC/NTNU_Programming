#include <stdio.h>
#include <stdint.h>

int main()
{
	int64_t salary;
	int32_t married;
	int32_t num_fam;
	int32_t num_income;
	int32_t dedu;
	int32_t dedu_t;
	int32_t pre_children;
	int32_t disable;
	
	float total;
	
	printf("Gross Salary: ");
	int32_t rec = scanf("%ld" , &salary);
	
//---English Character---
	if(rec != 1)
	{
		printf("Input Error. \n");
		return 0;
	}
//-----------------------
	else if(salary < 0)
	{
	printf("Wrong Input. \n");
	return 0;
	}
	printf("Married(0 if not married. /1 if married.) : ");
	
//---English Character---
	int32_t rec02 = scanf("%d" , &married);
	if(rec02 !=1)
	{
		printf("Input Error. \n");
		return 0;
	}
//-----------------------
	
	if(married != 0 && married !=1)
	{
		printf("Wrong Input. There are only two situations! \n");
		return 0;
	}
	
	if(married == 0)
		{
			salary= salary - 120000;
		}
	else
		{
			salary= salary - 240000;
		}
	
	printf("How many people are there in your family? : ");
	int32_t rec03 = scanf("%d" , &num_fam);
	
//---English Character---
	if(rec03 !=1)
		{
			printf("Input Error. \n");
			return 0;
		}
//-----------------------

	salary = salary - (num_fam * 88000);
	
	printf("How many people in your family have income? :");
	int32_t rec04 = scanf("%d" , &num_income);
	
//---English Character---
	if(rec04 !=1)
		{
			printf("Input Error. \n");
			return 0;
		}
//-----------------------

	if(num_income>=0){
	salary = salary - (num_income * 200000);
	}
	else
	{
	printf("Wrong Input. \n");
	return 0;
	}
	printf("Special Deduction for Savings and investment: ");
	scanf("%d" , &dedu);
	if(dedu>=0 && dedu <= 270000){
		salary = salary - dedu;
	}
	else if(dedu > 270000)
	{
		salary = salary - 270000;
	}
	else
	{
		printf("wrong input. \n");
		return 0;
	}		
	
	printf("Special Deduction for Tuition: ");
	int32_t rec05 = scanf("%d" , &dedu_t);
//---English Character---
	if(rec05 !=1)
		{
			printf("Input Error. \n");
			return 0;
		}
//-----------------------

	salary = salary - (dedu_t * 25000);
	
	printf("How many preschool children: ");
	int32_t rec06 = scanf("%d", &pre_children);
//---English Character---
	if(rec06 !=1)
		{
			printf("Input Error. \n");
			return 0;
		}
//-----------------------

	salary= salary - (pre_children * 120000);
	
	printf("How many people are disable: ");
	int32_t rec07 = scanf("%d", &disable);
//---English Character---
	if(rec07 !=1)
		{
			printf("Input Error. \n");
			return 0;
		}
//-----------------------

	salary = salary -(disable * 200000);
	
	if(salary < 0)
	{
		printf("Wrong input");
		return 0;
	}
	else if(salary < 540000)
	{
	total = salary * 0.05;
	}
	else if(salary <1210000)
	{
	total = (540000 * 0.05) + (salary -540000) * 0.12;
	}
	else if(salary < 2420000)
	{
	total = (540000 * 0.05) + (1210000 -540000) * 0.12 + (salary - 1210000) * 0.2;
	}
	else if(salary < 4530000)
	{
	total = (540000 * 0.05) + (1210000 -540000) * 0.12 + (2420000 - 1210000) * 0.2 + (salary - 2420000) * 0.3;
	}
	else
	{
	total = (540000 * 0.05) + (1210000 -540000) * 0.12 + (2420000 - 1210000) * 0.2 + (4530000 - 2420000) * 0.3 + (salary - 4530000) * 0.4;
	}
	
	printf("Total tax is %.0f. \n", total);
	return 0;
}
