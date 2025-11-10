#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Book{
    int id;
    char title[50];
    char author[50];
    float price;
};
void addbook();
void displaybooks();
void searchbook();
void deletebook();
void updatebook();
int main(){
    int choice;
    while(1){
        printf("\n**************Library Managemnet System**************\n");
        printf("1.Add Book\n");
        printf("2.Display All Books\n");
        printf("3.Search Book\n");
        printf("4.Delete Book\n");
        printf("5.Update book\n");
        printf("6.Exit\n");
        printf("Enter Your choice:");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                addbook();
                break;
            case 2:
                displaybooks();
                break;
            case 3:
                searchbook();
                break;
            case 4:
                deletebook();
                break;
            case 5:
                updatebook();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid Choice! Try again.\n");
        }
    }
}
void addbook(){
    struct Book b1;
    FILE *fp;
    fp=fopen("library.txt","a");
    if(fp==NULL){
        printf("Error in opening file!\n");
        return;
    }
    printf("Enter book ID:");
    scanf("%d",&b1.id);
    getchar();
    printf("Enter book title:");
    fgets(b1.title,sizeof(b1.title),stdin);
    b1.title[strcspn(b1.title,"\n")]='\0';
    printf("Enter author name:");
    fgets(b1.author,sizeof(b1.author),stdin);
    b1.author[strcspn(b1.author,"\n")]='\0';
    printf("Enter price of the book:");
    scanf("%f",&b1.price);
    fprintf(fp,"%d,%s,%s,%.2f\n",b1.id,b1.title,b1.author,b1.price);
    fclose(fp);
    printf("Book added successfuly.\n");
}
void displaybooks() {
    struct Book b1;
    FILE *fp = fopen("library.txt", "r");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n%-5s %-25s %-25s %-10s\n", "ID", "Title", "Author", "Price");
    printf("---------------------------------------------------------------\n");

    while (fscanf(fp, "%d,%49[^,],%49[^,],%f", &b1.id, b1.title, b1.author, &b1.price) == 4) {
        printf("%-5d %-25s %-25s %-10.2f\n", b1.id, b1.title, b1.author, b1.price);
    }
    printf("---------------------------------------------------------------\n");
    fclose(fp);
}
void searchbook() {
    int id, found = 0;
    struct Book b1;
    FILE *fp = fopen("library.txt", "r");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter book ID to search: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d,%49[^,],%49[^,],%f\n", &b1.id, b1.title, b1.author, &b1.price) != EOF) {
        if (b1.id == id) {
            printf("\nBook Found!\n");
            printf("ID: %d\nTitle: %s\nAuthor: %s\nPrice: %.2f\n", b1.id, b1.title, b1.author, b1.price);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Book not found.\n");

    fclose(fp);
}
void deletebook() {
    int id, found = 0;
    struct Book b1;
    FILE *fp = fopen("library.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter book ID to delete: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d,%49[^,],%49[^,],%f\n", &b1.id, b1.title, b1.author, &b1.price) != EOF) {
        if (b1.id != id)
            fprintf(temp, "%d,%s,%s,%.2f\n", b1.id, b1.title, b1.author, b1.price);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (found)
        printf("Book deleted successfully.\n");
    else
        printf("Book ID not found.\n");
}
void updatebook() {
    int id, found = 0;
    struct Book b1;
    FILE *fp = fopen("library.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter book ID to update: ");
    scanf("%d", &id);
    getchar();
    while (fscanf(fp, "%d,%49[^,],%49[^,],%f", &b1.id, b1.title, b1.author, &b1.price) == 4) {
        if (b1.id == id) {
            found = 1;
            printf("Enter new title: ");
            fgets(b1.title, sizeof(b1.title), stdin);
            b1.title[strcspn(b1.title, "\n")] = '\0';
            printf("Enter new author: ");
            fgets(b1.author, sizeof(b1.author), stdin);
            b1.author[strcspn(b1.author, "\n")] = '\0';
            printf("Enter new price: ");
            scanf("%f", &b1.price);
        }
        fprintf(temp, "%d,%s,%s,%.2f\n", b1.id, b1.title, b1.author, b1.price);
    }
    fclose(fp);
    fclose(temp);
    remove("library.txt");
    rename("temp.txt", "library.txt");
    if (found)
        printf("Book updated successfully.\n");
    else
        printf("Book ID not found.\n");
}