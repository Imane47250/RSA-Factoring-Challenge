#include <stdio.h>
#include <stdlib.h>

/**
 * factorize - Factorizes a number into two smaller numbers.
 * @num: The number to factorize.
 */
void factorize(unsigned long long num)
{
	unsigned long long p, q;

	for (p = 2; p * p <= num; p++)
	{
		if (num % p == 0)
		{
			q = num / p;
			printf("%llu=%llu*%llu\n", num, p, q);
			return;
		}
	}
	printf("%llu=%llu*%llu\n", num, num, 1ULL);
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
		fprintf(stderr, "USAGE: factors <file>\n");
		return (1);
	}

	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
		return (1);
	}

	while (fgets(line, sizeof(line), file))
	{
		num = strtoull(line, NULL, 10);
		factorize(num);
	}

	fclose(file)
		return (0);
}
