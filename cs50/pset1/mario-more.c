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
        int brick_l = i;
        while (brick_l > 0)
        {
            printf("#");
            brick_l--;
        }
        printf("  ");
        int brick_r = i;
        while (brick_r > 0)
        {
            printf("#");
            brick_r--;
        }
        printf("\n");
	}
}