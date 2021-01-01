#include <stdio.h>
#include <stdlib.h>
#include "myheader.h"
struct account_info {
    char **first_name;
    char **last_name;
    char **house_addr;
    char **phone_no;
    int initial_deposit;
};
typedef struct account_info account_info;
int createacc(void) {
    account_info acc;
    acc.first_name = (char**) malloc(sizeof(char *));
    acc.last_name = (char**) malloc(sizeof(char *));
    acc.house_addr =(char**) malloc(sizeof(char *));
    acc.phone_no = (char**) malloc(sizeof(char *));

    size_t n; 
    getchar();
    printf("Enter your first name[35 chars only]: ");
    //n = 35;
    getline(acc.first_name, &n, stdin);
    printf("Enter your last name[35 chars only]: ");
    //n = 35;
    getline(acc.last_name, &n, stdin);
    printf("Enter your house adderess[100 chars only]: ");
    //n = 100;
    getline(acc.house_addr, &n, stdin);
    printf("Enter your phone number[10 chars only]: ");
    //n = 10;
    getline(acc.phone_no, &n, stdin);
    char totstring[200];
    sprintf(totstring, "{\"first name\":\"%s\"\n\"last name\":\"%s\"\n\"house address\":\"%s\"\n\"phone number\":\"%s\"}\n",*acc.first_name, *acc.last_name, *acc.house_addr, *acc.phone_no);
    db(totstring);
    return 0;
}

    


int main() {
    int option;
    do {
        printf("%s",
                "\tBANK MANAGEMENT SYSTEM\t\n"
                "\t###welcome to the main menu###\t\n"
                "[1]Enter 1 to create account\n"
                "[2]Update info of existing account\n"
                "[3]Transactions\n"
                "[4]Check the details of an existing account\n"
                "[5]Remove existing account\n"
                "[6]View customer's list\n"
                "[7]ATM Feature\n"
                "[8]Exit\n"
                "Enter your choice: "
              );
        scanf("%d", &option);
    } while (option != 8);
    createacc();
    return 0;
}
