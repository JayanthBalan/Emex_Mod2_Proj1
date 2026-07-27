#ifndef FILE_H
#define FILE_H

#include "contact.h"

void saveContactsToFile(AddressBook *addressBook);
size_t loadContactsFromFile(AddressBook *addressBook);

#endif
