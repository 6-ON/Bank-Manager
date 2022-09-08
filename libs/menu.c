#define MODE_KEY "stty raw"
#define MODE_LINE "stty cooked"

// menu choices
#define MENU_CHOICE_1 1
#define MENU_CHOICE_2 2
#define MENU_CHOICE_3 3
#define MENU_CHOICE_4 4
#define MENU_CHOICE_5 5
#define MENU_CHOICE_6 6
#define MENU_CHOICE_7 7
#define MENU_CHOICE_8 8

// prompts
#define AMMOUNT_PROMPT "Enter the ammount: "
#define PROMPT_ACCOUNT_NUMBER "Enter the account number of the account : "
#define CONFIRMATION_PROMPT "CONFIRM ? y/n"
// messages
#define MSG_ADDED_ACCOUNT "Account Added successfully"
#define MSG_OPERATION_DONE "Operation done successfully"
// errors messages
#define ERR_WRONG_INPUT "Wrong input !!"
#define ERR_ACCOUNT_NOT_FOUND "The account is not found do you want to create an account with the given account number? y/n"
// err nums
#define WRONG_INPUT 0

// std libs includes
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// my libs includes
#include "bank_management.h"
#include "menu.h"
AccountsList accs;

int cleanGetInt(int *val)
{
    char buff[255];

    fgets(buff, sizeof(buff), stdin);
    if (sscanf(buff, "%d", val) == WRONG_INPUT)
    {
        puts(ERR_WRONG_INPUT);
        return -1;
    }
    return 0;
}
int cleanGetDouble(double *val)
{
    char buff[255];

    fgets(buff, sizeof(buff), stdin);
    if (sscanf(buff, "%lf", val) == WRONG_INPUT)
    {
        puts(ERR_WRONG_INPUT);
        return -1;
    }
    return 0;
}
// returns  index of  the account selected
int selectFromTable()
{
    // system(CLS);
    printAccountsTable(accs);
    puts("<-- 0 ");
    int index;
    while (true)
    {
        printf(">> ");
        if (cleanGetInt(&index) == -1)
            continue;
        if (index > 0 && index < accs.length + 1)
            break;
        else if (index == 0)
        {
            puts("going back to menu...");
            return -1;
        }
        else
            puts(ERR_WRONG_INPUT);
    }
    return index - 1;
}

void operate(int (*operation)(account *, double), int _index)
{
    while (true)
    {
        double ammDeposit;
        printf(AMMOUNT_PROMPT);
        if(cleanGetDouble(&ammDeposit)==-1) continue;;
        if (ammDeposit <= 0)
        {
            puts(ERR_WRONG_INPUT);
        }
        else
        {
            int rslt = operation(accs.elements + _index, ammDeposit);
            switch (rslt)
            {
            case SUCCESS:
                break;
            case ERR_NO_IDENTITY:
                break;
            case ERR_NOT_ENOUGH_MONEY:
                break;
            default:
                puts("unknown error  ");
            }
            writeData(accs);

            puts(MSG_OPERATION_DONE);
            break;
        }

    }
}
void selectOperate(int (*operation)(account *, double))
{
    int selected;
    selected = selectFromTable();
    system(CLS);
    printacc(accs.elements[selected]);
    if (selected + 1)
        operate(operation, selected);
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
void Menu()
{
    printMenu();
    int input;
    if (cleanGetInt(&input) == -1)
        return;
    // printf("TODO %d",input);
    switch (input)
    {
    case MENU_CHOICE_1:
        system(CLS);
        // getchar();// clears an extra newline from stdin character to avoid using it
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
        system(CLS);
        puts("|Select Sender|");
        int selectedSender = selectFromTable();
        if (!(selectedSender + 1))
            return ;

        step_2:
        system(CLS);
        printf("Sender >>");
        printaccTable(accs.elements[selectedSender]);
        puts("|Select Receiver|");
        int selectedReceiver = selectFromTable();
        if (!(selectedReceiver + 1))
            return ;
        if(selectedReceiver == selectedSender)
            goto step_2;
        system(CLS);
        printf("Sender >>");
        printaccTable(accs.elements[selectedSender]);

        printf("Receiver >>");
        printaccTable(accs.elements[selectedReceiver]);
        printf(AMMOUNT_PROMPT);
        
        double ammount;
        
        while (cleanGetDouble(&ammount) == -1 || ammount < 0)
        {
            printf("enter a valid number>> ");
        }
        switch(transfer(accs.elements + selectedSender, accs.elements + selectedReceiver, ammount)){
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
        break;
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
