#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "accounts.h"

#define EXPAND_ACL 1000
#define SHRINK_ACL 1001

#define ERR_ACC_N "INCORRECT ACCOUNT NUMBER"

// intiate an account (avoid using it explcitly use bank_managment--createaccount instead)
account _init_account(char *accn, char *acch, double amm)
{
    account acc;

    if (strlen(accn) != ACCOUNT_NBR_LEN)
    {
        puts(ERR_ACC_N);
        exit(EXIT_FAILURE);
    }

    strcpy(acc.account_number, accn);

    acc.holder_name = malloc(strlen(acch) + 1);
    strcpy(acc.holder_name, acch);

    acc.ammount = amm;

    return acc;
}

// copies an account to another account
void accountcpy(account *dest, account src)
{
    strcpy(dest->account_number, src.account_number);

    if (dest->holder_name == NULL) // check if already allocated
        dest->holder_name = malloc(strlen(src.holder_name));
    else
        dest->holder_name = realloc(dest->holder_name, sizeof(char) * strlen(src.holder_name));
    strcpy(dest->holder_name,src.holder_name);
    dest->ammount = src.ammount;
}

// prints the account details
void printacc(account ac)
{
    printf("->Account Number :%s \n->Holder Name : %s \n->Ammount : %f MAD\n", ac.account_number, ac.holder_name, ac.ammount);
}

// prints the account details in table format
void printaccTable(account ac)
{
    printf("|| Account Number :%s | Holder Name : %s | Ammount : %f MAD ||\n", ac.account_number, ac.holder_name, ac.ammount);
}

// compare two accounts
// returns ture if thier account number match, false if not
bool accountcmp(account acc1, account acc2)
{
    return (strcmp(acc1.account_number, acc2.account_number) == 0) ? true : false;
}

// compare two accounts
// returns ture if they're equal, false if not
bool accountsequal(account acc1, account acc2)
{
    return ((strcmp(acc1.account_number, acc2.account_number) == 0) &&
            (strcmp(acc1.holder_name, acc2.holder_name) == 0) &&
            (acc1.ammount == acc2.ammount))
               ? true
               : false;
}

// initiate an accountList
AccountsList _init_accountList()
{
    AccountsList acl;
    acl.length = 0;
    acl.elements = calloc(1, sizeof(*acl.elements));
    acl.size = 1;
    return acl;
}

// expand or shrink the already allocated memory of accountList
void _modify_accountList(AccountsList *acl, int mod_type)
{
    switch (mod_type)
    {
    case SHRINK_ACL:
        acl->size--; // decrease size
        break;
    case EXPAND_ACL:
        acl->size++; // increase size
        break;
    default:
        return; // useless
        break;
    }

    acl->elements = realloc(acl->elements, (acl->size) * sizeof(*acl->elements)); // reallocate the memory allocated of the elements pointer to fit the size of the account list

    if (acl->elements == NULL)
    {
        errno = ENOMEM;
        fprintf(stderr, "Error :%s", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

// add an element to the end of an accountList
void addElement(AccountsList *acl, account acc)
{
    _modify_accountList(acl, EXPAND_ACL); // expand the account list to fit the new element
    acl->elements[acl->length] = acc;     // assign the account to the accountList
    acl->length++;                        // icrease the lenght
}

// remove the last element of an accountList
void popElement(AccountsList *acl)
{
    acl->length--;                        // decrease the lenght
    _modify_accountList(acl, SHRINK_ACL); // shrink the account list
}

// removes an account from an accountList if found otherwise returns -1
signed int removeElement(AccountsList *acl, account acc)
{
    // steps detect account if exits
    signed int _index = indexOfAccount(*acl, acc);
    if (_index == NOT_FOUND)
    {
        return NOT_FOUND;
    }
    else
    {
        removeElementAt(acl,_index);
    }
}

// removes an account from an accountList if found otherwise returns -1
signed int removeElementAt(AccountsList *acl, int _index)
{
    if (_index + 1 > acl->length || _index < 0)
    {
        return NOT_FOUND;   
    }
    // rearrenge the elements to pop the last element
    // lenght-1 to stop at second last element to prevent going out of range
    for (int i = _index; i < acl->length - 1; i++)
    {
        accountcpy(acl->elements + i, acl->elements[i + 1]);
    }
    // remove the last element
    popElement(acl);
    return 0;
}
// returns the index of the given account
// returns -1 if not found
// NOTE : it matches the account number only
signed int indexOfAccount(AccountsList acl, account acc)
{
    for (int index = 0; index < acl.length; index++)
    {
        if (accountcmp(acl.elements[index], acc))
        {
            return index;
        }
    }
    return NOT_FOUND;
}

void printAccountlist(AccountsList acl)
{
    for (int index = 0; index < acl.length; index++)
    {
        printf("Account %d :\n", index + 1);
        printacc(acl.elements[index]);
    }
}

void printAccountsTable(AccountsList acl)
{
    for (int index = 0; index < acl.length; index++)
    {
        printf("-%d ", index + 1);
        printaccTable(acl.elements[index]);
    }
}
