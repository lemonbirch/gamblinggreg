#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

typedef struct
{
    char dogNames[9][20]; // Fixed the array size for dog names
    double payout;
    double odds;
} Dog;

void initializeDogs(Dog dogs[]);
void displayMenu();                           // Renamed printMenu() to displayMenu()
void takeBet(Dog dogs[], double bankBalance); // Removed pointer reference for bankBalance
void clearInputBuffer();                      // Added function prototype
void printRaceResults(Dog dogs[]);

int main()
{
    srand(time(NULL));
    Dog dogs[9];
    double bankBalance = 1000.0;
    char choice;

    initializeDogs(dogs);

    do
    {
        displayMenu();
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice)
        {
        case 'G':
        case 'g':
            takeBet(dogs, bankBalance); // Removed pointer reference for bankBalance
            break;
        case 'B':
        case 'b':
            printf("Enter the amount to [D]eposit or [W]ithdraw: ");
            double amount;
            scanf("%lf", &amount);
            bankBalance += (choice == 'D' || choice == 'd') ? amount : -amount;
            break;
        case 'R':
        case 'r':
            printRaceResults(dogs);
            break;
        case 'L':
        case 'l':
            printf("Thank you for playing! Goodbye.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 'L' && choice != 'l');

    return 0;
}

void initializeDogs(Dog dogs[])
{
    char dogNames[9][20] = {"Dog 1", "2 to 1", "5 to 1", "10 to 1", "15 to 1",
                            "50 to 1", "20 to 1", "10 to 1", "5 to 1"};
    double payouts[9] = {2.0, 5.0, 10.0, 15.0, 50.0, 20.0, 10.0, 5.0, 3.0};
    double odds[9] = {0.4, 0.1, 0.08, 0.06, 0.01, 0.04, 0.08, 0.1, .13};

    for (int i = 0; i < 9; i++)
    {
        strcpy(dogs[i].dogNames, dogNames[i]);
        dogs[i].payout = payouts[i];
        dogs[i].odds = odds[i];
    }
}

void displayMenu()
{
    printf("\nMenu:\n");
    printf("[G]amble\n");
    printf("[B]anking\n");
    printf("[R]esults of each race that Greg wagered\n");
    printf("[L]eave the dog track\n");
}

void takeBet(Dog dogs[], double bankBalance)
{
    double wager;

    // Loop until valid wager entered
    while (1)
    {
        printf("Enter wager amount: ");
        if (scanf("%lf", &wager) != 1)
        {
            // Handle non-number input
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        if (wager <= 0)
        {
            printf("Wager must be greater than 0.\n");
            continue;
        }
        break;
    }

    int dogChoice;

    // Loop until valid dog choice
    while (1)
    {
        printf("Pick a dog (1-9): ");
        if (scanf("%d", &dogChoice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        if (dogChoice < 1 || dogChoice > 9)
        {
            printf("Invalid dog choice. Try again.\n");
            continue;
        }

        break;
    }

    dogChoice--; // Moved inside the takeBet() function

    double randNum = (double)rand() / RAND_MAX;
    if (randNum < dogs[dogChoice].odds)
    {
        printf("Congratulations! You won %.2lf!\n", wager * dogs[dogChoice].payout);
        bankBalance += wager * dogs[dogChoice].payout; // Removed pointer reference for bankBalance
    }
    else
    {
        printf("Sorry, you lost %.2lf.\n", wager);
        bankBalance -= wager; // Removed pointer reference for bankBalance
    }
}

void clearInputBuffer()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void printRaceResults(Dog dogs[])
{
    printf("\nRace Results:\n");
    for (int i = 0; i < 9; i++)
    {
        printf("Dog %d: %s\tPayout: %.2lf\tOdds: %.2lf%%\n",
               i + 1, dogs[i].dogNames, dogs[i].payout, dogs[i].odds * 100);
    }
}
