#ifndef CONTACT_H
/*
 NAME         : C REDDY VASANTHA NARASIMHA REDDY
 BATCH        : 26015B
 DATE         : 29-08-2026
 PROJECT NAME : ADDRESS BOOK

 DISCRIPTION:
 --------------
    The " ADDRESS BOOK " is a C Language based Program. This a Personal Digital Book
to Store basic detailes of a person like " NAME "," PHONE NUMBER "," Email ID ". 
In this we can store upto 100 contacts. This program has a features like menu with options of 

1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit

    By selectig option we can proceed forward based on user selection.Ever option has a EXIT button
to return back to main, if you don't want to proceed forward.

    The System has a feature to Store only unique person detailes. No duplicate contact detailes will be
found or Saved.
*/
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {

    char name[51];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
void saveAndExit(AddressBook *addressBook);

#endif
