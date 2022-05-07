//----------------------------------------------------------------
/* @Author: Ahmed Hany @Ahmed-H300 Github username
 * System for Bank
 * with both User and Admin Interface
 */
//----------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "definitions.h"

void getCash(double *currBalance)
{
    char balance[20];
    do
    {
        puts("\nEnter The amount to withdraw\n");
        gets(balance);

    } while (checkBalance(balance) == 0);

    double amount = 0.0;
    amount = atof(balance);
    if (amount > *currBalance)
    {
        printf(RED);
        puts("\nThe required money is more than your balance number\n");
        printf(WHITE);
        return;
    }
    *currBalance -= amount;
    printf(GREEN);
    puts("\nDone\n");
    printf(WHITE);
}

void save(char *id, bankAccount user)
{
    // saving data in filename
    char filename[idLimit + 10] = "./users/";
    char type[] = ".txt";
    strncat(filename, id, strlen(id));
    strcat(filename, type);

    FILE *fptr;
    fptr = fopen(filename, "wb");

    if (fptr == NULL)
    {
        puts("error in opening file");
        return;
    }

    fwrite(user.password, sizeof(user.password), 1, fptr);
    fwrite(user.name, sizeof(user.name), 1, fptr);
    fwrite(user.address, sizeof(user.address), 1, fptr);
    fwrite(user.nationalID, sizeof(user.nationalID), 1, fptr);
    fwrite(&user.age, sizeof(user.age), 1, fptr);
    if (user.age < 21)
    {
        fwrite(user.gNationalID, sizeof(user.gNationalID), 1, fptr);
    }
    fwrite(user.id, sizeof(user.id), 1, fptr);
    fwrite(&user.accountStatus, sizeof(user.accountStatus), 1, fptr);
    fwrite(&user.balance, sizeof(user.balance), 1, fptr);
    fclose(fptr);
}

void addCash(double *currBalance)
{
    char balance[20];
    do
    {
        puts("\nEnter The amount to add\n");
        gets(balance);

    } while (checkBalance(balance) == 0);

    double amount = 0.0;
    amount = atof(balance);

    *currBalance += amount;
    printf(GREEN);
    puts("\nDone\n");
    printf(WHITE);
}

void tran(bankAccount *userold)
{
    if (userold->accountStatus != ACTIVE)
    {
        printf(RED);
        puts("This Account(which money will be transferred from) is not active");
        printf(WHITE);
        return;
    }
    puts("Enter the id of the account to transfer to\n");
    char id[idLimit];
    gets(id);
    if (getUser(id) == 1)
    {
        char filename[idLimit + 10] = "./users/";
        char type[] = ".txt";
        strncat(filename, id, strlen(id));
        strcat(filename, type);

        FILE *fptr;
        fptr = fopen(filename, "rb");
        if (fptr == NULL)
        {
            puts("Couldn't open file'");
            return;
        }

        bankAccount user;
        fread(user.password, sizeof(user.password), 1, fptr);
        fread(user.name, sizeof(user.name), 1, fptr);
        fread(user.address, sizeof(user.address), 1, fptr);
        fread(user.nationalID, sizeof(user.nationalID), 1, fptr);
        fread(&user.age, sizeof(user.age), 1, fptr);
        if (user.age < 21)
        {
            fread(user.gNationalID, sizeof(user.gNationalID), 1, fptr);
        }
        fread(user.id, sizeof(user.id), 1, fptr);
        fread(&user.accountStatus, sizeof(user.accountStatus), 1, fptr);
        fread(&user.balance, sizeof(user.balance), 1, fptr);
        fclose(fptr);

        if (user.accountStatus != ACTIVE)
        {
            printf(RED);
            puts("This Account(which money will be transferred to) is not active");
            printf(WHITE);
            return;
        }

        char balance[20];
        do
        {
            puts("\nEnter The amount to transfer\n");
            gets(balance);

        } while (checkBalance(balance) == 0);

        double amount = 0.0;
        amount = atof(balance);
        if (amount > userold->balance)
        {
            printf(RED);
            puts("\nThe required money is more than your balance number\n");
            printf(WHITE);
            return;
        }
        userold->balance -= amount;

        user.balance += amount;
        save(user.id, user);

        printf(GREEN);
        puts("DONE\n");
        printf(WHITE);
        return;
    }
    else
    {
        printf(RED);
        puts("This ID is not Found\n");
        printf(WHITE);
        return;
    }
}

void print(bankAccount user)
{
    printf(GREEN);
    puts("=============================User information =============================");
    puts(user.password);
    puts(user.name);
    puts(user.address);
    puts(user.nationalID);
    if (user.age < 21)
    {
        puts(user.gNationalID);
    }
    puts(user.id);
    printf("%d\n", user.age);
    if (user.accountStatus == ACTIVE)
    {
        printf("Account Status is :: Ready\n");
    }
    else if (user.accountStatus == RESTRICTED)
    {
        printf("Account Status is :: RESTRICTED\n");
    }
    else if (user.accountStatus == CLOSED)
    {
        printf("Account Status is :: CLOSED\n");
    }
    printf("%lf\n", user.balance);
    printf(WHITE);
}
