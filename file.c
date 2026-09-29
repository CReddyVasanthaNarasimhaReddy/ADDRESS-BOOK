#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void initialize(AddressBook *addressBook) {
    // Start with empty address book
    addressBook->contactCount = 0;
    
    // Load contacts from file
    loadContactsFromFile(addressBook);
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp = fopen("contacts.txt", "r");
    if(fp == NULL) {
        printf("No saved contacts file found. Starting with empty address book.\n");
        return;
    }
    
    int fileCount;
    if(fscanf(fp, "%d", &fileCount) != 1) {
        printf("Error reading contact count from file.\n");
        fclose(fp);
        return;
    }
    
    if(fileCount < 0 || fileCount > MAX_CONTACTS) {
        printf("Error: Invalid contact count in file (%d).\n", fileCount);
        fclose(fp);
        return;
    }
    
    // Reset contact count to 0 to avoid duplicates
    addressBook->contactCount = 0;
    
    for(int i = 0; i < fileCount && addressBook->contactCount < MAX_CONTACTS; i++) {
        if(fscanf(fp, " %[^\n]", addressBook->contacts[addressBook->contactCount].name) != 1 || 
           fscanf(fp, " %[^\n]", addressBook->contacts[addressBook->contactCount].phone) != 1 ||
           fscanf(fp, " %[^\n]", addressBook->contacts[addressBook->contactCount].email) != 1) {
            printf("Error reading contact #%d from file.\n", i + 1);
            break;
        }
        addressBook->contactCount++;
    }
    
    fclose(fp);
    printf("Loaded %d contacts from file.\n", addressBook->contactCount);
}

void saveContactsToFile(AddressBook *addressBook) {
    FILE *fp = fopen("contacts.txt", "w");
    if(fp == NULL) {
        printf("Error: Unable to open file for saving.\n");
        return;
    }
    
    // Save all contacts
    fprintf(fp, "%d\n", addressBook->contactCount);
    for(int i = 0; i < addressBook->contactCount; i++) {
        fprintf(fp, "%s\n%s\n%s\n", 
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }
    
    fclose(fp);
    printf("Saved %d contacts to 'contacts.txt'.\n", addressBook->contactCount);
}