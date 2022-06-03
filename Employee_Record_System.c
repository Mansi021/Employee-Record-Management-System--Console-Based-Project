#include<stdio.h>        // for printf and scanf function
#include<stdlib.h>       //for exit function and system("cls") function
#include<conio.h>
#include<string.h>       // string operations

void horizontal_spaces(int n);     //Declaration of the function named horizontal_spaces
void vertical_spaces(int n);       //Declaration of the function named vertical_spaces

int main()                   //Starting of the main function
{
    FILE *fp, *ft;           // file pointers to access the file
    char another, choice;

    /* structure to represent the details of the employee*/
    struct emp
    {
        char name[40];    // name of the employee
        int age;          //  age of the employee
        float bs;         // basic salary of each employee
    };

    struct emp e;         // structure variable of the structure named emp

    char empname[40];     // character array to store the name of the employee whose data is to be modified

    long int recsize;     // size of each employee of the structure emp

    /* open file in read and write mode ,i.e r+ mode
    and if the file EMP.txt already exists, then open it in read write mode
     if the file does not exit it simply create a new copy
    */
    fp = fopen("EMP.txt","r+");
    if(fp == NULL)
    {
        fp = fopen("EMP.txt","w+");
        if(fp == NULL)
        {
            printf("Cannot open file");
            exit(1);
        }
    }

    // size of each record i.e. size of structure variable e
    recsize = sizeof(e);

    // infinite loop continues until the break statement encounter
    while(!0)             // here the condition is that till 1 is true the loop will execute(which is always true,that's why it is an infinite loop)
    {
        system("cls"); //clear the console
        vertical_spaces(2);
        horizontal_spaces(4);
        printf("------EMPLOYEE RECORD SYSTEM------\n");
        vertical_spaces(4);
        horizontal_spaces(5);
        printf("1. Add any new Record \n"); // to add any record
        vertical_spaces(2);
        horizontal_spaces(5);
        printf("2. List of all the Records \n"); // option for showing existing record
        vertical_spaces(2);
        horizontal_spaces(5);
        printf("3. Modify any Record \n"); // option for editing any record
        vertical_spaces(2);
        horizontal_spaces(5);
        printf("4. Delete any Record \n"); // option for deleting any record
        vertical_spaces(2);
        horizontal_spaces(5);
        printf("5. Exit the program \n"); // exit from the program by using the exit function
        vertical_spaces(2);
        horizontal_spaces(5);
        printf("Your Choice: "); // enter the digit between 1 to 5
        fflush(stdin); // flush the input buffer
        choice  = getchar(); // to get the input
        switch(choice)
        {
        case '1':  //  if user input 1 then
            system("cls");
            fseek(fp,0,SEEK_END);  //search the file 'fp' and move cursor to end of this file
            // here 0 indicates moving 0 distance from the end of the file

            another = 'y';
            while(another == 'y')  //if user input another record
            {
                vertical_spaces(4);
                printf("\nEnter name: ");
                scanf("%s",e.name);
                vertical_spaces(2);
                printf("\nEnter age: ");
                scanf("%d", &e.age);
                vertical_spaces(2);
                printf("\nEnter basic salary: ");
                scanf("%f", &e.bs);

                fwrite(&e,recsize,1,fp); // write the record in the file
                vertical_spaces(2);
                printf("\nAdd another record(y/n): ");
                fflush(stdin);
                another = getchar();
            }
            break;
        case '2':
            system("cls");
            rewind(fp);  // this moves file cursor to start of the file
            int i=1;
            while(fread(&e,recsize,1,fp)==1)  // read the file and fetch the record one record per fetch
            {
                printf("\nThe details of the employee %d is: ",i); // print the name, age and basic salary
                vertical_spaces(1);
                printf("Name: %s",e.name);
                vertical_spaces(1);
                printf("Age: %d",e.age);
                vertical_spaces(1);
                printf("Basic salary: %.2f",e.bs);
                vertical_spaces(2);
                i++;
            }
            getch();
            break;

        case '3':  // if user press 3 then do editing existing record
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                vertical_spaces(5);
                printf("Enter the employee name to modify: ");
                scanf("%s", empname);
                rewind(fp);
                while(fread(&e,recsize,1,fp)==1)  // fetch all record from file
                {
                    if(strcmp(e.name,empname) == 0)  //if entered name matches with that in file
                    {
                        vertical_spaces(1);
                        printf("\nEnter new name: ");
                        scanf("%s",e.name);
                        printf("\nEnter new age: ");
                        scanf("%d",&e.age);
                        printf("\nEnter new basic salary: ");
                        scanf("%f",&e.bs);
                        fseek(fp,-recsize,SEEK_CUR); // move the cursor 1 step back from current position
                        fwrite(&e,recsize,1,fp); // override the record
                        break;
                    }
                }
                printf("\nModify another record(y/n): ");
                fflush(stdin);
                another = getchar();
            }
            break;
        case '4':
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                vertical_spaces(3);
                printf("\nEnter name of employee to delete: ");
                scanf("%s",empname);
                ft = fopen("Temp.txt","w");  // create a intermediate file for temporary storage
                rewind(fp);                   // move record to starting of file
                while(fread(&e,recsize,1,fp) == 1)   // read all records from file
                {
                    if(strcmp(e.name,empname) != 0)  // if the entered record match
                    {
                        fwrite(&e,recsize,1,ft);    // move all records except the one that is to be deleted to temp file
                    }
                }
                fclose(fp);
                fclose(ft);
                remove("EMP.txt");               // remove the original file
                rename("Temp.txt","EMP.txt");    // rename the temp file to original file name
                fp = fopen("EMP.txt", "r+");
                vertical_spaces(2);
                printf("Delete another record(y/n): ");
                fflush(stdin);
                another = getchar();
            }
            break;
        case '5':
            printf("\n");
            fclose(fp);  // close the file
            exit(0); // exit from the program
        }
    }
    return 0;
}


void horizontal_spaces(int n)
{
    for(int i=0 ; i<n ; i++ )
    {
        printf("\t");
    }
}


void vertical_spaces(int n)
{
    for(int i=0 ; i<n ; i++ )
    {
        printf("\n");
    }
}
