#include <stdio.h>
#include<string.h>
#include "contact.h"

int main() {
    int choice=0,exit=0;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book
// Displaying the menu to user
    do {
        printf("\n\n===============   ADDRESS BOOK MENU : ===================\n\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%1d", &choice);
        getchar();
        
        switch (choice) {
            case 1:// Creating contact
                createContact(&addressBook);
                break;
            case 2:// Search contact
                searchContact(&addressBook);
                break;
            case 3:// Edit contact
                editContact(&addressBook);
                break;
            case 4:// Delete contact
                deleteContact(&addressBook);
                break;
            case 5:
                printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("4. Exit\n");
                printf("Enter your choice: ");
                int sortChoice;
                scanf("%d", &sortChoice);
                if(sortChoice==4)
                {
                    break;
                }
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                char ans[2]; 
                printf("Confirm to exit (y/n) : ");
                scanf("%s",ans);
                getchar();
                if(ans[0]=='Y'|| ans[0]=='y')
                {
                    saveContactsToFile(&addressBook);
                    exit=1;
                    break;
                }
                else
                {
                    printf("Exit cancilled...\n");
                    break;
                }
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6 || exit != 1);
    
       return 0;
}
