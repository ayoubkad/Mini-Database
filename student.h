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

list_student *creat_list_student(); // cette fonction pour cree un liste de etudiant.
student *creat_student(); // pour cree un etudiant.
void add_student(list_student *list, student *new_student);
void display_all_student(list_student *list_student);
void delete_student(list_student *list,char *cne_to_delete);
void save_database(list_student *list, char *filename);