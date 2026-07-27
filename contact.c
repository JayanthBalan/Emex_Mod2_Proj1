
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>

unsigned char index_name[MAX_CONTACTS], index_phone[MAX_CONTACTS], index_email[MAX_CONTACTS];

void sortContactPopulate(AddressBook *addressBook) {
    // Populate function to add a contact to address book
    Contact *cont = &addressBook->contacts[addressBook->contactCount - 1];
    unsigned char flag1 = 0, flag2 = 0, flag3 = 0;
    for(size_t i = 0; i < addressBook->contactCount - 1; i++) {
        if(flag1 == 0 && strcmp(addressBook->contacts[index_name[i]].name, cont->name) > 0) {
            for(int k = (int)addressBook->contactCount - 2; k >= (int)i; k--) {
                index_name[k + 1] = index_name[k];
            }
            index_name[i] = addressBook->contactCount - 1;
            flag1 = 1;
        }
        if(flag2 == 0 && strcmp(addressBook->contacts[index_phone[i]].phone, cont->phone) > 0) {
            for(int k = (int)addressBook->contactCount - 2; k >= (int)i; k--) {
                index_phone[k + 1] = index_phone[k];
            }
            index_phone[i] = addressBook->contactCount - 1;
            flag2 = 1;
        }
        if(flag3 == 0 && strcmp(addressBook->contacts[index_email[i]].email, cont->email) > 0) {
            for(int k = (int)addressBook->contactCount - 2; k >= (int)i; k--) {
                index_email[k + 1] = index_email[k];
            }
            index_email[i] = addressBook->contactCount - 1;
            flag3 = 1;
        }
        if(flag1 && flag2 && flag3) {
            break; // All indices have been populated, exit the loop
        }
    }
    if (!flag1) {
        index_name[addressBook->contactCount - 1] = addressBook->contactCount - 1;
    }
    if (!flag2) {
        index_phone[addressBook->contactCount - 1] = addressBook->contactCount - 1;
    }
    if (!flag3) {
        index_email[addressBook->contactCount - 1] = addressBook->contactCount - 1;
    }
}

void listContacts(AddressBook *addressBook, unsigned char sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    unsigned char *criteria;
    size_t count = addressBook->contactCount;
    switch(sortCriteria) {
        case 1: // Sort by name
            criteria = index_name;
            break;
        case 2: // Sort by phone
            criteria = index_phone;
            break;
        case 3: // Sort by email
            criteria = index_email;
            break;
        default:
            printf("Invalid sort criteria.\n");
            return;
    }

    for(size_t i = 0; i < count; i++) {
        Contact *contact = &addressBook->contacts[criteria[i]];
        printf("Contact %zu: %s, %s, %s\n", i + 1, contact->name, contact->phone, contact->email);
    }
}

