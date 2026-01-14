#include <stdio.h>
#include <string.h>
#include "student.h"
// #include <windows.h> // pour les Accents

/**
 * @brief Point d'entrée principal du programme.
 * 
 * Initialise la base de données, charge les données existantes
 * et affiche un menu interactif pour gérer les étudiants.
 * 
 * @return 0 si le programme s'exécute correctement.
 */
int main() {
    // SetConsoleOutputCP(65001); // pour les Accents
    list_student *my_db = creat_list_student();

    load_database(my_db, "my_data.db");

    int choice = 0;
    char cne_buffer[15];

    do {
        printf("\n=== MINI DATABASE MENU ===\n");
        printf("1. Ajouter un etudiant\n");
        printf("2. Afficher tout\n");
        printf("3. Supprimer un etudiant\n");
        printf("4. Modifier les donnees d'etudiant\n");
        printf("5. Rechercher un etudiant par CNE\n");
        printf("6. Trier les etudiants par moyenne\n");
        printf("7. Supprimer tous les etudiants\n");
        printf("8. Sauvegarder et Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        switch (choice) {
            case 1: {
                student *s = creat_student();
                printf("Entrez Nom: ");
                fgets(s->nom, 20, stdin);
                s->nom[strcspn(s->nom, "\n")] = 0;
                printf("Entrez Prenom: ");
                fgets(s->prenom, 20, stdin);
                s->prenom[strcspn(s->prenom, "\n")] = 0;
                printf("Entrez Date de naissance (jour mois annee): ");
                scanf("%d %d %d", &s->date_naissance.jour, &s->date_naissance.mois,
                      &s->date_naissance.annee);
                while (getchar() != '\n');
                printf("Entrez CNE: ");
                fgets(s->CNE, 15, stdin);
                s->CNE[strcspn(s->CNE, "\n")] = 0;
                printf("Entrez Filiere: ");
                fgets(s->filiere, 30, stdin);
                s->filiere[strcspn(s->filiere, "\n")] = 0;
                printf("Entre Moyenne (doit etre entre 0 a 20): ");
                scanf("%f", &s->moyenne);
                while (s->moyenne > 20 || s->moyenne < 0) {
                    printf("Moyenne doit etre entre 0 a 20!!!\n");
                    printf("Entre Moyenne: ");
                    scanf("%f", &s->moyenne);
                    while (getchar() != '\n');
                }
                add_student(my_db, s);
                break;
            }
            case 2:
                display_all_student(my_db);
                break;
            case 3:
                printf("\nEntrez le CNE de l'etudiant a supprimer : ");
                fgets(cne_buffer, 15, stdin);
                cne_buffer[strcspn(cne_buffer, "\n")] = 0;
                delete_student(my_db, cne_buffer);
                break;
            case 4:
                printf("\nEntrez le CNE de l'etudiant a modifier : ");
                fgets(cne_buffer, 15, stdin);
                cne_buffer[strcspn(cne_buffer, "\n")] = 0;
                modify_student(my_db, cne_buffer);
                break;

            case 5:
                printf("\nEntrez le CNE de l'etudiant a rechercher : ");
                fgets(cne_buffer, 15, stdin);
                cne_buffer[strcspn(cne_buffer, "\n")] = 0;
                search_student_by_cne(my_db, cne_buffer);
                break;
            case 6:
                sort_students_by_grade(my_db);
                break;
            case 7:
                printf("\nATTENTION: Cette action supprimera tous les etudiants!\n");
                printf("Etes-vous sur? (1=Oui, 0=Non): ");
                int confirm;
                scanf("%d", &confirm);
                while (getchar() != '\n');
                if (confirm == 1) {
                    delete_all_students(my_db);
                } else {
                    printf("Operation annulee.\n");
                }
                break;
            case 8:
                save_database(my_db, "my_data.db");
                printf("Donnees sauvegardees. Au revoir!\n");
                break;
            default:
                printf("Choix invalide!\n");
        }
    } while (choice != 8);

    return 0;
}
