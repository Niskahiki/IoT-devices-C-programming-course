/*
Write a program that:
1. Asks user to enter the price of a bus ticket
2. Asks user to enter the price of a taxi trip
3. Asks user to enter how much money he/she has
4. If user has not enough money for either type tells user to walk and then the program stops
5. Asks user to choose taxi or bus (use numbers for selection)
6. Checks if user has enough money for the selected trip type
    o If User has enough money reduce the money by the selected trip’s price and print
      how much money is left, and go back to step 4
    o If user has not enough money for the selected trip type then tell that to user and go
      back to step 4
*/

#include <stdio.h>

int main(void)
{

    float priceOfBusTicket = 0;
    float priceOfTaxi = 0;
    float userMoney = 0;

    printf("Please enter the price of a bus ticket: ");
    scanf("%f", &priceOfBusTicket);

    printf("Please enter the price of a bus ticket: ");
    scanf("%f", &priceOfTaxi);

    printf("How much money do you have?: ");
    scanf("%f", &userMoney);

    while (userMoney > priceOfBusTicket || userMoney > priceOfTaxi)
    {
        int userChoice = 0;
        printf("Do you want to take:\n 1) Bus (%.2f)\n 2) Taxi (%.2f)\n", priceOfBusTicket, priceOfTaxi);
        printf("Enter your selection: ");
        scanf("%d", &userChoice);

        if (userChoice == 1)
        {
            printf("You chose bus.\n");

            if (userMoney < priceOfBusTicket)
            {
                printf("You don't have enough money for bus.\n");
            }
            else
            {
                userMoney -= priceOfBusTicket;
            }
        }
        else if (userChoice == 2)
        {
            printf("You chose taxi.\n");

            if (userMoney < priceOfTaxi)
            {
                printf("You don't have enough money for taxi.\n");
            }
            else
            {
                userMoney -= priceOfTaxi;
            }
        }

        printf("You have %.2f euros left.\n", userMoney);
    }

    printf("You need to walk. Bye");

    return 0;
}