#ifndef CONTACT_H
#define CONTACT_H

#include <stdbool.h>

typedef struct Contact_data {
    char Name[32];
    char Mobile_number[11];
    char Mail_ID[35];
} Contacts;

typedef struct AddressBook_Data {
    Contacts contact_details[100];
    int contact_count;
} AddressBook;

/* Initialization */
void init_addressbook(AddressBook *addressbook);

/* Core functions */
int create_contact(AddressBook *addressbook);
void list_contacts(AddressBook *addressbook);
int edit_contact(AddressBook *addressbook);
int delete_contact(AddressBook *addressbook);
int search_contacts(AddressBook *addressbook);
int save_contacts(AddressBook *addressbook);

/* Search helpers */
int search_name(AddressBook *addressbook);
int search_phone(AddressBook *addressbook);
int search_email(AddressBook *addressbook);

/* Validation + helpers */
void print_contact(Contacts *c, int i);
bool validate_name(char *name);
bool validate_phone(AddressBook *addressbook, char *phone);
bool validate_email(AddressBook *addressbook, char *email);

#endif