void initialize(AddressBook *addressBook) {
    if(loadContactsFromFile(addressBook) == 0) {
        return; // Populate address book not required
    }
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    if(addressBook->contactCount >= MAX_CONTACTS) {
        printf("Address book is full. Cannot add more contacts.\n");
        return;
    }

    char name[50], phone[20], email[50], create_retry = 0;

    createContactRetry:
    getchar();
    printf("Enter name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    for(char *ptr = name; *ptr != '\0'; ptr++) {
        if(!((*ptr >= 65 && *ptr <= 90) || (*ptr >= 97 && *ptr <= 122) || *ptr == ' ' || *ptr == '.')) {
            printf("Name Invalid. Retry...");
            if(create_retry < 3) {
                create_retry++;
                goto createContactRetry;
            }
            return;
        }
    }

    printf("Enter phone: ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;
    for(char *ptr = phone; *ptr != '\0'; ptr++) {
        if(!((*ptr >= 48 && *ptr <= 57) || *ptr == ' ' || *ptr == '+' || *ptr == '-')) {
            printf("Phone Invalid. Retry...");
            if(create_retry < 3) {
                create_retry++;
                goto createContactRetry;
            }
            return;
        }
    }
    
    printf("Enter email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0;
    for(char *ptr = email; *ptr != '\0'; ptr++) {
        if(!((*ptr >= 97 && *ptr <= 122) || *ptr == '.' || (*ptr >= 48 && *ptr <= 57) || *ptr == 64 || *ptr == '_')) {
            printf("Email Invalid. Retry...");
            if(create_retry < 3) {
                create_retry++;
                goto createContactRetry;
            }
            return;
        }
    }

    unsigned char flag1 = 0, flag2 = 0, flag3 = 0;
    for(size_t i = 0; i < addressBook->contactCount; i++) {
        if(strcmp(addressBook->contacts[index_phone[i]].phone, phone) == 0) {
            printf("A contact with this phone number already exists. Cannot add duplicate.\n");
            return;
        }
        if(strcmp(addressBook->contacts[index_email[i]].email, email) == 0) {
            printf("A contact with this email already exists. Cannot add duplicate.\n");
            return;
        }

        if(flag1 == 0 && strcmp(addressBook->contacts[index_name[i]].name, name) > 0) {
            for(int k = (int)addressBook->contactCount - 1; k >= (int)i; k--) {
                index_name[k + 1] = index_name[k];
            }
            index_name[i] = addressBook->contactCount;
            flag1 = 1;
        }
        if(flag2 == 0 && strcmp(addressBook->contacts[index_phone[i]].phone, phone) > 0) {
            for(int k = (int)addressBook->contactCount - 1; k >= (int)i; k--) {
                index_phone[k + 1] = index_phone[k];
            }
            index_phone[i] = addressBook->contactCount;
            flag2 = 1;
        }
        if(flag3 == 0 && strcmp(addressBook->contacts[index_email[i]].email, email) > 0) {
            for(int k = (int)addressBook->contactCount - 1; k >= (int)i; k--) {
                index_email[k + 1] = index_email[k];
            }
            index_email[i] = addressBook->contactCount;
            flag3 = 1;
        }
        if(flag1 && flag2 && flag3) {
            break; // All indices have been populated, exit the loop
        }
    }
    if (!flag1) {
        index_name[addressBook->contactCount] = addressBook->contactCount;
    }
    if (!flag2) {
        index_phone[addressBook->contactCount] = addressBook->contactCount;
    }
    if (!flag3) {
        index_email[addressBook->contactCount] = addressBook->contactCount;
    }

    addressBook->contacts[addressBook->contactCount++] = (Contact){0};
    strcpy(addressBook->contacts[addressBook->contactCount - 1].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount - 1].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount - 1].email, email);
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    getchar();
    char searchTerm[50];
    printf("Enter search term: ");
    fgets(searchTerm, sizeof(searchTerm), stdin);
    searchTerm[strcspn(searchTerm, "\n")] = 0;

    unsigned char *searchCriteria, type;
    if(strchr(searchTerm, '@') != NULL) {
        searchCriteria = index_email;
        type = 0;
    }
    else if(isdigit(searchTerm[0]) || (searchTerm[0] == '+' && isdigit(searchTerm[1]))) {
        searchCriteria = index_phone;
        type = 1;
    }
    else {
        searchCriteria = index_name;
        type = 2;
    }

    int count = addressBook->contactCount;
    int low = 0, high = count - 1, i;
    while(low <= high) {
        i = (low + high) / 2;
        const char *compareField = (type == 0 ? addressBook->contacts[searchCriteria[i]].email : 
            (type == 1 ? addressBook->contacts[searchCriteria[i]].phone : addressBook->contacts[searchCriteria[i]].name));
        int cmp = strcmp(searchTerm, compareField);
        if(cmp > 0) {
            low = i + 1;
        }
        else if(cmp < 0) {
            high = i - 1;
        }
        else {
            if(type != 2) {
                printf("Contact found: %s, %s, %s\nEntry number: %d\n", addressBook->contacts[searchCriteria[i]].name, 
                    addressBook->contacts[searchCriteria[i]].phone, 
                    addressBook->contacts[searchCriteria[i]].email, 
                    searchCriteria[i] + 1);
                return;
            }

            int up = i, down = i;
            while(up >= 0 && strcmp(searchTerm, addressBook->contacts[searchCriteria[up]].name) == 0) {
                up--;
            }
            up++; // Slide back correction to first matching index
            while(down < count && strcmp(searchTerm, addressBook->contacts[searchCriteria[down]].name) == 0) {
                down++;
            }
            for(int j = up; j < down; j++) {
                printf("Contact found: %s, %s, %s\nEntry number: %d\n", addressBook->contacts[searchCriteria[j]].name, 
                    addressBook->contacts[searchCriteria[j]].phone, 
                    addressBook->contacts[searchCriteria[j]].email, 
                    searchCriteria[j] + 1);
            }
            return;
        }
    }
    printf("Contact not found.\n");
}

