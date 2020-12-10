//WIP - Jazz
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int user_count(void);
int credit_check(int user);
int add_user(void);
int remove_user(void);

int server(int user_ID, char pwd[30])
{
    FILE *infile;

    if ((infile = fopen("clients.txt", "r")) == NULL) {
        puts("File could not be accessed");
    }
    else 
    {
        int ID;
        char password[30];
        char first[30];
        char last[30];
        double credit;

        int user_found = 0;

        double time=0;

        fscanf(infile,"%d%29s%29s%29s%lf", &ID, first, last, password, &credit);

        while(!feof(infile) ){
            if (ID == user_ID){
                user_found = 1;
                if (strcmp(password, pwd) == 0) {
                    if (credit == 0) {
                        printf("Sorry, %s %s! You have no credit remaining in your account.\n", first, last);
                    }
                    else {
                        printf("\nHello, %s %s! You are now in the system.\n", first, last);
                        printf("Your Current Credit is $%.2f\n", credit);
                        time = credit/5.0;
                        printf("You have %.1f hours on the system.\n", time);
                    }
                }
                else {
                    puts("Sorry, you have input an incorrect password. Please try logging in again.\n");
                    return 1;
                }
            }
            fscanf(infile,"%d%29s%29s%29s%lf", &ID, first, last, password, &credit);
        }
        if (user_found == 0) {
            puts("Hmmm, seems like you don't have an account with us.\nLet's make an account for you!\n");
            add_user();
        }
        fclose(infile); 
    }
    return 0;
}


int admin(char apwd[30]) {
    if (strcmp(apwd, "password")!=0) {
        puts("Sorry, wrong password! Restart system to login as administrator");
    }
    
    else {
        char action=' ';
    
        puts("Actions: \nUser count = 'u'\nCredit for user = 'c'\nAdd user = 'a'\nRemove user = 'r'\nExit = 'x'");
    
        while (action != 'x') {
            printf("What action would you like to perform: ");
            scanf("%s", &action);
            action = tolower(action);
            switch(action) {
                case 'u':
                    user_count();
                    break;
                case 'c':
                    printf("Please enter ID to check credit amount: ");
                    scanf("%d", &user);
                    credit_check(user);
                    break;
                case 'a':
                    add_user();
                    break;
                case 'r':
                    //remove_user();
                    break;
                case 'x':
                    break;
                default:
                    puts("Invalid input.");
                    break;
            }
        }
        puts("Thank you for using our system today! Goodbye.");
    }
}

int user_count(void) {
    FILE *infile;
    int count = 0;
    char c;

    if ((infile = fopen("clients.txt", "r")) == NULL) {
        puts("File could not be accessed");
    }
    else {
        for (c=getc(infile); c != EOF; c=getc(infile)) {
            if (c=='\n')
                count += 1;
        }
    }
    fclose(infile);
    printf("There are %d users in the system.\n", count);
}

int credit_check(int user) {
    FILE *infile;
    int count = 0;

    if ((infile = fopen("clients.txt", "r")) == NULL) {
        puts("File could not be accessed");
    }
    else {
        int ID;
        char password[30];
        char first[30];
        char last[30];
        double credit;

        fscanf(infile,"%d%29s%29s%29s%lf", &ID, first, last, password, &credit);
 
        while(!feof(infile) ){
            if (ID == user) {
                printf("User %d has the remaining credit: $%.2f\n", ID, credit);
                break;
            }
            else {
                printf("No user found with ID %d.\n", user);
                break;
            }
        }
        fclose(infile);
    }
}

int add_user(void) {
    FILE *infile;
    
    if ((infile = fopen("clients.txt", "a")) == NULL) {
        puts("File could not be accessed");
    }
    else {
        int ID;
        char password[30];
        char first[30];
        char last[30];
        double credit;
        
        int newID;
        char pass[30];
        char name1[30];
        char name2[30];
        double init_cred;
        
        printf("Enter the User ID, First name, Last name, Password, and starting credit for the account you would like to create: ");
        scanf("%d%s%s%s%lf", &newID, name1, name2, pass, &init_cred);
        /* This is to test if the user exists in the system already, but it doesn't work
        fscanf(infile,"%d%29s%29s%29s%lf", &ID, first, last, password, &credit);
        
        if (strcmp(first, name1)==0) {
            if (strcmp(last, name2)==0) {
                printf("Sorry, an account for %s %s already exists!", first, last);
            }
        }
        else {
            fprintf(infile, "%d %s %s %s %.2lf\n", newID, name1, name2, pass, init_cred);
            printf("Welcome to our server, %s %s!\n", name1, name2);
        }
        */
        fprintf(infile, "%d %s %s %s %.2lf\n", newID, name1, name2, pass, init_cred);
        printf("Welcome to our server, %s %s!\n", name1, name2);   
    }
    fclose(infile);   
}

/* Will probably get scrapped we don't have time 
int remove_user(void) {
    FILE *infile, *outfile;
    
    if ((infile = fopen("clients.txt", "r")) == NULL) {
        puts("File could not be accessed");
    }
    else {
        int ID;
        char password[30];
        char first[30];
        char last[30];
        double credit;
        int user;
        char line;

        fscanf(infile,"%d%29s%29s%29s%lf", &ID, first, last, password, &credit);
        
        rewind(infile);
        
        printf("Enter a user ID to remove: ");
        scanf("%d", &user);
        
        printf("Working on removing %d...\n", user);
        
        outfile = fopen("clients_replica.txt", "w");
        line = getc(infile);
        
        while(line != EOF){
            if (ID != user) {
                fprintf(outfile, "%d", line);
            }
        }
        fclose(outfile);
        remove("clients.txt");
        rename("clients_replica.txt", "clients.txt");
    }
    fclose(infile);
}
*/
