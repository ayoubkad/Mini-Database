#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h" // تأكد أن هذا الملف موجود

int main() {
    list_student *my_db = creat_list_student();
    int choice = 0;
    char cne_buffer[20];

    do {
        printf("\n=== MINI DATABASE MENU ===\n");
        printf("1. Ajouter un etudiant (Add)\n");
        printf("2. Afficher tout (Display)\n");
        printf("3. Supprimer un etudiant (Delete)\n");
        printf("4. Quitter (Exit)\n");
        printf("Votre choix: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: {
                student *s = creat_student();
                printf("Entrez Nom: ");
                scanf("%s", s->nom);
                printf("Entrez Prenom: ");
                scanf("%s", s->prenom);
                printf("Entrez Age: ");
                scanf("%d", &s->age);
                printf("Entrez CNE: ");
                scanf("%s", s->CNE);

                add_student(my_db, s);
                break;
            }
            case 2:
                display_all_student(my_db);
                break;
            case 3:
                printf("\nEntrez le CNE de l'etudiant a supprimer : ");
                scanf("%s", cne_buffer);
                delete_student(my_db, cne_buffer);
                break;
            case 4:
                save_database(my_db, "my_data.db");
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide!\n");
        }

    } while (choice != 4);

    return 0;
}