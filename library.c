#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
struct student tempS;
struct books{
    int id;
    char bookName[50];
    char authorName[50];
    char date[15];
    
    
    }b;
    struct student{
        int id;
        char sName[50];
        char sClass[50];
        int sRoll;
        char bookName[50];
        char date[15];

    }s;

FILE *fp;


int main(){
    
    int ch;
    while(1)
    {
         system("cls");
         printf("<===============Library Management System===============>\n");
         printf("1.Add Book\n");
         printf("2.View Books\n");
         printf("3.Remove Book\n");
         printf("4.Issue Book\n");
         printf("5.Search Book\n");
         printf("6.Submit Book\n");
         printf("7.View Issued  Book\n");
         printf("8. Exit\n");
         printf("<===============xxxxxxxxxxxxxxxxxxxxxxxxxx===============>\n");

         printf("Enter Your Choice: ");
         scanf("%d",&ch);



         switch(ch)
         {
            case 1: addBook(); break;
            case 2: viewBook(); break;
            case 3: removeBook(); break;
            case 4: issueBook(); break;
            case 5: searchBook(); break;
            case 6: submitBook(); break;
            case 7: issueList(); break;
            case 8: exit(0);break;
            default:printf("\nInvalid Choice...\n");
         }
         printf("\nPress any Key to Continue...");
         getch();


    }

    return 0;
}


void addBook()
{
    char myDate[15];
    time_t t=time(NULL);

    struct tm tm = *localtime(&t);
   
    sprintf(myDate,"%02d/%02d/%d",tm.tm_mday,tm.tm_mon+1,tm.tm_year +1900);
    strcpy(b.date,myDate);



    fp=fopen("books.txt","ab");
    printf("Enter Book Id: ");
    scanf("%d",&b.id);

    printf("Enter Book Name: ");
    fflush(stdin);
    gets(b.bookName);
    printf("Enter Author Name: ");
    fflush(stdin);
    gets(b.authorName);
    
    printf("Books Added Successfully: \n");
    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);

}
void viewBook(){

    system("cls");
    printf("<===============Available Books===============>\n\n");
    printf("%-10s %-30s %-20s %s\n\n", "Book id", "Book Name", "Author", "Date");

    fp = fopen("books.txt", "rb");
    while(fread(&b, sizeof(b), 1, fp) == 1){
        printf("%-10d %-30s %-20s %s\n", b.id, b.bookName, b.authorName, b.date);
    }

    fclose(fp);
}

void removeBook(){
    int id, f=0;
    system("cls");
      printf("<===============Remove Books===============>\n\n");
    printf("Enter Book id to remove: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("books.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while(fread(&b, sizeof(b), 1, fp) == 1){
        if(id == b.id){
            f=1;
        }else{
            fwrite(&b, sizeof(b), 1, ft);
        }
    }

    if(f==1){
        printf("\n\nDeleted Successfully...");
    }else{
        printf("\n\nRecord Not Found !");
    }

    fclose(fp);
    fclose(ft);

    remove("books.txt");
    rename("temp.txt", "books.txt");

}

void issueBook(){

    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(s.date, myDate);

    int f=0;

    system("cls");
    printf("<== Issue Books ==>\n\n");

    printf("Enter Book id to issue: ");
    scanf("%d", &s.id);

    //Check if we have book of given id
    fp = fopen("books.txt", "rb");

    while(fread(&b, sizeof(b), 1, fp) == 1){
        if(b.id == s.id){
            strcpy(s.bookName, b.bookName);
            f=1;
            break;
        }
    }

    if(f==0){
        printf("No book found with this id\n");
        printf("Please try again...\n\n");
        return;
    }

    fp = fopen("issue.txt", "ab");

    printf("Enter Student Name: ");
    fflush(stdin);
    gets(s.sName);

    printf("Enter Student Class: ");
    fflush(stdin);
    gets(s.sClass);

    printf("Enter Student Roll: ");
    scanf("%d", &s.sRoll);

    printf("Book Issued Successfully\n\n");

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
}


void submitBook() {
    int bookId;
    int found = 0;

    system("cls");
    printf("<===============Submit Book===============>\n\n");

    printf("Enter Book ID to submit: ");
    scanf("%d", &bookId);

    FILE *issuedFile, *tempFile;


    issuedFile = fopen("issue.txt", "rb");
    if (issuedFile == NULL) {
        printf("Error opening issued book file.\n");
        return;
    }

    
    tempFile = fopen("temp_issue.txt", "wb");
    if (tempFile == NULL) {
        printf("Error opening temporary file.\n");
        fclose(issuedFile);
        return;
    }

    while (fread(&s, sizeof(s), 1, issuedFile) == 1) {
    
        if (s.id == bookId) {
            found = 1;
            printf("\nBook with ID %d has been submitted by %s\n", bookId, s.sName);
        } else {
          
            fwrite(&s, sizeof(s), 1, tempFile);
        }
    }


    fclose(issuedFile);
    fclose(tempFile);


    if (!found) {
        printf("\nBook with ID %d is not currently issued.\n", bookId);
        remove("temp_issue.txt");
        return;
    }

   
    remove("issue.txt");
    rename("temp_issue.txt", "issue.txt");
}



void issueList(){
    system("cls");
   printf("<===============Book Issued List===============>\n\n");

    printf("%-10s %-30s %-20s %-10s %-30s %s\n\n", "S.id", "Name", "Class", "Roll", "Book Name", "Date");

    fp = fopen("issue.txt", "rb");
    while(fread(&s, sizeof(s), 1, fp) == 1){
        printf("%-10d %-30s %-20s %-10d %-30s %s\n", s.id, s.sName, s.sClass, s.sRoll, s.bookName, s.date);
    }

    fclose(fp);
}
void searchBook() {
    char searchName[50];
    int found = 0;

    system("cls");
    printf("<=======================Search Book=======================>\n\n");

    printf("Enter Book Name to search: ");
    fflush(stdin);
    gets(searchName);

    // Convert the search name to lowercase for case-insensitive comparison
    char lowercaseSearchName[50];
    strcpy(lowercaseSearchName, searchName);
    for (int i = 0; lowercaseSearchName[i]; i++) {
        lowercaseSearchName[i] = tolower(lowercaseSearchName[i]);
    }

    fp = fopen("books.txt", "rb");

    while (fread(&b, sizeof(b), 1, fp) == 1) {
        // Convert the current book name to lowercase for case-insensitive comparison
        char bookName[50];
        strcpy(bookName, b.bookName);
        for (int i = 0; bookName[i]; i++) {
            bookName[i] = tolower(bookName[i]);
        }

        // Check if the search name is a substring of the book name
        if (strstr(bookName, lowercaseSearchName) != NULL) {
            found = 1;
            printf("\nBook Found!\n");
            printf("%-10s %-30s %-20s %s\n", "Book id", "Book Name", "Author", "Date");
            printf("%-10d %-30s %-20s %s\n", b.id, b.bookName, b.authorName, b.date);
        }
    }

    fclose(fp);

    if (!found) {
        printf("\nBook with name \"%s\" not found.\n", searchName);
    }
}