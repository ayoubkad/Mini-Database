#include <stdlib.h>
#include "student.h"
#include <string.h>
#include <stdio.h>

list_student *creat_list_student() {
    list_student *l = (list_student *) malloc(sizeof(list_student));
    if (l == NULL) {
        exit(1);
    }
    l->tete = NULL;
    l->queues = NULL;
    return l;
}

student *creat_student() {
    student *s = (student *) malloc(sizeof(student));
    if (s == NULL) {
        exit(1);
    }
    s->age = 0;
    s->next = NULL;
    strcpy(s->CNE, "\0");
    strcpy(s->nom, "\0");
    strcpy(s->prenom, "\0");
    return s;
}

void add_student(list_student *list, student *new_student) {
    if (list->tete == NULL) {
        list->tete = new_student;
        list->queues = new_student;
    } else {
        list->queues->next = new_student;
        list->queues = new_student;
    }
}

void display_all_student(list_student *list_student) {
    int compte = 1;
    student *courent = list_student->tete;
    while (courent != NULL) {
        printf("\n -------les information d'etudiant %d-------  \n", compte);
        printf("Nom : %s\n", courent->nom);
        printf("Prenom : %s\n", courent->prenom);
        printf("CNE : %s\n", courent->CNE);
        printf("Age : %d\n", courent->age);
        compte++;
        courent = courent->next;
    }
}

void delete_student(list_student *list, char *cne_to_delete) {
    if (list == NULL || list->tete == NULL) {
        printf("La liste est vide ou n'existe pas.\n");
        return;
    }

    student *current = list->tete;
    student *previous = NULL;

    if (strcmp(current->CNE, cne_to_delete) == 0) {
        student *temp = list->tete;

        list->tete = list->tete->next;

        if (list->tete == NULL) {
            list->queues = NULL;
        }

        free(temp);
        printf("Etudiant supprime avec succes (Head).\n");
        return;
    }

    while (current != NULL && strcmp(current->CNE, cne_to_delete) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Etudiant avec CNE %s non trouve.\n", cne_to_delete);
        return;
    }


    previous->next = current->next;

    if (current == list->queues) {
        list->queues = previous;
    }

    free(current);
    printf("Etudiant supprime avec succes.\n");
}

void save_database(list_student *list, char *filename) {
    FILE *pFile = fopen(filename, "wb");
    student *suivant = list->tete;
    if (pFile == NULL) {
        printf("Impossible d'ouverture a ce fichier %s\n", filename);
        exit(1);
    }

    while (suivant != NULL) {
        fwrite(suivant, sizeof(student),1, pFile);
        suivant = suivant->next;
    }
    fclose(pFile);
}