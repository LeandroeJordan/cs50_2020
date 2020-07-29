#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

int collatz(int n);


int main(void)
{
    int n = 0;
    do
    {
       n = get_int("Number: ");
    }
    while (n <= 0);
    printf("Times = %i\n", collatz(n));
    

}

int collatz(int n)
{
    if (n == 1 )
    {
        return 0;
    }

    if ((n % 2) == 0)

    {
        return 1 + collatz(n / 2);
    }
    else
    {
        return 1 + collatz((n * 3) + 1);
    }

}