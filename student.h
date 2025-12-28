#ifndef MINI_DATABASE_STUDENT_H
#define MINI_DATABASE_STUDENT_H

#endif //MINI_DATABASE_STUDENT_H

typedef struct student {
    char nom[20];
    char prenom[20];
    int age;
    char CNE[10];
    struct student *next;
} student;

typedef struct ListStudent {
    student *tete;
    student *queues;
} list_student;

list_student *creat_list_student(); // Crée et initialise une liste d'étudiants vide.
student *creat_student(); // Crée et initialise un nouvel étudiant.
void add_student(list_student *list, student *new_student); // Ajoute un étudiant à la fin de la liste.
void display_all_student(list_student *list_student); // Affiche les informations de tous les étudiants de la liste.
void delete_student(list_student *list,char *cne_to_delete); // Supprime un étudiant de la liste en utilisant son CNE.
void save_database(list_student *list, char *filename); // Sauvegarde la liste des étudiants dans un fichier.
void load_database(list_student *list, char *filename); // Charge la liste des étudiants à partir d'un fichier.