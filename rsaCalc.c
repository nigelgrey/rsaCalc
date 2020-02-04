#include <stdio.h>
#include <stdint.h>
#include <math.h>

int main( void )
{
	uint32_t isPrime( uint32_t number );
	uint32_t gcd( uint32_t num1, uint32_t num2 );
	uint32_t calcE( uint32_t phi );
	uint32_t modInverse( uint32_t d, uint32_t e );
	uint64_t modExp( uint32_t A, uint32_t n, uint32_t m );

	uint64_t n, phi, e, d, plaintext, ciphertext = 0;
	uint32_t p, q;

	printf( "Enter a prime integer p: ");
	scanf( "%d", &p);

	while( isPrime( p ) == 0 )
	{
		printf( "%d is not prime.\n", p );
		printf( "Enter a prime integer p: ");
		scanf( "%d", &p);
	}

	printf( "Enter another prime integer q: ");
	scanf( "%d", &q);

	while( isPrime( q ) == 0 )
	{
		printf( "%d is not prime.\n", q );
		printf( "Enter a prime integer q: ");
		scanf( "%d", &q);
	}

	n = p * q;

	printf( "For p = %d and q = %d, n = %lu\n", p, q, n );

	phi = ( p - 1 ) * ( q - 1 );

	printf( "phi(n) = %lu\n", phi);

	e = calcE( phi );

	printf( "e = %lu\n", e );

	d = modInverse( e, phi );

	printf( "d = %lu\n", d );

    plaintext = 400;

	printf( "P = %lu\n", plaintext );

	printf( "Encrypting P...\n");

    ciphertext = modExp( plaintext, e, n );

	printf( "C = %lu\n", ciphertext );

	printf( "Decrypting C...\n");

	plaintext = modExp( ciphertext, d, n );

	printf( "Found P = %lu\n", plaintext );
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

uint64_t modExp( uint32_t A, uint32_t n, uint32_t m )
{
	uint64_t result = 1;
	unsigned long long a = A;

	a = a % m;

	while( n > 0 )
	{
		if( n & 1 )
		{
			result = ( ( result % m ) * ( a % m) ) % m;
		}
		n = n >> 1;
    // TODO fix so this can work with large ints
		a = ( ( a % m ) * ( a % m ) ) % m;
	}

	return result;
}
