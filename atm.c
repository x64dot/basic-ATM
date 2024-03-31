#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void clear();
void menu();
int auth();
void check_balance(int* cardb, int* cash);
void deposit(int* cardb, int* cash);
void withdraw(int* cardb, int* cash);

int main(){
    int* cash_atm = (int*)malloc(sizeof(int));
    int* cash = (int*)malloc(sizeof(int));
    *cash_atm = 1000;
    *cash = 20;
    char input[3];

    if (auth() != 0){
        free(cash_atm);
        free(cash);
        return -1;
    }

    while (1){
        clear();
        menu();
        printf("Pick a option: ");
        fgets(input, 2, stdin);
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (strcmp(input, "1") == 0){
            clear();
            check_balance(cash_atm, cash);
        }
        else if (strcmp(input, "2") == 0){
            clear();
            deposit(cash_atm, cash);

        }
        else if (strcmp(input, "3") == 0){
            clear();
            withdraw(cash_atm, cash);
        }
        else if (strcmp(input, "4") == 0){
            free(cash_atm);
            free(cash);
            clear();
            return 0;
        }
        else{
            puts("Invalid option.");
        }

    }
 
    return 0;
}

void clear(){
    system("clear");
}
void menu(){
    printf(
    "1. Check balance\n"
    "2. Deposit\n"
    "3. Withdraw\n"
    "4. Exit\n");
}

int auth() {
    int attempts = 0;
    char pin[6];

    for (attempts; attempts < 3; attempts++) {
        printf("Enter your 4 digit pin: ");
        fgets(pin, 6, stdin);
        if (strcmp(pin, "4454\n") == 0) {
            pin[strcspn(pin, "\n")] = '\0';
            return 0;
        }
    }

    printf("3 attempts exceeded, quitting!\n");
    return -1;
}



void check_balance(int* cardb, int* cash){
    printf("Card balance: %d\nCash balance: %d", *cardb, *cash);

    while(getchar() != 'q'){
        puts("\nEnter 'q' to go back to main menu.");
    }
}

void deposit(int* cardb, int* cash){
    char input1;
    char input2[6];
    int amount = 0;

    dep:
        printf("Card balance: %d\nCash balance: %d\n", *cardb, *cash);

        printf("Would you like to deposit?(y/n): ");
        input1 = getchar(); 
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (input1 == 'n'){ 
            return;
        }
        else if (input1 != 'y'){ 
            printf("Invalid input. Please enter 'y' or 'n'.\n");
            goto dep; 
        }

        printf("How much cash do you want to deposit? ");
        fgets(input2,5, stdin);

        sscanf(input2, "%d", &amount);


        if (amount <= 0){
            printf("Invalid amount. Please enter a positive integer.\n");
            goto dep;
        }

        if (amount > *cash){
            printf("Not enough cash. Going back to menu...\n");
            fflush(stdout);
            sleep(2);
            return;
        }  

        *cash -= amount;

        *cardb += amount;

        printf("Deposit successful!\n");
        fflush(stdout);
        sleep(2);   
}

void withdraw(int* cardb, int* cash){
    char input1;
    char input2[6];
    int amount = 0;

    dep:
        printf("Card balance: %d\nCash balance: %d\n", *cardb, *cash);

        printf("Would you like to withdraw?(y/n): ");
        input1 = getchar(); 
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (input1 == 'n'){ 
            return;
        }
        else if (input1 != 'y'){ 
            printf("Invalid input. Please enter 'y' or 'n'.\n");
            goto dep; 
        }

        printf("How much cash do you want to withdraw? ");
        fgets(input2,5, stdin);

        sscanf(input2, "%d", &amount);


        if (amount <= 0){
            printf("Invalid amount. Please enter a positive integer.\n");
            goto dep;
        }

        if (amount > *cardb){
            printf("Not enough cash in your card. Going back to menu...\n");
            fflush(stdout);
            sleep(2);
            return;
        }  

        *cardb -= amount;

        *cash += amount;

        printf("Withdraw successful!\n");
        fflush(stdout);
        sleep(2);   
}
