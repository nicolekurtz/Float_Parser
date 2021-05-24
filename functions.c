// Nicole Kurtz
// Functions for float parser program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// return sign bit
int sign(int exp, int frac, int hex)
{
	int sign_bit = hex >> (exp + frac);

	if(sign_bit % 2 != 0)
	{
		return 1;
	}
	return 0;
}

// calculate the bias
int bias(int exp)
{
	return pow(2, (exp-1)) - 1;
}

// calculate E 
int E(int exponent, int fraction, int hex)
{
	int E = 0;
	int bit = 1;
	int one = 1;
	int result;

	// remove fraction bits from hex to isolate exponent
	result = hex >> fraction;

	for(int i=0; i < exponent; ++i)
	{
		if(result % 2 != 0)
		{
			E += bit;
		}

		bit = bit << one;

		result = result >> one;
	}

	return E;
}

// calculate exponent field
int exponent(int E, int exponent)
{
	if(E == 0)
		return 0;
	return E - bias(exponent);
}

// count number of bits in hex value
int hex_bit_counter(int hex)
{
	int result = hex;
	int one = 1;
	int counter = 0;

	while(result != 0)
	{
		++counter;
		result = result >> one;
	}

	return counter;
}

// calculate M, significand - fractional number
float signif(int E, float frac)
{
	if(E == 0)
		return frac;

	else
		return 1 + frac;
}

// calculate fraction value
float fraction(int hex, int exponent_bit, int frac_bit, int sign)
{
	int check;
	int shift = 1;
	float sig = 0.00000;
	float fraction = 0.5;

	for (int i=0; i < frac_bit; ++i)
	{
		check = hex >> (frac_bit - shift);
		if(check % 2 != 0)
			sig += fraction;
		++shift;
		fraction /= 2.000000;
	}

	return sig;
}


// calculate: C = (-1) ^ s * M * 2^E
float float_result(int sign, int exponent, float signif)
{
	float result = pow((-1), sign) * signif * pow(2, exponent);
	return result;
}

// check for special values
int check_special(int exp, int frac, int hex, int E)
{
	int result = E;
	int counter = 0;
	int one = 1;

	for (int i = 0; i < exp; ++i)
	{ 
		if(result % 2 != 0)
		{
			++counter;
		}
		result = result >> one;
	}
	if(counter == exp)
		return 1;
	return 0;
}

// determine which special case the number is and print 
void special(float frac, int sign)
{
	if(frac != 0)
	{
		if(printf("NaN\n") < 0)
			error(EXIT_FAILURE, 0, "Print error\n");
	}
	else if(sign)
	{
		if(printf("-inf \n") < 0)
			error(EXIT_FAILURE, 0, "Print error\n");
	}
	else
	{
		if(printf("+inf\n") < 0)
			error(EXIT_FAILURE, 0, "Print error\n");
	}
}
