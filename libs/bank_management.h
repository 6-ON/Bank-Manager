#ifndef BANK_MANAGEMENT_H
#define BANK_MANAGEMENT_H

#define SUCCESS 0

#define ERR_NO_IDENTITY 1

#define ERR_NOT_ENOUGH_MONEY 2

#include "accounts.h"

int deposit(account *acc, double amm);

int withdraw(account *acc, double amm);

int transfer(account *sacc, account *racc, double amm);

account createAccount();

#endif
