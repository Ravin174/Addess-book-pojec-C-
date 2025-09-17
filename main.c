#include <stdio.h>
#include <stdlib.h>
#include "contact.h"

int main() {
    AddressBook addressbook;
    int choice;
    int running = 1;

    init_addressbook(&addressbook);

    while (running) {
        printf("\n===== Address Book =====\n");
        printf("1. Create Contact\n");
        printf("2. List Contacts\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Search Contacts\n");
        printf("6. Save Contacts\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_contact(&addressbook);
                break;
            case 2:
                list_contacts(&addressbook);
                break;
            case 3:
                edit_contact(&addressbook);
                break;
            case 4:
                delete_contact(&addressbook);
                break;
            case 5:
                search_contacts(&addressbook);
                break;
            case 6:
                save_contacts(&addressbook);
                break;
            case 7:
                running = 0;
                printf("Exiting Address Book. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
