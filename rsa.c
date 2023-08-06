#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

/**
 * miller_rabin - Perform Miller-Rabin primality test.
 * @n: The number to test.
 * @k: The number of iterations for the test.
 * Return: true if n is likely prime, false otherwise.
 */
bool miller_rabin(unsigned long long n, int k)
{
	if (n <= 1)
		return (false);
	if (n <= 3)
		return (true);
	if (n % 2 == 0)
		return (false);

	unsigned long long d = n - 1;
	int r = 0;

	while (d % 2 == 0)
	{
		d /= 2;
		r++;
	}
	for (int i = 0; i < k; i++)
	{
		unsigned long long a = rand() % (n - 4) + 2;
		unsigned long long x = 1;
		unsigned long long power = d;

		while (power > 0)
		{
			if (power % 2 == 1)
				x = (x * a) % n;
			a = (a * a) % n;
			power /= 2;
		}
		if (x == 1 || x == n - 1)
			continue;
		for (int j = 0; j < r - 1; j++)
		{
			x = (x * x) % n;
			if (x == n - 1)
				break;
		}
		if (x != n - 1)
			return (false);
	}
	return (true);
}
/**
 * gcd - Calculate the greatest common divisor of two numbers.
 * @a: First number.
 * @b: Second number.
 * Return: The greatest common divisor of a and b.
 */
unsigned long long gcd(unsigned long long a, unsigned long long b)
{
	if (b == 0)
		return (a);
	return (gcd(b, a % b));
}

/**
 * pollards_rho - Use Pollard's rho algorithm to find a factor of n.
 * @n: The number to factorize.
 * Return: A factor of n, or 0 if no factor is found.
 */
unsigned long long pollards_rho(unsigned long long n)
{
	if (n % 2 == 0)
		return (2);

	unsigned long long x = rand() % (n - 2) + 2;
	unsigned long long y = x;
	unsigned long long c = rand() % (n - 1) + 1;
	unsigned long long d = 1;

	while (d == 1)
	{
		x = (x * x + c) % n;
		y = (y * y + c) % n;
		y = (y * y + c) % n;
		d = gcd(abs(x - y), n);
	}

	if (d == n)
		return (0);

	return (d);
}

/**
 * factorize_rsa - Find the prime factors of an RSA number.
 * @n: The RSA number to factorize.
 */
void factorize_rsa(unsigned long long n)
{
	unsigned long long p, q;

	if (n < 2)
	{
		printf("%llu=%llu*%llu\n", n, n, 1ULL);
		return;
	}

	if (miller_rabin(n, 10))
	{
		printf("%llu=%llu*%llu\n", n, n, 1ULL);
		return;
	}

	p = pollards_rho(n);
	q = n / p;

	printf("%llu=%llu*%llu\n", n, p, q);
}

/**
 * main - Entry point.
 * @argc: Argument count.
 * @argv: Array of pointers to command-line arguments.
 * Return: 0 on success, 1 on failure.
 */
int main(int argc, char *argv[])
{
	FILE *file;
	char line[100];
	unsigned long long num;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: rsa <file>\n");
		return (1);
	}

	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
		return (1);
	}

	srand(time(NULL));

	while (fgets(line, sizeof(line), file))
	{
		num = strtoull(line, NULL, 10);
		factorize_rsa(num);
	}

	fclose(file);
	return (0);
}

