#include <stdio.h>
#include <stdint.h>

int main( void )
{
	uint32_t isPrime( uint32_t number );
	uint32_t gcd( uint32_t num1, uint32_t num2 );
	uint32_t calcE( uint32_t phi );
	uint32_t modInverse( uint32_t d, uint32_t e );
	uint64_t modExp( uint32_t A, uint32_t n, uint32_t m );
	uint64_t fastExp( uint32_t x, uint32_t n, uint32_t mod );

	uint32_t n, phi, e, d;
	uint32_t p, q;
	uint64_t plaintext, ciphertext, decrypted;

	p = 83;
	q = 97;

	n = p * q;

	printf( "For p = %d and q = %d, n = %u\n", p, q, n );

	phi = ( p - 1 ) * ( q - 1 );

	printf( "phi(n) = %u\n", phi);

	e = calcE( phi );

	printf( "e = %u\n", e );

	d = modInverse( e, phi );

	printf( "d = %u\n", d );

	plaintext = 202020;

	printf( "P = %lu\n", plaintext );

	printf( "Encrypting P...\n");

	ciphertext = modExp( plaintext, e, n );

	printf( "C = %lu\n", ciphertext );

	printf( "Decrypting C...\n");

	decrypted = modExp( ciphertext, d, n );

	printf( "Found P = %lu\n", decrypted );
}

uint32_t isPrime( uint32_t number )
{
	uint32_t divisor = number - 1;

	while( divisor > 1 )
	{
		if( number % divisor == 0)
		{
			return 0;
		}
		divisor -= 1;
	}
	return number != 1;
}

uint32_t gcd( uint32_t num1, uint32_t num2 )
{
	uint32_t index = 1, gcd = 0;

	while( ( index <= num1 ) && ( index <= num2 ) )
	{
		if( ( num1 % index == 0 ) && ( num2 % index == 0 ) )
		{
			gcd = index;
		}
		index++;
	}
	return gcd;
}

uint32_t calcE( uint32_t phi )
{
	uint32_t index = 3, e = 1, temp;

	while( index < phi )
	{
		temp = gcd( phi, index );

		if( gcd( phi, index ) == 1 )
		{
			e = index;

			return e;
		}
		index++;
	}
	return e;
}

uint32_t modInverse( uint32_t e, uint32_t phi )
{
	uint32_t index;

	for( index = 1; index < phi ; index++ )
	{
		if( ( e * index ) %  phi == 1 )
		{
			return index;
		}
	}
	return 0;
}

uint64_t modExp( uint32_t base, uint32_t exp, uint32_t mod )
{
	uint64_t result = 1;
	if( mod == 1 )
	{
		return 0;
	}
	base = base % mod;
	while( exp > 0 )
	{
		if( exp % 2 == 1 )
		{
			result = ( result * base ) % mod;
		}
		exp = exp >> 1;
		base = ( base * base ) % mod;
	}
	return result;
}