static int* findContact_internal(AddressBook *addressBook, const char *searchTerm, unsigned char *type) 
{
    /* Define the logic for search */

    unsigned char *searchCriteria;
    if(strchr(searchTerm, '@') != NULL) {
        searchCriteria = index_email;
        *type = 0;
    }
    else if(isdigit(searchTerm[0]) || (searchTerm[0] == '+' && isdigit(searchTerm[1]))) {
        searchCriteria = index_phone;
        *type = 1;
    }
    else {
        searchCriteria = index_name;
        *type = 2;
    }

    static int fIdx[2];
    fIdx[0] = -1;
    fIdx[1] = -1;

    int count = addressBook->contactCount;
    int low = 0, high = count - 1, i;
    while(low <= high) {
        i = (low + high) / 2;
        const char *compareField = (*type == 0 ? addressBook->contacts[searchCriteria[i]].email : 
            (*type == 1 ? addressBook->contacts[searchCriteria[i]].phone : addressBook->contacts[searchCriteria[i]].name));
        int cmp = strcmp(searchTerm, compareField);
        if(cmp > 0) {
            low = i + 1;
        }
        else if(cmp < 0) {
            high = i - 1;
        }
        else {
            if(*type != 2) {
                fIdx[0] = i;
                return fIdx;
            }

            int up = i, down = i;
            while(up >= 0 && strcmp(searchTerm, addressBook->contacts[searchCriteria[up]].name) == 0) {
                up--;
            }
            up++;

            while(down < count && strcmp(searchTerm, addressBook->contacts[searchCriteria[down]].name) == 0) {
                down++;
            }

            fIdx[0] = up;
            if(down - up > 1) {
                fIdx[1] = down;
            }
            return fIdx;
        }
    }
    return fIdx;
}

static void remove_rank(unsigned char *index_table, size_t idx, size_t cnt) {
    // Remove an element and slide left
    for(size_t i = idx; i < cnt - 1; i++) {
        index_table[i] = index_table[i + 1];
    }
} 

