#ifndef FUNCTION_H
#define FUNCTION_H

#define FILE_NAME "accounts.dat"

struct Account {
    int acc_num;
    char name[50];
    char acc_type[15];
    float balance;
};


int account_check(int account);
void Current_time(void);
void create_account(void);
void deposit(void);
void withdraw(void);
void list_accounts(void);
void search_account(void);

#endif