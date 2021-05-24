// Nicole Kurtz
// Floating Pointer Parser for an arbitrary number of bit settings
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// protypes
int bias(int exp); // calculate and return bias
int exponent(int E, int exponent_value); // calculate and return exponent
int E(int exponent, int fraction, int hex); // calculate and return E
int sign(int exp, int frac, int hex); // calculate and return sign (1 or 0)
float signif(int E, float frac);  // return M (significand)
float fraction(int hex, int exponent_bit, int frac_bit, int sign); // return fraction
float float_result(int sign, int exponent, float signif); // calculate: C = (-1) ^ s * M * 2^E
void special(float frac, int sign); // check if float value is a special number
int check_special(int exp, int frac, int hex, int E); // if special number, print specific special number

int main(int argc, char * argv[])
{
	if(argc != 4)
	{
		error(EXIT_FAILURE, 0, "Error: please enter in 3 arguments: frac bit, exponent bit, hex.\n");
	}

	
	// get value of fraction and exponent bits
	int frac_bit[50];
	int exp_bit[50];
	unsigned int hex[50];
	int hex_len = strnlen(argv[3], 100);

	if(sscanf(argv[1], "%d", frac_bit) != 1)
	{
		error(EXIT_FAILURE, 0, "Input error\n");
	}
	sscanf(argv[2], "%d", exp_bit);
	sscanf(argv[3], "%x", hex);

	int sign_bit = sign(*exp_bit, *frac_bit, *hex);

	// erorr check that fraction bit is in range
	if(*frac_bit < 2 || *frac_bit > 10)
	{
		error(EXIT_FAILURE, 0, "Invalid number of fraction bit. Should be between 2 and 10.\n");
	}
	
	// error check that exponent bit is in range
	if(*exp_bit < 3 || *exp_bit > 5)
	{
		error(EXIT_FAILURE, 0, "Invalid number of exponent bit. Should be between 3 and 5.\n");
	}

	// check if hex is correct size
	if((hex_bit_counter(*hex)) > (*exp_bit + *frac_bit + 1))
	{
		error(EXIT_FAILURE, 0, "Hexadecimal does not match number of bits provided.\n");
	}

	// check if hex is legititmate hex value
	for(int i = 0; i < hex_len; ++i)
	{
		if(!isxdigit(argv[3][i]))
		{
			error(EXIT_FAILURE, 0, "Third argument is not a valid hexadecimal.\n");
		}
	}

	int calculated_E = E(*exp_bit, *frac_bit, *hex);
	int calculated_exponents = exponent(calculated_E, *exp_bit);
	float calculated_fraction = fraction(*hex, *exp_bit, *frac_bit, sign_bit);
	float calculated_significand = signif(calculated_E, calculated_fraction);
	float float_value = float_result(sign_bit, calculated_exponents, calculated_significand); 

	if(check_special(*exp_bit, *frac_bit, *hex, calculated_E))
		special(calculated_fraction, sign_bit);
	else
	{
		if(printf("%f\n", float_value) < 0)
			error(EXIT_FAILURE, 0, "Input error\n");

	}

	exit(EXIT_SUCCESS);
}

