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

int checkUser(char *id, char *password)
{
    char filename[idLimit + 10] = "./users/";
    char type[] = ".txt";
    strncat(filename, id, strlen(id));
    strcat(filename, type);

    FILE *fptr;
    fptr = fopen(filename, "rb");
    if (fptr == NULL)
    {
        return 0;
    }

    char passwordCheck[passwordLimit];
    fread(passwordCheck, sizeof(passwordCheck), 1, fptr);
    fclose(fptr);

    if (strcmp(password, passwordCheck) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void User(char *id)
{
    // clear screen
    system("cls");

    char filename[idLimit + 10] = "./users/";
    char type[] = ".txt";
    strncat(filename, id, strlen(id));
    strcat(filename, type);

    FILE *fptr;
    fptr = fopen(filename, "rb");
    if (fptr == NULL)
    {
        puts("Couldn't open file'");
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

    puts("\n=========================================================================================================");
    puts("================================Welcome in User  Page=============================");
    puts("=========================================================================================================\n");

    print(user);

    // Main LOOP in the Admin
    char choiceA;
    while (1)
    {
        puts("=========================================================================================================\n");
        puts("Enter 1 To Make Transaction\n");
        puts("Enter 2 To Change Account Password\n");
        puts("Enter 3 To Get Cash\n");
        puts("Enter 4 To Deposit in Account\n");
        puts("Enter 5 To Return to main Menu\n");
        puts("=========================================================================================================\n");
        scanf("%c", &choiceA);
        fflush(stdin);
        if (choiceA == '1')
        {
            tran(&user);
            save(user.id, user);
        }
        else if (choiceA == '2')
        {
            changePass(&user);
            save(user.id, user);
        }
        else if (choiceA == '3')
        {
            getCash(&user.balance);
            save(user.id, user);
        }
        else if (choiceA == '4')
        {
            addCash(&user.balance);
            save(user.id, user);
        }
        else if (choiceA == '5')
        {
            puts("Returning to Admin Main Menu\n");
            break;
        }
        else
        {
            puts("Invalid Input Please Retry\n");
        }
        print(user);
    }
}

void changePass(bankAccount *user)
{
    puts("Please Enter your old Password :");
    char password[passwordLimit];
    gets(password);

    if (strcmp(password, user->password) == 0)
    {
        puts("Please Enter your new Password :");
        gets(user->password);
    }
    else
    {
        printf(RED);
        puts("\nINCORRECT password\n");
        printf(WHITE);
    }
}
