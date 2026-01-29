#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "function.h"

int main() {
    int choice;

    while (1) {
        printf("-------Bank Management System-------\n\n");
        printf("1. Create account.\n");
        printf("2. Deposite amount.\n");
        printf("3. Withdraw amount.\n");
        printf("4. List accounts.\n");
        printf("5. Search account.\n");
        printf("6. Save and exit.\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_account();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                list_accounts();
                break;
            case 5:
                search_account();
                break;
            case 6:
                exit(0);
            default:
                printf("\nInvalid option! Try again.\n\n");
        }
    }
    return 0;
}