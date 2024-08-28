#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int calc_value(string p);
const int points [] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int total;

int main(void)
{
    string p1 = get_string("Player 1: ");
    string p2 = get_string("Player 2: ");

    int p1_total = calc_value(p1);
    int p2_total = calc_value(p2);

    if (p1_total > p2_total)
    {
        printf("Player1 wins! - [%s] %i > [%s] %i\n", p1, p1_total, p2, p2_total);
    }
    else if (p1_total < p2_total)
    {
        printf("Player2 wins! - [%s] %i > [%s] %i\n", p2, p2_total, p1, p1_total);
    }
    else if (p1_total == p2_total)
    {
        printf("Tie! - [%s] %i = [%s] %i\n", p1, p1_total, p2, p2_total);
    }
    else
    {
        printf("error\n");
    }
}

int calc_value(string player)
{
    int total = 0;
    for (int i = 0; i < strlen(player); i++)
    {
        int p_int = (toupper(player[i]));
        //printf("p_int: %i  |  ", p_int);
        int zeroed_int = (p_int - 65);
        //printf("zeroed_int: %i  |  ", zeroed_int);
        int value = points[zeroed_int];
        //printf("value: + %i  |  ", value);
        total = total + value;
        //printf("running total: (%i)\n", total);
    }
    return total;
}