static void sortContact_internal(AddressBook *addressBook, Contact *cont, unsigned char origin_idx) {
    // Readjust rankings for modified contact
    size_t count = addressBook->contactCount;
    for(size_t i = 0; i < count; i++) {
        if(index_name[i] == origin_idx) {
            remove_rank(index_name, i, count);
            break;
        }
    }
    for(size_t i = 0; i < count; i++) {
        if(index_phone[i] == origin_idx) {
            remove_rank(index_phone, i, count);
            break;
        }
    }
    for(size_t i = 0; i < count; i++) {
        if(index_email[i] == origin_idx) {
            remove_rank(index_email, i, count);
            break;
        }
    }

    unsigned char flag1 = 0, flag2 = 0, flag3 = 0;
    for(size_t i = 0; i < count - 1 && !(flag1 && flag2 && flag3); i++) {
        if(flag1 == 0 && strcmp(addressBook->contacts[index_name[i]].name, cont->name) > 0) {
            for(int k = (int)count - 2; k >= (int)i; k--) {
                index_name[k + 1] = index_name[k];
            }
            index_name[i] = origin_idx;
            flag1 = 1;
        }
        if(flag2 == 0 && strcmp(addressBook->contacts[index_phone[i]].phone, cont->phone) > 0) {
            for(int k = (int)count - 2; k >= (int)i; k--) {
                index_phone[k + 1] = index_phone[k];
            }
            index_phone[i] = origin_idx;
            flag2 = 1;
        }
        if(flag3 == 0 && strcmp(addressBook->contacts[index_email[i]].email, cont->email) > 0) {
            for(int k = (int)count - 2; k >= (int)i; k--) {
                index_email[k + 1] = index_email[k];
            }
            index_email[i] = origin_idx;
            flag3 = 1;
        }
    }
    if (!flag1) {
        index_name[count - 1] = origin_idx;
    }
    if (!flag2) {
        index_phone[count - 1] = origin_idx;
    }
    if (!flag3) {
        index_email[count - 1] = origin_idx;
    }
}

