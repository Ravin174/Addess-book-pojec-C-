#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "contact.h"

/*Initialization*/
void init_addressbook(AddressBook *addressbook) {
    addressbook->contact_count = 0;
}

/* Validation Helpers*/
bool validate_name(char *name) {
    return strlen(name) > 0; // simple check
}

bool validate_phone(AddressBook *addressbook, char *phone) {
    if (strlen(phone) != 10) return false;
    for (int i = 0; i < addressbook->contact_count; i++) {
        if (strcmp(addressbook->contact_details[i].Mobile_number, phone) == 0)
            return false; // duplicate
    }
    return true;
}

bool validate_email(AddressBook *addressbook, char *email) {
    const char *domain = "@gmail.com";
    int len_email = strlen(email);
    int len_domain = strlen(domain);

    if (len_email <= len_domain) {
        printf("Invalid email! Must end with @gmail.com\n");
        return false;
    }
    if (strcmp(email + (len_email - len_domain), domain) != 0) {
        printf("Invalid email! Only @gmail.com addresses are allowed.\n");
        return false;
    }
    for (int i = 0; i < addressbook->contact_count; i++) {
        if (strcmp(addressbook->contact_details[i].Mail_ID, email) == 0) {
            printf("Duplicate email not allowed!\n");
            return false;
        }
    }
    return true;
}

/* CRUD Operations */
int create_contact(AddressBook *addressbook) {
    if (addressbook->contact_count >= 100) {
        printf("AddressBook full!\n");
        return 0;
    }

    Contacts *c = &addressbook->contact_details[addressbook->contact_count];

    printf("Enter Name: ");
    scanf("%31s", c->Name);
    if (!validate_name(c->Name)) {
        printf("Invalid name!\n");
        return 0;
    }

    printf("Enter Phone (10 digits): ");
    scanf("%10s", c->Mobile_number);
    if (!validate_phone(addressbook, c->Mobile_number)) {
        printf("Invalid or duplicate phone!\n");
        return 0;
    }

    printf("Enter Email: ");
    scanf("%34s", c->Mail_ID);
    if (!validate_email(addressbook, c->Mail_ID)) {
        printf("Invalid or duplicate email!\n");
        return 0;
    }

    addressbook->contact_count++;
    printf("Contact added successfully!\n");
    return 1;
}

void list_contacts(AddressBook *addressbook) {
    if (addressbook->contact_count == 0) {
        printf("\nNo contacts found!\n");
        return;
    }

    printf("\n-----------------------------------------------------------------\n");
    printf("| %-3s | %-20s | %-12s | %-30s |\n",
           "No", "Name", "Phone", "Email");
    printf("-----------------------------------------------------------------\n");

    for (int i = 0; i < addressbook->contact_count; i++) {
        printf("| %-3d | %-20s | %-12s | %-30s |\n",
               i + 1,
               addressbook->contact_details[i].Name,
               addressbook->contact_details[i].Mobile_number,
               addressbook->contact_details[i].Mail_ID);
    }

    printf("-----------------------------------------------------------------\n");
}

int edit_contact(AddressBook *addressbook) {
    if (addressbook->contact_count == 0) {
        printf("No contacts to edit!\n");
        return 0;
    }

    int index;
    list_contacts(addressbook);
    printf("Enter contact number to edit: ");
    scanf("%d", &index);

    if (index < 1 || index > addressbook->contact_count) {
        printf("Invalid index!\n");
        return 0;
    }

    Contacts *c = &addressbook->contact_details[index - 1];

    printf("Enter new Name: ");
    scanf("%31s", c->Name);
    printf("Enter new Phone: ");
    scanf("%10s", c->Mobile_number);
    printf("Enter new Email: ");
    scanf("%34s", c->Mail_ID);

    printf("Contact updated successfully!\n");
    return 1;
}

