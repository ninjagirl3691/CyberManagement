#include <stdio.h>
#include <string.h>


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

        fscanf(infile,"%d%29s%29s%29s%lf", &ID, first, last, password, &credit);

        while(!feof(infile) ){
            if (ID == user_ID & (strcmp(password, pwd) == 0)) {
                user_found = 1;
                if (credit == 0) {
                    puts("You have no credit remaining in your account.");
                }
                else {
                    printf("Hello, %s %s! You are now in the system.\n", first, last);
                    printf("Your Current Credit is $%.2f\n", credit);
                }
            }
            fscanf(infile,"%d%29s%29s%29s%lf", &ID, first, last, password, &credit);
        }
        if (user_found == 0) {
            puts("Sorry, unfortunately you do not have an account with us.");
        }
        fclose(infile); 
    }
}

int main(void)
{
    int user_ID;
    char pwd[30];
    printf("Enter your account ID number: ");
    scanf("%d", &user_ID);
    printf("Enter your password: ");
    scanf("%s", pwd);
    
    server(user_ID, pwd);






/*Working code for reading and printing out file line by line*/

// int main(void)
// {
//     FILE *infile;

//     if ((infile = fopen("clients.txt", "r")) == NULL) {
//         puts("File could not be accessed");
//     }
//     else {
//         int ID;
//         char password[30];
//         char first[30];
//         char last[30];
//         double credit;

//         // Test, seeing if I can write out all the values in client record
//         fscanf(infile,"%d%29s%29s%29s%lf", &ID, first, last, password, &credit);

//         while(!feof(infile) ){
//             printf("%-10d%-13s%-13s%-13s%7.2f\n", ID, first, last, password, credit);
//             fscanf(infile,"%d%29s%29s%29s%lf", &ID, first, last, password, &credit);
//         }
//         fclose(infile); 
//     }
// }
