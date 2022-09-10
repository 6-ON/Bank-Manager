#ifndef _ACCOUNTS_H
#define _ACCOUNTS_H

#include <stdbool.h>

// the legal account number length
#define ACCOUNT_NBR_LEN 16

#define NOT_FOUND -1
// the account prototype which contains the common account properities
typedef struct
{
    char account_number[ACCOUNT_NBR_LEN + 1];
    char *holder_name;
    double ammount;
} account;

// a dynamic array of accounts
typedef struct
{
    account *elements;
    int length;
    int size;

} AccountsList;


account _init_account(char* accn,char* acch,double amm);

void printacc(account ac);
void printaccTable(account ac);

bool accountcmp(account acc1, account acc2);

bool accountsequal(account acc1, account acc2);

void accountcpy(account *dest, account src);

// accounList funcs
AccountsList _init_accountList();

void printAccountlist(AccountsList acl);

void printAccountsTable(AccountsList acl);

void addElement(AccountsList *acl, account acc);

void popElement(AccountsList *acl);

signed int removeElement(AccountsList *acl,account acc);

signed int removeElementAt(AccountsList *acl, int _index);

signed int indexOfAccount(AccountsList acl , account acc);

#endif