# Address Book
### **Author:** Jayanth Balan

> A terminal-based Address Book application written in C as part of the Emertxe Advanced C module.

The project lets users manage contacts through a menu-driven interface. Contacts can be created, searched, edited, deleted, listed, and saved to a binary file for persistence. The application also maintains sorted indexes for names, phone numbers, and email addresses to support faster searching and listing without rearranging the original contact array.

## Features

- Create new contacts
- Search contacts by name, phone number, or email
- Edit existing contact details
- Delete contacts
- List contacts sorted by name, phone number, or email
- Prevent duplicate phone numbers and email addresses
- Handle multiple contacts with the same name using phone number or email refinement
- Save contacts to a file and load them on startup

## Concepts Used

- Structures
- Arrays and index tables
- Binary search
- File handling
- String handling
- Modular programming

## Build

``` bash
gcc -Wall -Wextra -std=c11 main.c contact.c file.c populate.c -o addressbook
./addressbook
```
