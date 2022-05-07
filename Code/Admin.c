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

int checkAdmin(char *id, char *password)
{
    if ((strcmp(id, usernameA) == 0) && (strcmp(password, passwordA) == 0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Admin()
{
    // clear screen
    system("cls");

    puts("\n=========================================================================================================");
    puts("===========================================Welcome in Admin Page========================================");
    puts("=========================================================================================================\n");

    // Main LOOP in the Admin
    char choiceA;
    while (1)
    {
        puts("=========================================================================================================\n");
        puts("Enter 1 To Create New User\n");
        puts("Enter 2 To Open an existing User\n");
        puts("Enter 3 To Exit Admin\n");
        puts("=========================================================================================================\n");
        scanf("%c", &choiceA);
        fflush(stdin);
        if (choiceA == '1')
        {
            createUser();
        }
        else if (choiceA == '2')
        {
            openUser();
        }
        else if (choiceA == '3')
        {
            puts("Exiting Admin\n");
            break;
        }
        else
        {
            puts("Invalid Input Please Retry\n");
        }
    }
}

void UserA(char *id)
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
    puts("================================Welcome in User Admin previlage Page=============================");
    puts("=========================================================================================================\n");

    print(user);

    // Main LOOP in the Admin
    char choiceA;
    while (1)
    {
        puts("=========================================================================================================\n");
        puts("Enter 1 To Make Transaction\n");
        puts("Enter 2 To Change Account Status\n");
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
            int temp = changeState();
            if (temp != -1)
            {
                user.accountStatus = temp;
            }
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

void createUser()
{
    puts("\n=========================================================================================================");
    puts("===========================================Create New User========================================");
    puts("=========================================================================================================\n");

    bankAccount newUser;

    do
    {
        puts("Please Enter New User's Full Name\n");
        gets(newUser.name);

    } while (checkName(newUser.name) == 0);

    puts("\nPlease Enter New User's Full Address\n");
    gets(newUser.address);

    char age[5];
    do
    {
        puts("\nPlease Enter New User's Age\n");
        gets(age);

    } while (checkAge(age) == 0);

    newUser.age = atoi(age);

    do
    {
        puts("\nPlease Enter New User's National ID\n");
        gets(newUser.nationalID);

    } while (checknationalID(newUser.nationalID) == 0);

    if (newUser.age < 21)
    {
        do
        {
            puts("\nPlease Enter Guardian National ID\n");
            gets(newUser.gNationalID);

        } while (checknationalID(newUser.gNationalID) == 0);
    }

    char balance[20];
    do
    {
        puts("\nPlease Enter New User's Balance\n");
        gets(balance);

    } while (checkBalance(balance) == 0);

    newUser.balance = atof(balance);

    newUser.accountStatus = ACTIVE;

    FILE *fptr;
    char filename[idLimit + 15] = "./users/";
    do
    {
        // to be uniqued id
        srand((unsigned int)(time(NULL)));

        long long num = (rand() % (UPPERID - LOWERID + 1)) + LOWERID;

        sprintf(newUser.id, "%lld", num);

        char type[] = ".txt";
        strncat(filename, newUser.id, strlen(newUser.id));
        strcat(filename, type);

        fptr = fopen(filename, "rb");

    } while (fptr != NULL);

    // password -> to not make all passwords of the same size
    int rNum = (rand() % (UPPERPASS - LOWERPASS + 1)) + LOWERPASS;

    // Password randomizer
    randomPasswordGeneration(rNum, newUser.password);

    newUser.password[rNum] = '\0';

    // saving data in filename
    fptr = fopen(filename, "wb");

    if (fptr == NULL)
    {
        puts("error in opening file");
        return;
    }

    fwrite(newUser.password, sizeof(newUser.password), 1, fptr);
    fwrite(newUser.name, sizeof(newUser.name), 1, fptr);
    fwrite(newUser.address, sizeof(newUser.address), 1, fptr);
    fwrite(newUser.nationalID, sizeof(newUser.nationalID), 1, fptr);
    fwrite(&newUser.age, sizeof(newUser.age), 1, fptr);
    if (newUser.age < 21)
    {
        fwrite(newUser.gNationalID, sizeof(newUser.gNationalID), 1, fptr);
    }
    fwrite(newUser.id, sizeof(newUser.id), 1, fptr);
    fwrite(&newUser.accountStatus, sizeof(newUser.accountStatus), 1, fptr);
    fwrite(&newUser.balance, sizeof(newUser.balance), 1, fptr);
    fclose(fptr);

    print(newUser);
}

int checkName(char *name)
{
    int len = strlen(name);
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        if (name[i] == ' ')
        {
            count++;
        }
    }
    if (count >= 3)
    {
        return 1;
    }
    puts("please Enter at least 4 names");
    return 0;
}

int checkAge(char *age)
{
    int ageNum = atoi(age);
    if (ageNum > 0)
    {
        return 1;
    }
    puts("please Enter a valid age");
    return 0;
}

int checknationalID(char *nationalID)
{
    if (strlen(nationalID) == 14)
    {
        return 1;
    }
    puts("please Enter a valid nationalID");
    return 0;
}

int checkBalance(char *balance)
{
    int balanceNum = atof(balance);
    if (balanceNum > 0)
    {
        return 1;
    }
    puts("please Enter a valid Balance");
    return 0;
}

void randomPasswordGeneration(int N, char *password)
{
    int random;
    // to be uniqued id
    srand((unsigned int)(time(NULL)));
    // Array of numbers
    char numbers[] = "0123456789";
    // Array of small alphabets
    char letter[] = "abcdefghijklmnoqprstuvwyzx";
    // Array of capital alphabets
    char LETTER[] = "ABCDEFGHIJKLMNOQPRSTUYWVZX";
    for (int i = 0; i < N; i++)
    {
        random = rand() % 3;
        if (random == 0)
        {
            password[i] = numbers[rand() % 10];
        }
        else if (random == 1)
        {
            password[i] = letter[rand() % 26];
        }
        else
        {
            password[i] = LETTER[rand() % 26];
        }
    }
}

void openUser()
{
    // clear screen
    system("cls");

    puts("\n=========================================================================================================");
    puts("=========================================Open Existing Account======================================");
    puts("=========================================================================================================\n");

    puts("\nEnter id\n");

    char id[idLimit];
    gets(id);
    if (getUser(id) == 1)
    {
        UserA(id);
    }
    else
    {
        printf("This ID is not Found!\n");
    }
}

int getUser(char *id)
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
    else
    {
        fclose(fptr);
        return 1;
    }
}

int changeState()
{
    puts("=========================================================================================================\n");
    puts("Enter 1 To Set Account to Active State\n");
    puts("Enter 2 To Set Account to Restricted State\n");
    puts("Enter 3 To Set Account to Closed\n");
    puts("=========================================================================================================\n");
    char choiceA;
    scanf("%c", &choiceA);
    fflush(stdin);
    if (choiceA == '1')
    {
        return ACTIVE;
    }
    else if (choiceA == '2')
    {
        return RESTRICTED;
    }
    else if (choiceA == '3')
    {
        return CLOSED;
    }
    else
    {
        puts("Invalid Input Please Retry\n");
        return -1;
    }
}