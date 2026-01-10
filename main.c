#include <stdio.h>
#include "student.h"


/**
 * @brief Point d'entrée principal du programme.
 * 
 * Initialise la base de données, charge les données existantes
 * et affiche un menu interactif pour gérer les étudiants.
 * 
 * @return 0 si le programme s'exécute correctement.
 */
int main() {
    list_student *my_db = creat_list_student();

    load_database(my_db, "my_data.db");

    int choice = 0;
    char cne_buffer[20];

    do {
        printf("\n=== MINI DATABASE MENU ===\n");
        printf("1. Ajouter un etudiant\n");
        printf("2. Afficher tout\n");
        printf("3. Supprimer un etudiant\n");
        printf("4. modifier les donnees d'etudiant\n");
        printf("5. Sauvegarder et Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                student *s = creat_student();
                printf("Entrez Nom: ");
                scanf("%s", s->nom);
                printf("Entrez Prenom: ");
                scanf("%s", s->prenom);
                printf("Entrez Date de naissance (jour mois annee): ");
                scanf("%d %d %d", &s->date_naissance.jour, &s->date_naissance.mois, &s->date_naissance.annee);
                printf("Entrez CNE: ");
                scanf("%s", s->CNE);
                printf("Entrez Filiere: ");
                scanf("%s", s->filiere);
                printf("Entrez Moyenne: ");
                scanf("%f", &s->moyenne);
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
                printf("\nEntrez le CNE de l'etudiant a modifiee : ");
                scanf("%s", cne_buffer);
                modify_student(my_db, cne_buffer);
                break;
            case 5:
                save_database(my_db, "my_data.db");
                printf("Donnees sauvegardees. Au revoir!\n");
                break;
        default:
            printf("Choix invalide!\n");
        }
    } while (choice != 5);

    return 0;
}