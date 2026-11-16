#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PLAYER 4
#define BOARD_SIZE 20
#define INITIAL_ENERGY 100

#define START 0
#define CITY 1
#define EVENT 2
#define ISLAND 3

typedef struct {
    char name[30];
    int energy;
    int position;
} Player;

char typeName[4][20] = {
    "START",
    "CITY",
    "EVENT",
    "ISLAND"
};

char gradeName[5][5] = {
    "A+",
    "A0",
    "A-",
    "B+",
    "B0"
};

char *getName(int type)
{
    if (type < 0 || type >= 4)
        return "UNKNOWN";

    return typeName[type];
}

char *getGradeName(int grade)
{
    if (grade < 0 || grade >= 5)
        return "UNKNOWN";

    return gradeName[grade];
}

void createPlayer(Player *p)
{
    printf("Player name: ");
    scanf("%29s", p->name);

    p->energy = INITIAL_ENERGY;
    p->position = 0;
}

void printPlayer(Player *p)
{
    printf("Name: %s\n", p->name);
    printf("Energy: %d\n", p->energy);
    printf("Position: %d\n", p->position);
}

void movePlayer(Player *p, int steps)
{
    p->position = (p->position + steps) % BOARD_SIZE;

    printf("%s moved %d steps!\n", p->name, steps);
}

int main(void)
{
    Player players[MAX_PLAYER];
    int playerCount;
    int i;
    int dice;
    int round = 1;

    srand((unsigned int)time(NULL));

    printf("=== Node Types ===\n");

    for (i = 0; i < 4; i++)
        printf("Type %d : %s\n", i, getName(i));

    printf("\n=== Grade Types ===\n");

    for (i = 0; i < 5; i++)
        printf("Grade %d : %s\n", i, getGradeName(i));

    while (1)
    {
        printf("\nNumber of players (2~4): ");

        if (scanf("%d", &playerCount) != 1)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
            continue;
        }

        if (playerCount >= 2 && playerCount <= 4)
            break;

        printf("Please enter 2~4 players.\n");
    }

    for (i = 0; i < playerCount; i++)
    {
        printf("\nPlayer %d\n", i + 1);
        createPlayer(&players[i]);
    }

    printf("\n=== Player Information ===\n");

    for (i = 0; i < playerCount; i++)
    {
        printPlayer(&players[i]);
        printf("\n");
    }

    while (round <= 3)
    {
        printf("\n=== Round %d ===\n", round);

        for (i = 0; i < playerCount; i++)
        {
            dice = rand() % 6 + 1;

            printf("\n%s rolled %d\n",
                   players[i].name, dice);

            movePlayer(&players[i], dice);
            printPlayer(&players[i]);
        }

        round++;
    }

    printf("\n=== Final Player Information ===\n");

    for (i = 0; i < playerCount; i++)
    {
        printPlayer(&players[i]);
        printf("\n");
    }

    return 0;
}