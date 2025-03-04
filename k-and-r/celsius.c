#include <stdio.h>

int main()
{
	float lower = 0;
	float upper = 300;
	float step = 20;

	printf(" °C     °F\n");
	printf("---  -----\n");

	float celsius = lower;
	float fahrenheit;
	while (celsius <= upper) {
		fahrenheit = (9.0/5.0 * celsius) + 32.0;
		printf("%3.0f %6.1f\n", celsius, fahrenheit);
		celsius += step;
	}
}
