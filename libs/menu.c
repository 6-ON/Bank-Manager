// menu choices
#define CREATE_ACCOUNT 1
#define DEPOSIT 2
#define WITHDRAW 3
#define TRANSFER 4
#define DELETE 5
#define SHOW_ACCOUNT 6
#define SHOW_ACCOUNTS 7
#define EXIT_MENU 8
#define BACK_TO_MENU -1

// prompts
#define AMMOUNT_PROMPT "Enter the ammount: "
#define PROMPT_ACCOUNT_NUMBER "Enter the account number of the account : "
#define CONFIRMATION_PROMPT "CONFIRM ? y/n"
#define PROMPT_CONFIRM_DELETION "Are you sure you want delete this account Y/n? "
// messages
#define MSG_ADDED_ACCOUNT "Account Added successfully"
#define MSG_OPERATION_DONE "Operation done successfully"
#define MSG_REMOVED_ACC "Account removed successfully..."
// errors messages
#define ERR_WRONG_INPUT "Wrong input !!"
#define ERR_OOR "OUT OF RANGE !!"
#define ERR_ACCOUNT_NOT_FOUND "The account is not found do you want to create an account with the given account number? y/n"
#define ERR_NEGATIVE_AMMOUT "error: you cant enter a negative ammount"
#define NOT_ENOUGH_MONEY "YOU DONT HAVE ENGOUGH MONEY FOR THIS OPERATION !!"
// err nums
#define WRONG_INPUT 0

// std libs includes
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

// my libs includes
#include "bank_management.h"
#include "menu.h"
AccountsList accs;
// get int
void getInt(int *val)
{
    while (true)
    {
        char buff[255];
        fgets(buff, sizeof(buff), stdin);
        if (sscanf(buff, "%d", val) == WRONG_INPUT)
        {
            puts(ERR_WRONG_INPUT);
            printf("|>> ");
            continue;
        }
        break;
    }
}

void getDouble(double *val)
{
    while (true)
    {
        char buff[255];
        fgets(buff, sizeof(buff), stdin);
        if (sscanf(buff, "%lf", val) == WRONG_INPUT)
        {
            puts(ERR_WRONG_INPUT);
            printf(">> ");
            continue;
        }
        break;
    }
}
// returns  index of  the account selected
int selectFromTable()
{
    printAccountsTable(accs); // print Table
    puts("<-- 0 ");           // add 0
prompt:;
    int index;
    printf(">> ");
    getInt(&index); // prompt index and set it

    if (index == 0)
    {
        puts("going back to menu...");
        return BACK_TO_MENU;
    }
    else if (index < 0 || index > accs.length + 1)
    {
        puts(ERR_OOR);
        goto prompt;
    }
    return index - 1;
}

void operate(int (*operation)(account *, double), int _index)
{
restart:
    printf(AMMOUNT_PROMPT);
    double operationAmmount;
    getDouble(&operationAmmount);

    if (operationAmmount < 0)
    {
        puts(ERR_NEGATIVE_AMMOUT);
        goto restart;
    }
    else
    {
        int rslt = operation(accs.elements + _index, operationAmmount);
        switch (rslt)
        {
        case SUCCESS:
            puts(MSG_OPERATION_DONE);
            writeData(accs);
            break;
        case ERR_NO_IDENTITY:
            break;
        case ERR_NOT_ENOUGH_MONEY:
            puts(NOT_ENOUGH_MONEY);
            break;
        default:
            puts("unknown error  ");
        }
    }
}

void selectOperate(int (*operation)(account *, double))
{
    int selected;
    selected = selectFromTable();

    switch (selected)
    {
    case BACK_TO_MENU:
        // return;
        break;
    default:
        system(CLS);
        printacc(accs.elements[selected]);
        operate(operation, selected);
        break;
    }
}

void printMenu()
{
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
           "1- create account",
           "2- deposit",
           "3- withraw",
           "4- transfer",
           "5- delete",
           "6- show account detail",
           "7- show accounts list",
           "8- exit program");
}

void showTransferView()
{
step_1:
    system(CLS);
    puts("|Select Sender|");
    int selectedSender = selectFromTable();
    if (selectedSender == BACK_TO_MENU)
    {
        return;
    }

step_2:
    system(CLS);
    printf("Sender >>");
    printaccTable(accs.elements[selectedSender]);
    puts("|Select Receiver|");
    int selectedReceiver = selectFromTable();
    if (selectedReceiver == BACK_TO_MENU)
    {
        goto step_1;
    }

    if (selectedReceiver == selectedSender)
    {
        goto step_2;
    }

    system(CLS);
    printf("Sender >>");
    printaccTable(accs.elements[selectedSender]);

    printf("Receiver >>");
    printaccTable(accs.elements[selectedReceiver]);
    printf("\n" AMMOUNT_PROMPT);

    double ammount;

    getDouble(&ammount);

    switch (transfer(accs.elements + selectedSender, accs.elements + selectedReceiver, ammount))
    {
    case SUCCESS:
        puts(MSG_OPERATION_DONE);
        writeData(accs);
        break;
    case ERR_NO_IDENTITY:
        break;
    case ERR_NOT_ENOUGH_MONEY:
        break;
    default:
        break;
    }
}

void showRemoveView()
{
    system(CLS);
    int selected = selectFromTable();
    if (selected == BACK_TO_MENU)
        return;
    system(CLS);
    printacc(accs.elements[selected]);
    printf(PROMPT_CONFIRM_DELETION);
    char confirmationChar = getchar();
    getchar(); // remove \n from stdin buffer
    if (confirmationChar == 'y' || confirmationChar == 'Y')
    {
        removeElement(&accs, accs.elements[selected]);
        puts(MSG_REMOVED_ACC);
        writeData(accs);
    }
    else
    {
        puts("Aborting...");
    }
}

void Menu()
{
    printMenu();
    int input;
    printf(">> ");
    getInt(&input);
    switch (input)
    {
    case CREATE_ACCOUNT:
        system(CLS);
        account newacc = createAccount();
        addElement(&accs, newacc);
        writeData(accs);
        puts(MSG_ADDED_ACCOUNT);
        break;
    case DEPOSIT:
        system(CLS);
        selectOperate(deposit);
        break;
    case WITHDRAW:
        system(CLS);
        selectOperate(withdraw);
        break;
    case TRANSFER:
        showTransferView();
    case DELETE:
        showRemoveView();

        break;
    case SHOW_ACCOUNT:
        break;
    case SHOW_ACCOUNTS:
        break;
    case EXIT_MENU:
        puts("quitting...");
        exit(EXIT_SUCCESS);
        break;
    default:
        fprintf(stderr, ERR_WRONG_INPUT);
        break;
    }
}
