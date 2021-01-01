#include <stdio.h>
#include <stdlib.h>
#include "myheader.h"
struct account_info {
    char *first_name;
    char *last_name;
    char *house_addr;
    char *phone_no;
    int initial_deposit;
};
typedef struct account_info account_info;
int createacc(void) {
    account_info acc;
    acc.first_name = (char*) malloc(35 *sizeof(char));
    acc.last_name = (char*) malloc(35* sizeof(char));
    acc.house_addr =(char*) malloc(100 *sizeof(char));
    acc.phone_no = (char*) malloc(50 *sizeof(char));
    getchar();
    printf("Enter your first name[35 chars only]: ");
    mygetline(acc.first_name, 35);
    printf("Enter your last name[35 chars only]: ");
    mygetline(acc.last_name, 35);
    printf("Enter your house adderess[100 chars only]: ");
    mygetline(acc.house_addr, 35);
    printf("Enter your phone number[10 chars only]: ");
    mygetline(acc.phone_no, 35);
    do {
        printf("Enter initial deposit amount [min:500]: ");
        scanf("%d", &acc.initial_deposit);
    } while (acc.initial_deposit < 500);

    printf("%s---%s---%s---%s---%d\n", acc.first_name, acc.last_name, acc.phone_no, acc.house_addr, acc.initial_deposit);
    char *totstring = (char*) malloc(200 * sizeof(char));
   sprintf(totstring, "{\"first name\":\"%s\",\"last name\":\"%s\",\"house address\":\"%s\",\"phone number\":\"%s\", \"balance\": %d}",acc.first_name, acc.last_name,acc.house_addr, acc.phone_no, acc.initial_deposit);
    getchar();
    printf("%s...\n", totstring);
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
        switch (option) {
            case 1:
                createacc();
        }
    } while (option != 8);
    return 0;
}
