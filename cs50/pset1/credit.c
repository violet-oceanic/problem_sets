#include <cs50.h>
#include <stdio.h>


int main(void)
{
	long cc_number;
    int odd_sum = 0;
    long long even = 0;
    int even_sum = 0;
    long long mod = 10;
    long long place = 1;
    int previous = 0;
    int first;
    int second;
    int first2;


    // prompt user for card number
	do
	{
		cc_number = get_long("Credit Card Number: ");
        // cc_number = 378282246310005;
	}
	while (cc_number < 0);

    // count the number of digits in CC
    int cc_digits_count = 0;
    long cc_digits = cc_number;
    while (cc_digits > 0)
    {
        cc_digits = cc_digits / 10;
        cc_digits_count += 1;
    }

    // loop through the digits
    for (int i = 1; i <= cc_digits_count; i++)
    {
        long long x = ((cc_number % mod) / place);
        // get first 2 digits in CC
        if (i == cc_digits_count)
        {
            first = x;
        }
        if (i == (cc_digits_count - 1))
        {
            second = x;
        }
        first2 = ((first * 10) + second);

        // if even number
        if ((i % 2) == 0)
        {
            even = x * 2;
            if (even > 9)
            {
                int ten;
                int hundred;
                ten = (even % 10);
                hundred = (even % 100) / 10;
                even_sum = even_sum + ten + hundred;
                //printf("EVEN   | %lli |   (%i  + %i) = %i\n", x, hundred, ten, even_sum);
            }
            if (even <= 9)
            {
                even_sum = even_sum + even;
                //printf("EVEN   | %lli |   %lli * 2 = %i\n", x, x, even_sum);
            }
        }
        // if odd number
        else
        {
            odd_sum = x + odd_sum;
            //printf(" > ODD | %lli | %i + %lli = %i\n", x, previous, x, odd_sum);
            previous = odd_sum;
        }
        mod = mod * 10;
        place = place * 10;
    }

    // determine card type
    string card_type;
    int invalid = 0;
    if (cc_digits_count == 15 && (first2 == 34 || first2 ==  37))
    {
        card_type = "AmericanExpress";
    }
    else if (cc_digits_count == 16 && (first2 == 51 || first2 == 52 || first2 == 53 || first2 == 54 || first2 ==  55))
    {
        card_type = "MasterCard";
    }
    else if ((cc_digits_count == 13 || cc_digits_count == 16) && first == 4)
    {
        card_type = "Visa";
    }
    else
    {
        card_type = "invalid";
        invalid = 1;

    }

    // output results
    if (invalid == 1)
    {
        printf("INVALID CARD");
    }
    else
    {
        int total = odd_sum + even_sum;
        string validity;
        if ((total % 10) == 0)
        {
            validity = "valid";
        }
        else
        {
            validity = "invalid";
        }
        printf("   ### Card Type: %s || first 2: %i || total digits:%i\n", card_type, first2, cc_digits_count);
        printf("     > odd_sum: %i + even_sum: %i = %i || validity: %s\n", odd_sum, even_sum, total, validity);
    }
}