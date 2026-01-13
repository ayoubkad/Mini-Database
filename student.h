#ifndef MINI_DATABASE_STUDENT_H
#define MINI_DATABASE_STUDENT_H

#endif //MINI_DATABASE_STUDENT_H
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct student {
    char nom[20];
    char prenom[20];
    Date date_naissance;
    char CNE[10];
    char filiere[30];
    float moyenne;
    struct student *next;
} student;

typedef struct {
    char nom[20];
    char prenom[20];
    Date date_naissance;
    char CNE[10];
    char filiere[30];
    float moyenne;
} student_data;

typedef struct ListStudent {
    student *tete;
    student *queues;
} list_student;

list_student *creat_list_student(); // Crée et initialise une liste d'étudiants vide.
student *creat_student(); // Crée et initialise un nouvel étudiant.
void add_student(list_student *list, student *new_student); // Ajoute un étudiant à la fin de la liste.
void display_all_student(list_student *list_student); // Affiche les informations de tous les étudiants de la liste.
void delete_student(list_student *list, char *cne_to_delete); // Supprime un étudiant de la liste en utilisant son CNE.
void save_database(list_student *list, char *filename); // Sauvegarde la liste des étudiants dans un fichier.
void load_database(list_student *list, char *filename); // Charge la liste des étudiants à partir d'un fichier.
void search_student_by_cne(list_student *list, char *cne);
void delete_all_students(list_student *list);
void modify_student(list_student *list, const char *cne_to_modify);
void sort_students_by_grade(list_student *list);


// Helper functions for sorting
student *get_middle(student *head);
student *merge_sorted_lists(student *left, student *right);
student *merge_sort_recursive(student *head);
