sort1 uses: bubble sort

How do you know?:  because this was the slowest for all random data sets and quickest for the small and medium sorted data sets.

sort2 uses: merge sort

How do you know?: as _n_ increases the run times increased, but it was much more efficient than the other algorithms as they likely did a lot more comparisons

sort3 uses: selection sort

How do you know?: sort3 was slower than sort2 on random and reversed, but nearly twice as slow as sort1(bubble sort) on sorted





|                   | sort1                                                    | sort2                                                    | sort3                                                    |
| ----------------- | -------------------------------------------------------- | -------------------------------------------------------- | -------------------------------------------------------- |
| random5000.txt    | real    0m0.079s<br>user    0m0.037s<br>sys     0m0.025s | real    0m0.035s<br>user    0m0.008s<br>sys     0m0.021s | real    0m0.045s<br>user    0m0.016s<br>sys     0m0.029s |
| random10000.txt   | real    0m0.196s<br>user    0m0.134s<br>sys     0m0.052s | real    0m0.106s<br>user    0m0.004s<br>sys     0m0.055s | real    0m0.128s<br>user    0m0.067s<br>sys     0m0.055s |
| random50000.txt   | real    0m5.720s<br>user    0m5.074s<br>sys     0m0.271s | real    0m0.498s<br>user    0m0.017s<br>sys     0m0.265s | real    0m2.181s<br>user    0m1.713s<br>sys     0m0.228s |
| reversed5000.txt  | real    0m0.070s<br>user    0m0.045s<br>sys     0m0.024s | real    0m0.038s<br>user    0m0.000s<br>sys     0m0.029s | real    0m0.050s<br>user    0m0.016s<br>sys     0m0.031s |
| reversed10000.txt | real    0m0.232s<br>user    0m0.167s<br>sys     0m0.054s | real    0m0.067s<br>user    0m0.010s<br>sys     0m0.046s | real    0m0.159s<br>user    0m0.075s<br>sys     0m0.055s |
| reversed50000.txt | real    0m4.798s<br>user    0m4.260s<br>sys     0m0.292s | real    0m0.584s<br>user    0m0.032s<br>sys     0m0.262s | real    0m2.470s<br>user    0m2.053s<br>sys     0m0.250s |
| sorted5000.txt    | real    0m0.033s<br>user    0m0.000s<br>sys     0m0.027s | real    0m0.036s<br>user    0m0.000s<br>sys     0m0.028s | real    0m0.054s<br>user    0m0.015s<br>sys     0m0.029s |
| sorted10000.txt   | real    0m0.064s<br>user    0m0.000s<br>sys     0m0.054s | real    0m0.132s<br>user    0m0.000s<br>sys     0m0.064s | real    0m0.117s<br>user    0m0.073s<br>sys     0m0.044s |
| sorted50000.txt   | real    0m0.478s<br>user    0m0.014s<br>sys     0m0.261s | real    0m0.454s<br>user    0m0.022s<br>sys     0m0.243s | real    0m2.333s<br>user    0m1.761s<br>sys     0m0.308s |
