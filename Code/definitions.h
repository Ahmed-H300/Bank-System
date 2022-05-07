//----------------------------------------------------------------
/* @Author: Ahmed Hany @Ahmed-H300 Github username
 * System for Bank
 * with both User and Admin Interface
 */
//----------------------------------------------------------------

#define usernameA "admin"
#define passwordA "admin"
#define idLimit 11
#define passwordLimit 16
#define nameLimit 50
#define addressLimit 50
#define nationalIDLimit 15
#define gNationalIDLimit 15
#define UPPERID 9999999999
#define LOWERID 1000000000
#define UPPERPASS 15
#define LOWERPASS 5

#define GREEN "\033[0;32m"   // GREEN
#define WHITE "\033[0;37m"   // WHITE
#define RED "\033[0;31m"	 // RED

enum status
{
	ACTIVE,
	RESTRICTED,
	CLOSED
};

typedef struct bankAccount
{
	char password[passwordLimit];
	char name[nameLimit];
	char address[addressLimit];
	char nationalID[nationalIDLimit];
	int age;
	char gNationalID[gNationalIDLimit];
	char id[idLimit];
	int accountStatus;
	double balance;
	
}bankAccount;

void login();
int checkAdmin(char *id, char *password);
int checkUser(char *id, char *password);
void Admin();
void User(char *id);
void UserA(char *id);
void createUser();
int checkName(char *name);
int checkAge(char *age);
int checknationalID(char *nationalID);
int checkBalance(char *balance);
void randomPasswordGeneration(int N, char *password);
void openUser();
int getUser(char *id);
int changeState();
void getCash(double *currBalance);
void addCash(double *currBalance);
void save(char *id, bankAccount user);
void tran(bankAccount *userold);
void changePass(bankAccount *user);
void print(bankAccount user);
