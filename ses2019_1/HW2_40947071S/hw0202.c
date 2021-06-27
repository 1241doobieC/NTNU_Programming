#include <stdio.h>
#include <stdint.h>

int main()
{
	/*
	Given two lines, please write a program to find the intersection.
	y = ax +b;
	*/
	
	//L1
	int32_t l1x1;
	int32_t l1y1;
	int32_t l1x2;
	int32_t l1y2;
	
	//L2
	int32_t l2x1;
	int32_t l2y1;
	int32_t l2x2;
	int32_t l2y2;
	
	float m1;
	float m2;
	float b1;
	float b2;
	float a1;
	float a2;
	
	float ix;
	float iy;
	
	
	
	printf("Please enter the first line: ");
	scanf("(%d,%d),(%d,%d)", &l1x1, &l1y1, &l1x2, &l1y2);
	
	setbuf(stdin, NULL);
	
	printf("Please enter the second line: ");
	scanf("(%d,%d),(%d,%d)", &l2x1, &l2y1, &l2x2, &l2y2);
	
	m1= (l1y2-l1y1) /  (float) (l1x2 - l1x1);
	m2= (l2y2-l2y1) /  (float) (l2x2 - l2x1);
	
	//Ausfall ==> gleiche Linie
	if(m1 == m2)
	{
	printf("Same line. Intersection doesn't exist. \n");
	return 0;
	}
	
	//y=ax+b
	a1 = (l1y1 - l1y2) / (float) (l1x1 - l1x2);
	b1 = l1y1 - (l1x1 * a1);
	a2 = (l2y1 - l2y2) / (float) (l2x1 - l2x2);
	b2 = l2y1 - (l2x1 * a2);
	
	ix = (b2 - b1) / (a1 - a2);
	iy = (ix * a1) + b1;
	
	printf("The intersection is (%.2f , %.2f). \n" , ix,iy);
	
	
	
	
	return 0;
	
	
}
