#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

extern unsigned char index_name[MAX_CONTACTS], index_phone[MAX_CONTACTS], index_email[MAX_CONTACTS];

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    size_t contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, unsigned char sortCriteria);
void initialize(AddressBook *addressBook);
void sortContactPopulate(AddressBook *addressBook);

#endif
