// menu choices
#define MENU_CHOICE_1 1
#define MENU_CHOICE_2 2
#define MENU_CHOICE_3 3
#define MENU_CHOICE_4 4
#define MENU_CHOICE_5 5
#define MENU_CHOICE_6 6
#define MENU_CHOICE_7 7
#define MENU_CHOICE_8 8
#define BACK_TO_MENU -1

// prompts
#define AMMOUNT_PROMPT "Enter the ammount: "
#define PROMPT_ACCOUNT_NUMBER "Enter the account number of the account : "
#define CONFIRMATION_PROMPT "CONFIRM ? y/n"
// messages
#define MSG_ADDED_ACCOUNT "Account Added successfully"
#define MSG_OPERATION_DONE "Operation done successfully"
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
        if (sscanf(buff, "%d", &val) == WRONG_INPUT)
        {
            puts(ERR_WRONG_INPUT);
            printf(">> ");
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
        if (sscanf(buff, "%lf", &val) == WRONG_INPUT)
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
prompt:
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
    double ammDeposit;
    printf(AMMOUNT_PROMPT);
    getDouble(&ammDeposit);

    if (ammDeposit < 0)
    {
        goto restart;
        puts(ERR_NEGATIVE_AMMOUT);
    }
    else
    {
        int rslt = operation(accs.elements + _index, ammDeposit);
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
    system(CLS);
    printacc(accs.elements[selected]);

    switch (selected)
    {
    case BACK_TO_MENU:
        return;
        break;
    default:
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
    system(CLS);
    puts("|Select Sender|");
    int selectedSender = selectFromTable();
    if (!(selectedSender + 1))
        return;

step_2:
    system(CLS);
    printf("Sender >>");
    printaccTable(accs.elements[selectedSender]);
    puts("|Select Receiver|");
    int selectedReceiver = selectFromTable();
    if (!(selectedReceiver + 1))
        return;
    if (selectedReceiver == selectedSender)
        goto step_2;
    system(CLS);
    printf("Sender >>");
    printaccTable(accs.elements[selectedSender]);

    printf("Receiver >>");
    printaccTable(accs.elements[selectedReceiver]);
    printf(AMMOUNT_PROMPT);

    double ammount;

    getDouble(&ammount);

    printf("enter a valid number>> ");

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

void Menu()
{
    printMenu();
    int input;
    printf(">> ");
    getInt(&input);
    switch (input)
    {
    case MENU_CHOICE_1:
        system(CLS);
        account newacc = createAccount();
        addElement(&accs, newacc);
        writeData(accs);
        puts(MSG_ADDED_ACCOUNT);
        break;
    case MENU_CHOICE_2:
        system(CLS);
        selectOperate(deposit);
        break;
    case MENU_CHOICE_3:
        system(CLS);
        selectOperate(withdraw);
        break;
    case MENU_CHOICE_4:
        showTransferView();
    case MENU_CHOICE_5:

        break;
    case MENU_CHOICE_6:
        break;
    case MENU_CHOICE_7:
        break;
    case MENU_CHOICE_8:
        puts("quitting...");
        exit(EXIT_SUCCESS);
        break;
    default:
        fprintf(stderr, ERR_WRONG_INPUT);
        break;
    }
}
