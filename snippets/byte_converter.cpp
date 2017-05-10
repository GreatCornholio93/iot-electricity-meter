#include <stdio.h>
#include <stdlib.h>

/*
*	convert 3 unsigned integers to 12B unsigned char array
*	convert 3 integers to format {a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4} 
*	where x1 is low significant byte and x4 is high significant byte
*/
int parse_int_to_12bytes(unsigned char *bytes, unsigned int a, unsigned int b, unsigned int c)
{
	bytes[0] = (char) (a);
	bytes[1] = (char) (a >> 8);
	bytes[2] = (char) (a >> 16);
	bytes[3] = (char) (a >> 24);
	bytes[4] = (char) (b);
	bytes[5] = (char) (b >> 8);
	bytes[6] = (char) (b >> 16);
	bytes[7] = (char) (b >> 24);
	bytes[8] = (char) (c);
	bytes[9] = (char) (c >> 8);
	bytes[10] = (char) (c >> 16);
	bytes[11] = (char) (c >> 24);
	// TODO same logic with b and c
}

int main(void)
{
	unsigned char bytes[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	// tests
	unsigned int n1 = 0xcafedead;
	parse_int_to_12bytes(bytes, n1, n1, n1);
	printf("%0X\n", n1);
	printf("%0X %0X %0X %0X : %0X %0X %0X %0X : %0X %0X %0X %0X\n", bytes[11], bytes[10], bytes[9], bytes[8], bytes[7], bytes[6], bytes[5], bytes[4], bytes[3], bytes[2], bytes[1], bytes[0]);

	unsigned int n2 = 666;
	parse_int_to_12bytes(bytes, n2, n2, n2);
	printf("%0X\n", n2);
	printf("%0X %0X %0X %0X : %0X %0X %0X %0X : %0X %0X %0X %0X\n", bytes[11], bytes[10], bytes[9], bytes[8], bytes[7], bytes[6], bytes[5], bytes[4], bytes[3], bytes[2], bytes[1], bytes[0]);

	unsigned int n3 = 4000000000;
	parse_int_to_12bytes(bytes, 520, 30, 40);
	printf("%0X\n", n3);
	printf("%0X %0X %0X %0X : %0X %0X %0X %0X : %0X %0X %0X %0X\n", bytes[11], bytes[10], bytes[9], bytes[8], bytes[7], bytes[6], bytes[5], bytes[4], bytes[3], bytes[2], bytes[1], bytes[0]);

	return 0;
}


