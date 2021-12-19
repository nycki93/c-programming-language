#include <stdio.h> 

/* Limits of temperature table, in farenheit. */
#define TABLE_BEGIN 0
#define TABLE_END 300
#define TABLE_STEP 20

/* print Fahrenheit-Celsius table */
int main()
{
	printf(" °F     °C\n");
	printf("---  -----\n");

	for (
		int fahrenheit = TABLE_BEGIN; 
		fahrenheit <= TABLE_END; 
		fahrenheit += TABLE_STEP) 
	{
		printf("%3d %6.1f\n",
			fahrenheit,
			(5.0/9.0) * (fahrenheit - 32)
		);
	}
}
