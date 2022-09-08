#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include "model.h"

#define EXPAND_ACL 1000
#define SHRINK_ACL 1001
// opens the data.txt file with the given mode
FILE *openData(char *mode)
{
    FILE *data;
    data = fopen("data.txt", mode);
    if (data == NULL)
    {
        fprintf(stderr, "Can't open data.txt file :%s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    return data;
}

// get an accountslist from the opened data file
// consider that the data is well formatted
AccountsList getData()
{
    FILE *data = openData("r");

    char account_number_buff[ACCOUNT_NBR_LEN + 1];
    char first_name_buff[255];
    char last_name_buff[255];
    char holder_name_buff[255];
    double ammount_buff;

    AccountsList acl = _init_accountList();
    while (fscanf(data, "%s%s%s%lf", account_number_buff, first_name_buff, last_name_buff, &ammount_buff) != EOF)
    {
        sprintf(holder_name_buff, "%s %s", first_name_buff, last_name_buff);
        account tempacc = _init_account(account_number_buff, holder_name_buff, ammount_buff);
        addElement(&acl, tempacc);
    }

    fclose(data);
    return acl;
}

// writes an AccountsList in the data file

void writeData(AccountsList acl)
{
    FILE *data = openData("w");

    for (int i = 0; i < acl.length; i++)
    {
        account tempacc = acl.elements[i];
        char firstN_buff[255];
        char lastN_buff[255];
        for (int i = 0; i < 255; i++) // clear garbage
        {
            firstN_buff[i] = 0;
            lastN_buff[i] = 0;
        }

        if (sscanf(tempacc.holder_name, "%s %s", firstN_buff, lastN_buff) != 2)
        {
            strcpy(lastN_buff,"(null)");
            
        }
        fprintf(data, "%s %s %s %lf\n", tempacc.account_number, firstN_buff, lastN_buff, tempacc.ammount);
    }

    fclose(data);
}