int delete_contact(AddressBook *addressbook) {
    if (addressbook->contact_count == 0) {
        printf("No contacts to delete!\n");
        return 0;
    }

    int index;
    list_contacts(addressbook);
    printf("Enter contact number to delete: ");
    scanf("%d", &index);

    if (index < 1 || index > addressbook->contact_count) {
        printf("Invalid index!\n");
        return 0;
    }

    for (int i = index - 1; i < addressbook->contact_count - 1; i++) {
        addressbook->contact_details[i] = addressbook->contact_details[i + 1];
    }

    addressbook->contact_count--;
    printf("Contact deleted successfully!\n");
    return 1;
}

/*Search*/
int search_name(AddressBook *addressbook) {
    char name[32];
    printf("Enter name to search: ");
    scanf("%31s", name);

    for (int i = 0; i < addressbook->contact_count; i++) {
        if (strcmp(addressbook->contact_details[i].Name, name) == 0) {
            printf("\nResult:\n");
            printf("-----------------------------------------------------------------\n");
            printf("| %-3s | %-20s | %-12s | %-30s |\n",
                   "No", "Name", "Phone", "Email");
            printf("-----------------------------------------------------------------\n");
            printf("| %-3d | %-20s | %-12s | %-30s |\n",
                   i + 1,
                   addressbook->contact_details[i].Name,
                   addressbook->contact_details[i].Mobile_number,
                   addressbook->contact_details[i].Mail_ID);
            printf("-----------------------------------------------------------------\n");
            return 1;
        }
    }
    printf("No contact found with that name!\n");
    return 0;
}

int search_phone(AddressBook *addressbook) {
    char phone[11];
    printf("Enter phone to search: ");
    scanf("%10s", phone);

    for (int i = 0; i < addressbook->contact_count; i++) {
        if (strcmp(addressbook->contact_details[i].Mobile_number, phone) == 0) {
            printf("\nResult:\n");
            printf("-----------------------------------------------------------------\n");
            printf("| %-3s | %-20s | %-12s | %-30s |\n",
                   "No", "Name", "Phone", "Email");
            printf("-----------------------------------------------------------------\n");
            printf("| %-3d | %-20s | %-12s | %-30s |\n",
                   i + 1,
                   addressbook->contact_details[i].Name,
                   addressbook->contact_details[i].Mobile_number,
                   addressbook->contact_details[i].Mail_ID);
            printf("-----------------------------------------------------------------\n");
            return 1;
        }
    }
    printf("No contact found with that phone!\n");
    return 0;
}

int search_email(AddressBook *addressbook) {
    char email[35];
    printf("Enter email to search: ");
    scanf("%34s", email);

    for (int i = 0; i < addressbook->contact_count; i++) {
        if (strcmp(addressbook->contact_details[i].Mail_ID, email) == 0) {
            printf("\nResult:\n");
            printf("-----------------------------------------------------------------\n");
            printf("| %-3s | %-20s | %-12s | %-30s |\n",
                   "No", "Name", "Phone", "Email");
            printf("-----------------------------------------------------------------\n");
            printf("| %-3d | %-20s | %-12s | %-30s |\n",
                   i + 1,
                   addressbook->contact_details[i].Name,
                   addressbook->contact_details[i].Mobile_number,
                   addressbook->contact_details[i].Mail_ID);
            printf("-----------------------------------------------------------------\n");
            return 1;
        }
    }
    printf("No contact found with that email!\n");
    return 0;
}

int search_contacts(AddressBook *addressbook) {
    int choice;
    printf("\nSearch by:\n1. Name\n2. Phone\n3. Email\nEnter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: return search_name(addressbook);
        case 2: return search_phone(addressbook);
        case 3: return search_email(addressbook);
        default: printf("Invalid choice!\n"); return 0;
    }
}

/* File Save */
int save_contacts(AddressBook *addressbook) {
    FILE *fp = fopen("contacts.txt", "w");
    if (!fp) {
        printf("Error saving contacts!\n");
        return 0;
    }

    for (int i = 0; i < addressbook->contact_count; i++) {
        fprintf(fp, "%s %s %s\n",
                addressbook->contact_details[i].Name,
                addressbook->contact_details[i].Mobile_number,
                addressbook->contact_details[i].Mail_ID);
    }
    fclose(fp);
    printf("Contacts saved to contacts.txt\n");
    return 1;
}

