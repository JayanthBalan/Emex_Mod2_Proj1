
#include <stdio.h>
#include "contact.h"

int main() {
    unsigned char choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");
        printf("7. Force quit\n");
        printf("Enter your choice: ");
        scanf("%1[^\n]", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                unsigned char sortChoice, tries = 0;
                SortCriteriaRetry:
                printf("\nSort Criteria:\n");
                printf("1. Name\n");
                printf("2. Phone\n");
                printf("3. Email\n");
                scanf("%hhu", &sortChoice);
                if(sortChoice < 1 || sortChoice > 3) {
                    tries++;
                    printf("Invalid sort criteria. RETRY.\n");
                    if(tries >= 3) {
                        printf("Too many invalid attempts. Returning to main menu.\n");
                        break;
                    }
                    goto SortCriteriaRetry;
                }
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            case 7:
                printf("Force quitting without saving...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != '6' && choice != '7');
    
    return 0;
}
