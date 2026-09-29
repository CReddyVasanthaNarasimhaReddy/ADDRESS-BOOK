#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    if(addressBook->contactCount == 0)
    {
        printf("\nNo contacts found.\n");
        return;
    }
    
    // Create a temporary array for sorting
    Contact temp[MAX_CONTACTS];
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        temp[i] = addressBook->contacts[i];
    }
    
    // Bubble sort based on criteria
    for(int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for(int j = i + 1; j < addressBook->contactCount; j++)
        {
            int should_swap = 0;
            
            switch(sortCriteria)
            {
                case 1: // Sort by name
                    if(strcmp(temp[i].name, temp[j].name) > 0)
                        should_swap = 1;
                    break;
                case 2: // Sort by phone
                    if(strcmp(temp[i].phone, temp[j].phone) > 0)
                        should_swap = 1;
                    break;
                case 3: // Sort by email
                    if(strcmp(temp[i].email, temp[j].email) > 0)
                        should_swap = 1;
                    break;
                default:
                    should_swap = 0;
            }
            
            if(should_swap)
            {
                Contact swap = temp[i];
                temp[i] = temp[j];
                temp[j] = swap;
            }
        }
    }
    
    // Display sorted contacts
    printf("\n========================================================================================================================\n");
    printf("%-5s %-30s %-15s %-30s\n", "S.No", "Name", "Phone", "Email");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-5d %-30s %-15s %-30s\n", i + 1,temp[i].name,temp[i].phone,temp[i].email);
        }
    printf("========================================================================================================================\n");
    return;
}
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook);
    printf("Saving and Exiting...\n"); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    if(addressBook -> contactCount >= MAX_CONTACTS)
    {
        printf("\nStorage limit Exicedes.....\n");
        return;
    }

    // Name validation

    int flag=1;
    char temp_name[60];
    char temp_phone[20];
    char temp_email[50];
        for(int i=0;i<3;i++)
        {
            printf("------------------\nEnter Name : ");
            scanf(" %[^\n]",temp_name);
            //Chack no.of characters in name
            if(strlen(temp_name)<=3)
            {
                printf("ERROR : Name must contain at least 4 characters..\n");
                continue;
            }
            if(strlen(temp_name)>50)
            {
                printf("ERROR : Invalid Input (Name should be less than 50 characters)!!\n");
                continue;
            }
            // Check is name contine only alphabits.
            int char_flag=0;
            for(int a=0;temp_name[a]!='\0';a++)
            {
                char_flag=1;
                if((temp_name[a] >='A' &&  temp_name[a] <='Z')|| (temp_name[a]==' ') || (temp_name[a] >='a' &&  temp_name[a] <='z') )
                {
                    char_flag=0;
                }
                if(char_flag==1)
                {
                    printf("ERROR : Name should contain only alphabets..\n");
                    break;
                }
            }
            if(char_flag==0)
            {
                flag=0;
                break;
            }
        }
        if(flag==1)
        {   printf("Pleae Try Again..\n");
            return;
        }

        // Phone number validation

        flag=1;
        for(int i=0;i<3;i++)
        {
            printf("-----------------\nEnter Phone Number : ");
            scanf(" %[^\n]",temp_phone);
            // Check no.of characters in phone number.
            if(strlen(temp_phone)!=10)
            {
                printf("ERROR : Invalid Input (Phone number contain only 10 numbers)!!\n");
                continue;
            }
            if(temp_phone[0] < '6' || temp_phone[0] >'9')
            {
                printf("ERROR : First digit must be between 6 To 9..\n");
                continue;
            }
            int count=0;
            for(int i=0;temp_phone[i]!='\0';i++)
            {
                if(temp_phone[i]>='0'&& temp_phone[i]<='9')
                {
                    count++;
                }
            }
            if(strlen(temp_phone)!= count)
            {
                printf("ERROR : Invalid Input (Phone number must contain numbers only)!!\n");
                continue;
            }
            // Checking is there any duplicate is exsting or not..
            int duplicate=0;
            for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if(strcmp(addressBook->contacts[i].phone, temp_phone) == 0)
                    {
                    printf(" ERROR : Phone number is already Exist..\n");
                    duplicate=1;
                    break;
                }
            }
            if(duplicate==1)
            {
                continue;
            }
            flag=0;
            break;
        }
        if(flag==1)
        {   printf("Pleae Try Again..\n");
            return;
        }

        // gmail validation

        flag=1;
        for(int j=0; j<3; j++)
        {
            printf("--------------------------------\nEnter email Addresss : ");
            scanf(" %[^\n]", temp_email);
            
            if(strlen(temp_email) > 50 || strlen(temp_email) <= 0)
            {
                printf("ERROR: Email must be between 1-50 characters.\n");
                continue;
            }
            
            // Check first 3 characters are letters
            int first3_valid = 1;
            for(int i=0; i<3 && temp_email[i]!='\0'; i++)
            {
                if(!(temp_email[i] >= 'a' && temp_email[i] <= 'z'))
                {
                    first3_valid = 0;
                    break;
                }
            }
            if(!first3_valid)
            {
                printf("First 3 characters of email must be lowercase letters only...\n");
                continue;
            }
            
            // Validate email - collect data first
            int at_pos = -1, dot_pos = -1;
            int at_count = 0, dot_count = 0;
            int valid = 1;
            
            for(int i=0; temp_email[i]!='\0'; i++)
            {
                char ch = temp_email[i];
                if(!((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || ch == '@' || ch == '.' ||ch == '_'))
                {
                    valid = 0;
                    printf("ERROR: Invalid character in email.\n");
                    break;
                }
                
                if(ch == '@')
                {
                    at_count++;
                    at_pos = i;
                }
                else if(ch == '.')
                {
                    dot_count++;
                    dot_pos = i;
                }
            }
            if(!valid)
                continue;
            if(at_count == 0 || dot_count == 0)
            {
                printf("ERROR: Email must contain @ and .\n");
                continue;
            }
            
            // Check only one @ and .
            if(at_count > 1 || dot_count > 1)
            {
                printf("ERROR: Email must contain only one @ and .\n");
                continue;
            }
            
            // Check @ before . with at least one character between
            if(at_pos > dot_pos || dot_pos - at_pos <= 1)
            {
                printf("ERROR: '.' must come after '@' with at least one character between.\n");
                continue;
            }
            int domain_len = 0;
            for(int i = dot_pos + 1; temp_email[i] != '\0'; i++)
                domain_len++;
            
            if(domain_len == 4 )
            {
                printf("ERROR: After '.com' no extra characters should be present..\n");
                continue;
            }
            
            // Check duplicate
            int duplicate = 0;
            for(int i=0; i<addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].email, temp_email) == 0)
                {
                    printf("ERROR: Email already exists.\n");
                    duplicate = 1;
                    break;
                }
            }
            if(duplicate)
                continue;
            
            flag = 0;
            break;
        }

        if(flag == 1)
        {
            printf("Please Try Again.\n");
            return;
        }
    // Coplying names into structure
    strcpy(addressBook->contacts[addressBook -> contactCount].name,temp_name);
    strcpy(addressBook->contacts[addressBook -> contactCount].phone,temp_phone);
    strcpy(addressBook->contacts[addressBook -> contactCount].email,temp_email);
    addressBook -> contactCount++;
    printf("\nContact Saved Sucessfully.....\n");
    return;
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int op,flag=0;
    int c=1;
    char exit[2];
    char EXIT[2]={"Y"};
    char search_phone[11];
    char search_name[50],search_email[50];
    printf("Select Search criteria:\n");
    printf("1. Search by name\n");
    printf("2. search by phone\n");
    printf("3. search by email\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d",&op);
    getchar();
    // List of contacts disply based on the user defined choise.
    switch(op)
    {
        case 1 :
        {
            printf("Enter Name : ");
            scanf(" %[^\n]",search_name);
            printf("\n========================================================================================================================\n");
            printf("%-5s %-30s %-15s %-30s\n", "S.No", "Name", "Phone", "Email");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
    
            for(int i=0;i<addressBook -> contactCount;i++)
            {
                if(strcasestr(addressBook->contacts[i].name, search_name) != NULL)
                {
                    flag=1;
                    printf("%-5d%-30s %-15s %-30s\n",c,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    c++;
                }
            }
            if(flag==0)
                {
                    printf("\nNo Contact Found...\n");
                    return;
                }
        }break;
        case 2:
        {
            printf("Enter Phone : ");
            scanf(" %[^\n]",search_phone);
            printf("\n========================================================================================================================\n");
            printf("%-5s %-30s %-15s %-30s\n", "S.No", "Name", "Phone", "Email");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
    
            for(int i=0;i<addressBook -> contactCount;i++)
            {
                if(strcasestr(addressBook->contacts[i].phone, search_phone) != 0)
                {
                    flag=1;
                    printf("%-30s %-15s %-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
            }
            if(flag==0)
                {
                    printf("\nNo Contact Found...\n");
                    return;
                }
        }break;
        case 3:
        {
            printf("Enter Email : ");
            scanf(" %[^\n]",search_email);
            printf("\n========================================================================================================================\n");
            printf("%-5s %-30s %-15s %-30s\n", "S.No", "Name", "Phone", "Email");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
    
            for(int i=0;i<addressBook -> contactCount;i++)
            {
                if(strcasestr(addressBook->contacts[i].email, search_email) != 0)
                {
                    flag=1;
                    printf("%-30s %-15s %-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
            }
            if(flag==0)
                {
                    printf("\nNo Contact Found...\n");
                    return;
                }
        }break;
        // Exit from search contact.
        case 4 : printf("Conform to Exit (y/n) : ");
                scanf(" %s",exit);
                if(strcasestr(EXIT,exit)!=0)
                {
                    return;
                }
        default : printf(" Invalid Selection...\n");
            break;
    }

}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int op,count=0,c_flag=0;
    int index,j=0,arr[100]={0};
    char edit_phone[11],exit[2];
    char edit_name[50],edit_email[50];
    char EXIT[2]={"Y"};
    printf("Select Search criteria:\n");
    printf("1. Edit by Name\n");
    printf("2. Edit by Phone\n");
    printf("3. Edit by Email\n");
    printf("4. Edit All Detiles\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d",&op);
    getchar();
    // Displaying the list of contacts to user for edit.
    switch(op)
    {
        case 1 :
            {
                printf("Enter Name : ");
                scanf(" %[^\n]",edit_name);
                printf("\n========================================================================================================================\n");
                printf("%-5s %-30s %-15s %-30s\n", "S.No", "Name", "Phone", "Email");
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                for(int i=0;i<addressBook -> contactCount;i++)
                {
                    if(strcasestr(addressBook->contacts[i].name, edit_name) != NULL)
                    {
                        c_flag=1;
                        printf("%d.%-30s %-15s %-30s\n",j+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        arr[j]=i;
                        count++;
                        j++;
                    }
                }
                if(c_flag==0)
                    {
                        printf("\nNo Contact Found...\n");
                        return;
                    }
            }break;
            case 2:
            {
                printf("Enter Phone : ");
                scanf(" %[^\n]",edit_phone);
                 printf("\n========================================================================================================================\n");
                printf("%-5s %-30s %-15s %-30s\n", "S.No", "Name", "Phone", "Email");
                printf("------------------------------------------------------------------------------------------------------------------------\n");
    
                for(int i=0;i<addressBook -> contactCount;i++)
                {
                    if(strcasestr(addressBook->contacts[i].phone, edit_phone) != 0)
                    {
                        c_flag=1;
                        printf("%d.%-30s %-15s %-30s\n",j+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        arr[j]=i;
                        count++;
                        j++;
                    }
                }
                if(c_flag==0)
                    {
                        printf("\nNo Contact Found...\n");
                        return;
                    }
            }break;
            case 3:
            {
                printf("Enter Email : ");
                scanf(" %[^\n]",edit_email);
                printf("\n========================================================================================================================\n");
                printf("%-5s %-30s %-15s %-30s\n", "S.No", "Name", "Phone", "Email");
                printf("------------------------------------------------------------------------------------------------------------------------\n");
    
                for(int i=0;i<addressBook -> contactCount;i++)
                {
                    if(strcasestr(addressBook->contacts[i].email, edit_email) != 0)
                    {
                        c_flag=1;
                        printf("%d.%-30s %-15s %-30s\n",j+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        arr[j]=i;
                        count++;
                        j++;
                    }
                }
                if(c_flag==0)
                    {
                        printf("\nNo Contact Found...\n");
                        return;
                    }
            }break;
        case 4 :{
                printf("Enter Name : ");
                scanf(" %[^\n]",edit_name);
                printf("\n========================================================================================================================\n");
                printf("%-5s %-30s %-15s %-30s\n", "S.No", "Name", "Phone", "Email");
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                for(int i=0;i<addressBook -> contactCount;i++)
                {
                    if(strcasestr(addressBook->contacts[i].name, edit_name) != NULL)
                    {
                        c_flag=1;
                        printf("%d.%-30s %-15s %-30s\n",j+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        arr[j]=i;
                        count++;
                        j++;
                    }
                }
                if(c_flag==0)
                    {
                        printf("\nNo Contact Found...\n");
                        return;
                    }
            } break;
        case 5 : printf("Conform to Exit (y/n) : ");
                scanf(" %s",exit);
                if(strcasestr(EXIT,exit)!=0)
                {
                    return;
                }
                else{
                    void editContact(AddressBook *addressBook);
                }
                break;
            default : printf(" Invalid Selection...\n");
                break;
    }
    // Asking the user to select contact to edit.
        if(count>1)
        {
            printf("\nMultiple Contactes are found...\nPlese Select which One do you want to Edit : ");
            scanf(" %d",&index);
            index--;
            index = arr[index];
        }
        else
        {
            index=arr[0];
        }
        int flag=1;
        char temp_name[60];
        char temp_phone[20];
        char temp_email[50];

        if(op==1 || op==4 )
        {
            for(int i=0;i<3;i++)
          {
           printf("Edit Name %s --> ",addressBook->contacts[index].name);
            scanf(" %[^\n]",temp_name);
            if(strlen(temp_name)<=3)
            {
                printf("ERROR : Name must contain at least 4 characters..\n");
                continue;
            }
            if(strlen(temp_name)>50)
            {
                printf("ERROR : Invalid Input (Name should be less than 50 characters)!!\n");
                continue;
            }
            int char_flag=0;
            for(int a=0;temp_name[a]!='\0';a++)
            {
                char_flag=1;
                if((temp_name[a] >='A' &&  temp_name[a] <='Z')|| (temp_name[a]==' ') || (temp_name[a] >='a' &&  temp_name[a] <='z') )
                {
                    char_flag=0;
                }
                if(char_flag==1)
                {
                    printf("ERROR : Name should contain only alphabets..\n");
                    break;
                }
            }
            if(char_flag==0)
            {
                flag=0;
                break;
            }
        }
        if(flag==1)
        {   printf("Pleae Try Again..\n");
            return;
        }
        if(op==1)
        {
            strcpy(addressBook->contacts[index].name,temp_name);
            printf("\nContact Edits Saved Sucessfully..\n");
            return;
        }
    }
    if(op==2|| op==4)
    {
        flag=1;
        for(int i=0;i<3;i++)
        {
            printf("Edit Phone %s --> ",addressBook->contacts[index].phone);
            scanf(" %[^\n]",temp_phone);
            getchar();
            if(strlen(temp_phone)!=10)
            {
                printf("ERROR : Invalid Input (Phone number contain only 10 numbers)!!\n");
                continue;
            }
            if(temp_phone[0] < '6' || temp_phone[0] >'9')
            {
                printf("ERROR : First digit must be between 6 To 9..\n");
                continue;
            }
            int count=0;
            for(int i=0;temp_phone[i]!='\0';i++)
            {
                if(temp_phone[i]>='0'&& temp_phone[i]<='9')
                {
                    count++;
                }
            }
            if(strlen(temp_phone)!= count)
            {
                printf("ERROR : Invalid Input (Phone number contain must numbers only)!!\n");
                continue;
            }
            int duplicate=0;
            for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if(strcmp(addressBook->contacts[i].phone, temp_phone) == 0)
                    {
                    printf(" ERROR : Phone number is already Exist..\n");
                    duplicate=1;
                    break;
                }
            }
            if(duplicate==1)
            {
                continue;
            }
            flag=0;
            break;
        }
        if(flag==1)
        {   printf("Pleae Try Again..\n");
            return;
        }
        if(op==2)
        {
            strcpy(addressBook->contacts[index].phone,temp_phone);
            printf("\nContact Edits Saved Sucessfully..\n");
            return;
        }
    }
    if(op==3 || op == 4)
    {
        flag=1;
        for(int j=0; j<3; j++)
        {
            printf("Edit Email %s --> ",addressBook->contacts[index].email);
            scanf(" %[^\n]", temp_email);
            
            if(strlen(temp_email) > 50 || strlen(temp_email) <= 0)
            {
                printf("ERROR: Email must be between 1-50 characters.\n");
                continue;
            }
            
            // Check first 3 characters are letters
            int first3_valid = 1;
            for(int i=0; i<3 && temp_email[i]!='\0'; i++)
            {
                if(!(temp_email[i] >= 'a' && temp_email[i] <= 'z'))
                {
                    first3_valid = 0;
                    break;
                }
            }
            if(!first3_valid)
            {
                printf("First 3 characters of email must be letters only...\n");
                continue;
            }
            
            // Validate email - collect data first
            int at_pos = -1, dot_pos = -1;
            int at_count = 0, dot_count = 0;
            int valid = 1;
            
            for(int i=0; temp_email[i]!='\0'; i++)
            {
                char ch = temp_email[i];
                if(!((ch >= 'a' && ch <= 'z')|| (ch >= '0' && ch <= '9') || ch == '@' || ch == '_'|| ch=='.'))
                {
                    valid = 0;
                    printf("ERROR: Invalid character in email.\n");
                    break;
                }
                
                if(ch == '@')
                {
                    at_count++;
                    at_pos = i;
                }
                else if(ch == '.')
                {
                    dot_count++;
                    dot_pos = i;
                }
            }
            if(!valid)
                continue;
            if(at_count == 0 || dot_count == 0)
            {
                printf("ERROR: Email must contain @ and .\n");
                continue;
            }
            
            // Check only one @ and .
            if(at_count > 1 || dot_count > 1)
            {
                printf("ERROR: Email must contain only one @ and .\n");
                continue;
            }
            
            // Check @ before . with at least one character between
            if(at_pos > dot_pos || dot_pos - at_pos <= 1)
            {
                printf("ERROR: '.' must come after '@' with at least one character between.\n");
                continue;
            }
            int domain_len = 0;
            for(int i = dot_pos + 1; temp_email[i] != '\0'; i++)
                domain_len++;
            
            if(domain_len == 4 )
            {
                printf("ERROR: After '.com' no extra characters should be present..\n");
                continue;
            }
            
            // Check duplicate
            int duplicate = 0;
            for(int i=0; i<addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].email, temp_email) == 0)
                {
                    printf("ERROR: Email already exists.\n");
                    duplicate = 1;
                    break;
                }
            }
            if(duplicate)
                continue;
            
            flag = 0;
            break;
        }

        if(flag == 1)
        {
            printf("Please Try Again.\n");
            return;
        }
         if(op==3)
        {
           strcpy(addressBook->contacts[index].email,temp_email);
            printf("\nContact Edits Saved Sucessfully..\n");
            return;
        }
    }
        strcpy(addressBook->contacts[index].name,temp_name);
        strcpy(addressBook->contacts[index].phone,temp_phone);
        strcpy(addressBook->contacts[index].email,temp_email);
        printf("\nContact Edits Saved Sucessfully..\n");
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int op,count=0,c_flag=0;
    int index,j=0,arr[100]={0};
    char delete_phone[11],exit[2];
    char delete_name[50],delete_email[50];
    char EXIT[2]={"Y"};
    printf("Select Delete criteria:\n");
    printf("1. Delete by Name\n");
    printf("2. Delete by Phone\n");
    printf("3. Delete by Email\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d",&op);
    getchar();
    switch(op)
    {
        case 1 :
            {
                printf("Enter Name : ");
                scanf(" %[^\n]",delete_name);
                printf("\n========================================================================================================================\n");
                printf("%-5s %-30s %-15s %-30s\n", "S.No", "Name", "Phone", "Email");
                printf("------------------------------------------------------------------------------------------------------------------------\n");
    
                for(int i=0;i<addressBook -> contactCount;i++)
                {
                    if(strcasestr(addressBook->contacts[i].name, delete_name) != NULL)
                    {
                        c_flag=1;
                        printf("%d.%-30s %-15s %-30s\n",j+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        arr[j]=i;
                        count++;
                        j++;
                    }
                }
                if(c_flag==0)
                    {
                        printf("\nNo Contact Found...\n");
                        return;
                    }
            }break;
            case 2:
            {
                printf("Enter Phone : ");
                scanf(" %[^\n]",delete_phone);
                printf("\n========================================================================================================================\n");
                printf("%-5s %-30s %-15s %-30s\n", "S.No", "Name", "Phone", "Email");
                printf("------------------------------------------------------------------------------------------------------------------------\n");
    
                for(int i=0;i<addressBook -> contactCount;i++)
                {
                    if(strcasestr(addressBook->contacts[i].phone, delete_phone) != 0)
                    {
                        c_flag=1;
                        printf("%d.%-30s %-15s %-30s\n",j+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        arr[j]=i;
                        count++;
                        j++;
                    }
                }
                if(c_flag==0)
                    {
                        printf("\nNo Contact Found...\n");
                        return;
                    }
            }break;
            case 3:
            {
                printf("Enter Email : ");
                scanf(" %[^\n]",delete_email);
                printf("\n========================================================================================================================\n");
                printf("%-5s %-30s %-15s %-30s\n", "S.No", "Name", "Phone", "Email");
                printf("------------------------------------------------------------------------------------------------------------------------\n");
    
                for(int i=0;i<addressBook -> contactCount;i++)
                {
                    if(strcasestr(addressBook->contacts[i].email, delete_email) != 0)
                    {
                        c_flag=1;
                        printf("%d.%-30s %-15s %-30s\n",j+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        arr[j]=i;
                        count++;
                        j++;
                    }
                }
                if(c_flag==0)
                    {
                        printf("\nNo Contact Found...\n");
                        return;
                    }
            }break;
        case 4 : printf("Conform to Exit (y/n) : ");
                scanf(" %s",exit);
                if(strcasestr(EXIT,exit)!=0)
                {
                    return;
                }
                else{
                    void editContact(AddressBook *addressBook);
                }
                break;
            default : printf(" Invalid Selection...\n");
                break;
    }
        if(count>1)
        {
            printf("\nMultiple Contactes are found...\nPlese Select which One do you want to Delete : ");
            scanf(" %d",&index);
            getchar();
            index--;
             if(index < 0 || index >= count)
             {
                printf("Invalid selection.\n");
                return;
            }
            index = arr[index];
        }
        else if(count ==1)
        {
            index=arr[0];
        }
        else
        {
            printf("No contacts found.\n");
            return;
        } 
        char conformation[2],Yes[2]={"y"};
        printf("Conform to Delete the contact of ''%s'' (y/n) : ",addressBook->contacts[index].name);
        scanf("%s",conformation);
        // Deleating the user selected contact by the Right Shifting contacts.
        if(strcasestr(Yes,conformation)!=0)
        {   for(int i=index;i < addressBook->contactCount-1;i++)
            {
                addressBook->contacts[i]=addressBook->contacts[i+1];
            }
            addressBook->contactCount--;
            printf("Contact Deleted Sucessfully!!!\n");
        }
        else{
            printf("Contact Deletion Cancelled....\n");
            return;
        }   
}


//gcc main.c contact.c file.c populate.c -o addressbook
//./addressbook