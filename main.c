#include <stdio.h>
#include <stdlib.h>
#include "myheader.h"
struct account_info {
    char *first_name;
    char *acc_no;
    char *last_name;
    char *house_addr;
    char *phone_no;
    char *password;
    int initial_deposit;
};
typedef struct account_info account_info;
int transaction(void) {
    char name[35];
    int opt, amount;
    printf("Enter your first name[35 chars only]: ");
    scanf("%s", name);
    if (!db_find_name(name)) {
        do {
            printf("what do you wanna do?\n");
            printf("[1]debit\n");
            printf("[2]credit\n");
            printf("[3]exit\n:: ");
            scanf("%d", &opt);
            switch (opt) {
                case 1:
                    printf("Enter the amount you wanna debit[min balance = 500]: ");
                    scanf("%d", &amount);
                    db_transact(name, amount, 'd');
                    break;
                case 2:
                    printf("Enter the amount you wanna credit[min balance = 500]: ");
                    scanf("%d", &amount);
                    db_transact(name, amount, 'c');
                    break;
                default:
                    printf("unknown option\n");
                    break;
            } 

        } while (opt != 3);
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
        
}

int create_new_account(void) {
    account_info acc;
    acc.first_name = (char*) malloc(35 *sizeof(char));
    acc.last_name = (char*) malloc(35* sizeof(char));
    acc.house_addr =(char*) malloc(100 *sizeof(char));
    acc.phone_no = (char*) malloc(50 *sizeof(char));
    acc.password = (char*) malloc(100 *sizeof(char));
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
    acc.acc_no = acc_no_gen();
   sprintf(totstring, "{\"first name\":\"%s\",\"acc_no\":\"%s\", \"last name\":\"%s\",\"house address\":\"%s\",\"phone number\":\"%s\",\"balance\": %d}", acc.first_name, acc.acc_no, acc.last_name, acc.house_addr, acc.phone_no, acc.initial_deposit);
    getchar();
    printf("%s...\n", totstring);
    db_create(totstring);
    return 0;
}

    
int main() {
    int option;
    char name[35], disopt;
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
                create_new_account();
				update_seed();
                break;
            case 4:
				do {
					printf("What do you want to enter?\n[1]name\n[2]account number\n[3]exit\n:: ");
					getchar();
					disopt = getchar();
					getchar();
					switch (disopt) {
						case '1':
							printf("Enter the name: ");
							scanf("%s", name);
							db_display(name, NULL);
							break;
						case '2':
							printf("Enter your account number: ");
							scanf("%s", name);
							db_display(NULL, name);
							break;
						case '3':
							break;
						default:
							printf("Unknown option\n");
							break;
					}
				} while (disopt != '3');
				break;
            case 5:
                printf("Enter the name to search: ");
                char name[35];
                scanf("%s", name);
                db_remove(name);
                break;
            case 3:
                if (!transaction())
                    printf("account not found\n");
                break;
        }
    } while (option != 8);
    return 0;
}
