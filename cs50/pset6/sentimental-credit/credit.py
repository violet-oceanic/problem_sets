from cs50 import get_string
import re

while True:
    try:
        #cc_number = "378282246310005"
        cc_number = get_string("Credit Card Number: ")
        if int(cc_number) > 0:
            break
    except:
        print("Must be positive integer")
        pass

cc_digits_count = len(cc_number)

if cc_digits_count == 15 and (re.match(r"^(34|37)", cc_number)):
    card_type = "AmericanExpress"
elif cc_digits_count == 16 and (re.match(r"^(51|52|53|54|55)", cc_number)):
    card_type = "MasterCard"
elif cc_digits_count in [13,16] and (re.match(r"^4", cc_number)):
    card_type = "Visa"
else:
    card_type = "invalid"

this_sum = 0
that_sum = 0

digits_count = cc_digits_count - 1

for i in range(0,(digits_count) + 1):
    reversed_index = (digits_count) - i
    if i % 2 != 0:
        this = int(cc_number[reversed_index]) * 2
        if this > 9:
            this_sum = this_sum + (1 + (this - 10))
        else:
            this_sum = this_sum + this
    else:
        that = int(cc_number[reversed_index])
        that_sum = that_sum + that

if card_type == "invalid":
    print(f"{cc_number} is an invalid card type")
else:
    total = this_sum + that_sum
    print(f"this_sum[{this_sum}] + that_sum[{that_sum}] = total[{total}]")
    if total % 10 == 0:
        print(f"  ** Card {cc_number} is a valid {card_type} card **")
    else:
        print(f"  ** Card {cc_number} is invalid **")
