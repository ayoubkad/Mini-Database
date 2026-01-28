#ifndef MINI_DATABASE_STUDENT_H
#define MINI_DATABASE_STUDENT_H

typedef struct hash_table hash_table;

typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct student {
    char nom[20];
    char prenom[20];
    Date date_naissance;
    char CNE[15];
    char filiere[30];
    float moyenne;
    struct student *next;
} student;

typedef struct ListStudent {
    student *tete;
    student *queues;
} list_student;

list_student *creat_list_student(); // Crée et initialise une liste d'étudiants vide.

student *creat_student(); // Crée et initialise un nouvel étudiant.

void display_all_student(list_student *list_student); // Affiche les informations de tous les étudiants de la liste.

void display_student_cne(list_student *list_student, char *cne);

void save_database(list_student *list, char *filename); // Sauvegarde la liste des étudiants dans un fichier.


void load_database(list_student *list, char *filename); // Charge la liste des étudiants à partir d'un fichier.

void populate_hash_table(hash_table *ht, list_student *list); // Remplit la table de hachage avec les étudiants de la liste.

void search_student_by_cne(hash_table *ht, const char *cne);

void delete_all_students(hash_table *ht, list_student *list);

void display_student_arbre(student *student);

#endif //MINI_DATABASE_STUDENT_H