static unsigned char check_Duplicate(AddressBook *addressBook, const char *field, unsigned char type, int idx) {
    // Check for duplicate phone or email
    unsigned char *searchCriteria = (type == 2 ? index_phone : index_email);
    size_t count = addressBook->contactCount;
    for(size_t i = 0; i < count; i++) {
        if(searchCriteria[i] == idx) {
            continue;
        }
        const char *compareField = (type == 2 ? addressBook->contacts[searchCriteria[i]].phone : 
            addressBook->contacts[searchCriteria[i]].email);
        if(strcmp(compareField, field) == 0) {
            return 0; // Duplicate found
        }
    }
    return 1; // No duplicate
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    getchar();
    char searchTerm[50];
    printf("Enter the contact to edit:\n");
    fgets(searchTerm, sizeof(searchTerm), stdin);
    searchTerm[strcspn(searchTerm, "\n")] = 0;

    unsigned char type, *searchCriteria, retry = 0;
    int *idx_contact = findContact_internal(addressBook, searchTerm, &type), idx = -1;
    if(idx_contact[0] == -1) {
        printf("Contact not found.\n");
        return;
    }

    if(type == 2 && idx_contact[1] != -1) {
        SearchCriteriaRetry:
        printf("Multiple contacts found under %s. Please refine search with mobile number or email address: ", searchTerm);
        fgets(searchTerm, sizeof(searchTerm), stdin);
        searchTerm[strcspn(searchTerm, "\n")] = 0;
        
        if(strchr(searchTerm, '@') != NULL) {
            searchCriteria = index_email;
            type = 0;
        }
        else {
            searchCriteria = index_phone;
            type = 1;
        }

        for(int i = idx_contact[0]; i < idx_contact[1]; i++) {
            int contactIdx = index_name[i];
            const char *compareField = (type == 0 ? addressBook->contacts[contactIdx].email : 
                addressBook->contacts[contactIdx].phone);
            if(strcmp(compareField, searchTerm) == 0) {
                idx = contactIdx;
                break;
            }
        }

        if(idx == -1) {
            printf("No contact found with the provided details.\n");
            if(retry < 3) {
                retry++;
                goto SearchCriteriaRetry;
            }
            return;
        }
    }
    else if(type != 2) {
        searchCriteria = type == 0 ? index_email : index_phone;
        idx = searchCriteria[idx_contact[0]];
    }
    else if (type == 2) {
        idx = index_name[idx_contact[0]];
    }

    Contact *target = &addressBook->contacts[idx];
    printf("Contact Details: %s, %s, %s\nEntry number: %d\n", target->name, target->phone, target->email, idx + 1);
    
    unsigned char fieldChoice;
    printf("Choose field to modify (1.Name, 2.Phone, 3.Email): ");
    scanf("%hhu", &fieldChoice);
    getchar();
    printf("Enter modified field: ");
    switch(fieldChoice) {
        case 1:
            fgets(target->name, sizeof(target->name), stdin);
            target->name[strcspn(target->name, "\n")] = 0;
            break;
        case 2:
            fgets(searchTerm, sizeof(target->phone), stdin);
            searchTerm[strcspn(searchTerm, "\n")] = 0;
            if(!check_Duplicate(addressBook, searchTerm, 2, idx)) {
                printf("A contact with this phone number already exists. No changes made.\n");
                return;
            }
            strcpy(target->phone, searchTerm);
            break;
        case 3:
            fgets(searchTerm, sizeof(target->email), stdin);
            searchTerm[strcspn(searchTerm, "\n")] = 0;
            if(!check_Duplicate(addressBook, searchTerm, 3, idx)) {
                printf("A contact with this email already exists. No changes made.\n");
                return;
            }
            strcpy(target->email, searchTerm);
            break;
        default:
            printf("Invalid choice. No changes made.\n");
            return;
    }
    sortContact_internal(addressBook, target, idx);
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    char searchTerm[50];
    getchar();
    printf("Enter the contact to delete:\n");
    fgets(searchTerm, sizeof(searchTerm), stdin);
    searchTerm[strcspn(searchTerm, "\n")] = 0;

    unsigned char type, *searchCriteria, retry = 0;
    int *idx_contact = findContact_internal(addressBook, searchTerm, &type), idx = -1;
    if(idx_contact[0] == -1) {
        printf("Contact not found.\n");
        return;
    }

    if(type == 2 && idx_contact[1] != -1) {
        SearchCriteriaRetry:
        printf("Multiple contacts found under %s. Please refine search with mobile number or email address: ", searchTerm);
        fgets(searchTerm, sizeof(searchTerm), stdin);
        searchTerm[strcspn(searchTerm, "\n")] = 0;

        if(strchr(searchTerm, '@') != NULL) {
            searchCriteria = index_email;
            type = 0;
        }
        else {
            searchCriteria = index_phone;
            type = 1;
        }

        for(int i = idx_contact[0]; i < idx_contact[1]; i++) {
            int contactIdx = index_name[i];
            const char *compareField = (type == 0 ? addressBook->contacts[contactIdx].email :
                addressBook->contacts[contactIdx].phone);

            if(strcmp(compareField, searchTerm) == 0) {
                idx = contactIdx;
                break;
            }
        }

        if(idx == -1) {
            printf("No contact found with the provided details.\n");
            if(retry < 3) {
                retry++;
                goto SearchCriteriaRetry;
            }
            return;
        }
    }
    else if(type != 2) {
        searchCriteria = (type == 0) ? index_email : index_phone;
        idx = searchCriteria[idx_contact[0]];
    }
    else {
        idx = index_name[idx_contact[0]];
    }

    printf("Deleting Contact: %s, %s, %s\n", addressBook->contacts[idx].name,
        addressBook->contacts[idx].phone,
        addressBook->contacts[idx].email);

    size_t count = addressBook->contactCount;

    for(size_t i = 0; i < count; i++) {
        if(index_name[i] == idx) {
            remove_rank(index_name, i, count);
            break;
        }
    }
    for(size_t i = 0; i < count; i++) {
        if(index_phone[i] == idx) {
            remove_rank(index_phone, i, count);
            break;
        }
    }
    for(size_t i = 0; i < count; i++) {
        if(index_email[i] == idx) {
            remove_rank(index_email, i, count);
            break;
        }
    }

    for(size_t i = idx; i < count - 1; i++) {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    for(size_t i = 0; i < count - 1; i++) {
        if(index_name[i] > idx) {
            index_name[i]--;
        }
        if(index_phone[i] > idx) {
            index_phone[i]--;
        }
        if(index_email[i] > idx) {
            index_email[i]--;
        }
    }

    addressBook->contactCount--;
    printf("Contact deleted successfully.\n");
}
