#include <cs50.h>
#include <stdio.h>

int main(void)
{
	int height = 0;
	do
	{
		height = get_int("height: ");
	}
	while (height < 1);
	
	for (int i = 1; i <= height; i++)
	{
        int space = height - i;
        while (space > 0)
        {
            printf(" ");
            space--;
        }
        int brick = i;
        while (brick > 0)
        {
            printf("#");
            brick--;
        }
        printf("\n");
	}
}