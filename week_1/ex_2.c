/*
Write a program that defines two floating-point arrays of 12 elements each. The program then asks
user to enter tax percentage and yearly income limit up to which the percentage applies to and the
(greater) tax percentage that will be applied to income that is over the limit. Then program asks user
to enter salary of each month and stores the values in the array. After user has entered all monthly
salaries, the program calculates tax for each month.

The program prints all salaries with two decimal precision and the amount of tax for each month.
*/

#include <stdio.h>
#define ARRAY_SIZE 12

int main(void)
{

    float taxRate = 0;
    float taxRateOverTheIncomeLimit = 0;
    float incomeLimit = 0;

    printf("Enter tax rate: ");
    scanf("%f", &taxRate);
    taxRate = taxRate / 100; // example. 18.0 to 0.18

    printf("Enter income limit: ");
    scanf("%f", &incomeLimit);

    printf("Enter tax rate for income over the limit: ");
    scanf("%f", &taxRateOverTheIncomeLimit);
    taxRateOverTheIncomeLimit = taxRateOverTheIncomeLimit / 100;

    float income[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("Enter income for month %d: ", i + 1);
        scanf("%f", &income[i]);
    }

    float taxPerMonth[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        float taxForMonth = 0;

        if ((incomeLimit - income[i]) >= 0)
        {

            taxForMonth = income[i] * taxRate;
            incomeLimit -= income[i];
        }
        /*
            The month income > income limit, but the income limit != 0.
            So some of the income goes with the normal tax rate and the rest with higher tax rate.
        */
        else if (incomeLimit != 0)
        {
            float incomeOfTheMonth = income[i];
            incomeOfTheMonth -= incomeLimit;
            taxForMonth = (incomeOfTheMonth * taxRateOverTheIncomeLimit) + (incomeLimit * taxRate);
            incomeLimit = 0;
        }
        else
        { // Yearly income has gone over the income limit.

            taxForMonth = income[i] * taxRateOverTheIncomeLimit;
        }

        taxPerMonth[i] = taxForMonth;
    }

    printf("%5s\t%7s\t%7s\n", "month", "income", "tax");
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%5d\t%7.2f\t%7.2f\n", i + 1, income[i], taxPerMonth[i]);
    }

    return 0;
}