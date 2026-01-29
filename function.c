#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "function.h"

int account_check(int account) {
    struct Account a;
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp)
        return 0;

    while (fread(&a, sizeof(struct Account), 1, fp)) {
        if (account == a.acc_num) {
            printf("\nAccount already exists!\n\n");
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void Current_time() {
    time_t t;
    struct tm *time_info;

    time(&t);
    time_info = localtime(&t);

    printf("Time: %02d-%02d-%04d  %02d:%02d:%02d\n\n",
        time_info->tm_mday, time_info->tm_mon + 1, time_info->tm_year + 1900,
        time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
}

void create_account() {
    struct Account a;
    int account;
    float balance;

    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) {
        printf("\nError opening file.\n\n");
        return;
    }

    printf("\nEnter account number: ");
    scanf("%d", &account);

    while (account_check(account) != 0) {
        printf("Enter account number: ");
        scanf("%d", &account);
    }

    a.acc_num = account;

    printf("Enter Account holder's name: ");
    scanf(" %[^\n]", a.name);

    printf("Enter account type (Saving/Current): ");
    scanf(" %[^\n]", a.acc_type);

    printf("Enter balance: ");
    scanf("%f", &balance);

    while (balance < 5000.00) {
        printf("\nMinimum balance: Rs. 5,000\n\n");
        printf("Enter balance: ");
        scanf("%f", &balance);
    }

    a.balance = balance;

    fwrite(&a, sizeof(struct Account), 1, fp);

    printf("\n");
    printf("Account created successfully!\n\n");

    fclose(fp);
}

void deposit() {
    FILE *fp;
    struct Account a;
    int acc_no, found = 0;
    float amount;

    fp = fopen(FILE_NAME, "rb+");
    if (fp == NULL) {
        printf("\nFile not found.\n\n");
        return;
    }

    printf("\nEnter account number: ");
    scanf("%d", &acc_no);

    printf("Enter deposit amount: ");
    scanf("%f", &amount);

    while (fread(&a, sizeof(struct Account), 1, fp)) {
        if (a.acc_num == acc_no) {
            if (amount > 0) {
                a.balance += amount;

                fseek(fp, -sizeof(struct Account), SEEK_CUR);
                fwrite(&a, sizeof(struct Account), 1, fp);

                printf("\nDeposit successful. New balance: %.2f\n", a.balance);
                Current_time();
                found = 1;
                break;
            } else {
                printf("\nInvalid amount!\n\n");
                return;
            }
        }
    }

    if (!found) {
        printf("\nAccount not found.\n");
    }

    fclose(fp);
}

void withdraw() {
   struct Account a;
    int account, found = 0;
    float amount;

    FILE *fp = fopen(FILE_NAME, "rb+");
    if (!fp) {
        printf("\nFile not found.\n\n");
        return;
    }

    printf("\nEnter account number: ");
    scanf("%d", &account);

    printf("\nEnter amount to withdraw: ");
    scanf("%f", &amount);

    while (fread(&a, sizeof(struct Account), 1, fp)) {
        if (a.acc_num == account) {
            if (a.balance > amount && amount > 0) {
                a.balance -= amount;

                fseek(fp, -sizeof(struct Account), SEEK_CUR);
                fwrite(&a, sizeof(struct Account), 1, fp);

                printf("\nWithdrawal successful. New balance: %.2f\n", a.balance);
                Current_time();
            } else {
                printf("\nInvalid amount!\n\n");
                return;
            }
            found = 1;
            break;
        }
    }

    if (a.balance < 5000.00)
        printf("Warning: Your balance is leass than Rs. 5,000\n\n");

    if (!found)
        printf("\nAccount not found.\n\n");

    fclose(fp);
}

void list_accounts () {
    struct Account a;

    FILE *fp = fopen(FILE_NAME, "rb");
    if(!fp) {
        printf("\nRecord not found\n\n");
        return;
    }

    printf("\n\n-------List of Accounts-------\n");

    while (fread(&a, sizeof(struct Account), 1, fp)) {
        printf("%d\t%-15s\t%-15s\t%.2f\n", a.acc_num, a.name, a.acc_type, a.balance);
    }

    printf("\n");

    fclose(fp);
}

void search_account() {
    struct Account a;
    int account, found = 0;

    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("\nFile not found.\n\n");
        return;
    }

    printf("\nEnter account number: ");
    scanf("%d", &account);

    while (fread(&a, sizeof(struct Account), 1, fp)) {
        if (a.acc_num == account) {
            printf("\nRecord found\n\n");
            printf("Account Number: %d\n", a.acc_num);
            printf("Account holder: %s\n", a.name);
            printf("Account Type: %s\n", a.acc_type);
            printf("Balance: %.2f\n\n", a.balance);
            found++;
            break;
        }
    }

    if (!found) 
        printf("\nAccount not found.\n\n");

    fclose(fp);
}