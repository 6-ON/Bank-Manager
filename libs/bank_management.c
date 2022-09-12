#define INVALID_ACCOUNT_CREATED "ERROR : Invalid account number\n"
#define ERR_INALID_AMMOUNT "Invalid Ammount"
// prompts
#define PROMPT_ACCOUNT_NUMBER "Enter the account number \nNOTE : it should be a sequence of 16 character\nThe Account Number: "
#define PROMPT_HOLDER_NAME "Enter the account holder name : "
#define PROMPT_AMMOUNT "Enter the initial ammount : "

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bank_management.h"

// retunrs 0 if in success 1 if the account have no identity
int deposit(account *acc, double amm)
{

	if (strlen(acc->account_number) == ACCOUNT_NBR_LEN)
	{
		acc->ammount += amm;
		return SUCCESS;
	}
	else
	{
		return ERR_NO_IDENTITY;
	}
}

// returns 0 if sucess
// returns 1 if the account have no identity
// returns 2 if the ammount is bigger than the account's ammount
int withdraw(account *acc, double amm)
{
	if (strlen(acc->account_number) == ACCOUNT_NBR_LEN)
	{
		if (acc->ammount >= amm)
		{
			acc->ammount -= amm;
			return SUCCESS;
		}
		else
		{
			return ERR_NOT_ENOUGH_MONEY;
		}
	}
	else
	{
		return ERR_NO_IDENTITY;
	}
}

// returns 0 if transaction comppleted successfully
// reutrns 1 if either sender or receiver  don't identified
// returns 2 if sender don't have enough money
int transfer(account *sacc, account *racc, double amm)
{
	switch (withdraw(sacc, amm))
	{
	case 0:
		if (deposit(racc, amm) == 0)
		{
			return SUCCESS;
		}
		else
		{
			deposit(sacc, amm); // give the sender his money
			return ERR_NO_IDENTITY;
		}
		break;
	case ERR_NO_IDENTITY:
		return ERR_NO_IDENTITY;
		break;
	case ERR_NOT_ENOUGH_MONEY:
		return ERR_NOT_ENOUGH_MONEY;
		break;
	}
}
// prompt  for account details and returns a variable type account or null variable if the account number is not valid
account createAccount()
{
	char acc_num_buff[100];
	char acc_holder_buff[100];
	char acc_ammount_buff[100];

	account createdAccount;

	char initAccountNumber[ACCOUNT_NBR_LEN + 1];
	while (true)
	{
		printf(PROMPT_ACCOUNT_NUMBER);
		fgets(acc_num_buff, sizeof(acc_num_buff), stdin);
		sscanf(acc_num_buff, "%s", initAccountNumber);

		if (initAccountNumber == NULL || strlen(initAccountNumber) != ACCOUNT_NBR_LEN)
		{
			puts(INVALID_ACCOUNT_CREATED);
			// sleep and clear
		}
		else
			break;
	}

	char initHolderName[255];
	while (true)
	{
		printf(PROMPT_HOLDER_NAME);
		char initLastName[255];
		char initFirstName[255];
		fgets(acc_holder_buff, sizeof(acc_holder_buff), stdin);
		if (sscanf(acc_holder_buff, "%s %s", initFirstName, initLastName) != 2)
		{
			puts("invalid name");
			continue;
		}
		sprintf(initHolderName, "%s %s", initFirstName, initLastName);
		break;
	}

	double initAmmount;
	while (true)
	{
		printf(PROMPT_AMMOUNT);
		fgets(acc_ammount_buff, sizeof(acc_ammount_buff), stdin);
		if (sscanf(acc_ammount_buff, "%lf", &initAmmount) != 1 || initAmmount < 0)
		{
			puts(ERR_INALID_AMMOUNT);
			continue;
		}
		break;
	}

	createdAccount = _init_account(initAccountNumber, initHolderName, initAmmount);
	return createdAccount;
}
