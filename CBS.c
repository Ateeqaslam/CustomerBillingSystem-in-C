#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int registration();
bool agreetopaynow();
int search();
int delete();
int main()
{
    system("cls");
    printf("\nCUSTOMER BILLING SYSTEM\n\n");
    printf("Select Mode:\n");
    printf("1. Register Customer\n2. Search Customer\n3. Delete Customer\nType any other key to exit\n");
    int s;
    scanf("%i", &s);
    switch (s)
    {
    case 1:
        system("cls");
        printf("<<<<<<<<<<Registration form>>>>>>>>>>\n");
        registration();
        break;

    case 2:
        system("cls");
        printf("<<<<<<<<<<Search User>>>>>>>>>>\n");

        search();
        break;
    case 3:
        system("cls");
        delete ();
        break;

    default:
        break;
    }
}

// registration funciton
int registration()
{
    // Register
    char Name[20];
    char P_Number[20];
    char Address[20];
    int payment = 500;

    // registration
    FILE *file;
    file = fopen("DataBase.txt", "a");
    printf("Name: ");
    getchar();
    scanf("%[^\n]s", &Name);
    getchar();
    printf("Phone: ");
    scanf("%[^\n]s", &P_Number);
    getchar();
    printf("City: ");
    scanf("%[^\n]s", &Address);
    getchar();
    printf("Your annual plan is activated!\nDO YOU WANT TO PAY NOW? y ,no\n");
    // y n checking
    if (agreetopaynow()) // if said yes
    {
        int paid = 0; // how much he is paying

        printf("Watch out We don't refund\n"); // alert
        printf("Total plan cost $500\nPay us: ");
        scanf("%i", &paid); // get payment
        if (paid < payment) // if paid less than plan
        {
            printf("Not enough balance\n");
            printf("Registration failed!!!\n");
            return 1;
        }    // payment checking
        else // paid more or plan
        {
            printf("Plan purchased\n");
            // write to file
            fprintf(file, "Name: %s\n  Phone: %s\n  Address: %s\n  Plan: Puchased\n\n", Name, P_Number, Address);
            fclose(file);
            // Successful message
            printf("Registration successful\n");
        } // payment checking
    }     // y n checking
    else  // everything except yes
    {
        printf("Registration failed!!!\n");
        return 1;
    }             // y n checking
    fclose(file); // Memory safety
}

// agreetopaynow fucntion
bool agreetopaynow()
{
    char list[4][5] = {
        "y",
        "Y",
        "yes",
        "YES",
    };         // yes agreement user mostly type
    char *str; // user input
    scanf("%s", str);
    for (int i = 0; i < 4; i++) // loop through list
    {
        if (strcmp(list[i], str) == 0) // compare list with user input
        {
            return true; // ifmatched
        }
    }

    return false; // not match
}

// Search Function
int search()
{
    int line_size = 50; // line size
    char buffer[line_size];

    char name[10]; // to searc in file
    printf("First Name: ");
    getchar();
    scanf("%[^\n]", name);
    FILE *file = fopen("DataBase.txt", "r");
    while (!feof(file)) // if not end of file
    {
        fgets(buffer, line_size, file); // read file by 50 char
        if (strstr(buffer, name))       // check equallity in each line
        {
            system("cls");
            printf("%s", buffer);       // print name
            for (int i = 0; i < 3; i++) // loop through 3 more line
            {
                fgets(buffer, line_size, file); // get line
                printf("%s", buffer);           // print it
            }
            break; // perform if() then break the while loop
        }
    };
    if (feof(file)) // if reached end of line
    {
        system("cls");
        printf("No Customer yet!\n");
    }

    fclose(file); // memory safety
}

// Delete function
int delete()
{
    int line_size = 50;     // line size
    char buffer[line_size]; //  store line in RAM

    char name[10]; // to delete in file
    printf("First Name: ");
    getchar(); // capture the \n which is still store in buffer
    scanf("%[^\n]", name);
    FILE *file = fopen("DataBase.txt", "r"); // read DataBase file
    if (file == NULL)                        // if not create yet
    {
        printf("NO CUSTOMER FOUND\n");
        return 1;
    }

    FILE *file2 = fopen("DataBase2.txt", "w"); // second file to store the rest
    while (!feof(file))
    {
        fgets(buffer, line_size, file);
        if (strstr(buffer, name)) // if the name equal
        {

            for (int i = 0; i < 4; i++) // move the fgets 4 line ahead
            {
                fgets(buffer, line_size, file);
            }
        }
        else // then save the rest in new file
        {
            fputs(buffer, file2); // copy buffer to file2
        }
    }
    fclose(file);                    // Memory safety
    fclose(file2);                   // Memory safety
    if (remove("DataBase.txt") == 0) // if file1 got remove
    {
        rename("DataBase2.txt", "DataBase.txt"); //  rename file2 as file1
        printf("deleted succesfully\n");
        return 1;
    }
    printf("deletion failed\n");
}
