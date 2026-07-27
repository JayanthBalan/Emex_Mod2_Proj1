#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE *fp = fopen("addressbook.dat", "wb");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    if(fwrite(addressBook, sizeof(AddressBook), 1, fp) != 1) {
        printf("Error writing file.\n");
    }
    fclose(fp);
    printf("Contacts saved to addressbook.dat\n");
}

unsigned char loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp = fopen("addressbook.dat", "rb");
    if (fp == NULL) {
        printf("Error: File does not exist.\n");
        return 2;
    }
    if(fread(addressBook, sizeof(AddressBook), 1, fp) != 1) {
        printf("Empty File: Populate structure\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);
    printf("Contacts loaded from addressbook.dat\n");
    return 0;
}
