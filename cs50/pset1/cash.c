#include <cs50.h>
#include <stdio.h>

int main(void)
{
	int n;
	int i = 0;
    int quarter = 0;
    int dime = 0;
    int nickle = 0;
    int penny = 0;
	do
	{
		n = get_int("Change owed: ");
	}
	while (n < 1);
	
	if (n >= 25)
	{
		while (n >= 25)
		{
            quarter += 1;
			n = n - 25;
			i = i + 1;
			//printf(" > +1 quarter | (%i)\n", n);
		}
	}

	if (n >= 10)
	{
        while (n >= 10)
		{
			dime += 1;
            n = n - 10;
			i = i + 1;
			//printf("  > +1 dime | (%i)\n", n);
		}
	}

	if (n >= 5)
	{
		while (n >= 5)
		{
            nickle += 1;
			n = n - 5;
			i = i + 1;
			//printf("   > +1 nickle | (%i)\n", n);
		}
	}

	if (n >= 1)
	{
        while (n >= 1)
		{
			penny += 1;
            n = n - 1;
			i = i + 1;
			//printf("    > +1 penny | (%i)\n", n);
		}
	}
    printf("quarter: %i | dime: %i | nickle: %i | penny: %i\n", quarter, dime, nickle, penny);
    printf("total amount of coins to return: %i\n", i);
}
