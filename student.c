#include <stdlib.h>
#include "student.h"
#include <string.h>
#include <stdio.h>

/**
 * @brief Crée et initialise une liste d'étudiants vide.
 * @return Un pointeur vers la nouvelle liste d'étudiants.
 */
list_student *creat_list_student() {
    list_student *l = (list_student *) malloc(sizeof(list_student));
    if (l == NULL) {
        exit(1);
    }
    l->tete = NULL;
    l->queues = NULL;
    return l;
}

/**
 * @brief Crée et initialise un nouvel étudiant.
 * 
 * Alloue de la mémoire pour une structure student et initialise
 * ses champs (age à 0, chaînes vides, next à NULL).
 * 
 * @return Un pointeur vers le nouvel étudiant créé.
 */
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

/**
 * @brief Ajoute un étudiant à la fin de la liste.
 * 
 * @param list Pointeur vers la liste d'étudiants.
 * @param new_student Pointeur vers l'étudiant à ajouter.
 */
void add_student(list_student *list, student *new_student) {
    if (list->tete == NULL) {
        list->tete = new_student;
        list->queues = new_student;
    } else {
        list->queues->next = new_student;
        list->queues = new_student;
    }
}

/**
 * @brief Affiche les informations de tous les étudiants de la liste.
 * 
 * Parcourt la liste et affiche le nom, prénom, CNE et âge de chaque étudiant.
 * 
 * @param list_student Pointeur vers la liste d'étudiants à afficher.
 */
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

/**
 * @brief Supprime un étudiant de la liste en utilisant son CNE.
 * 
 * Recherche un étudiant avec le CNE donné et le retire de la liste
 * chaînée s'il est trouvé. Libère la mémoire associée.
 * 
 * @param list Pointeur vers la liste d'étudiants.
 * @param cne_to_delete Chaîne de caractères représentant le CNE de l'étudiant à supprimer.
 */
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

/**
 * @brief Sauvegarde la liste des étudiants dans un fichier binaire.
 * 
 * Parcourt la liste et écrit chaque structure student dans le fichier spécifié.
 * 
 * @param list Pointeur vers la liste d'étudiants à sauvegarder.
 * @param filename Nom du fichier de destination.
 */
void save_database(list_student *list, char *filename) {
    FILE *pFile = fopen(filename, "wb");
    student *suivant = list->tete;
    if (pFile == NULL) {
        printf("Impossible d'ouverture a ce fichier %s\n", filename);
        exit(1);
    }

    while (suivant != NULL) {
        fwrite(suivant, sizeof(student), 1, pFile);
        suivant = suivant->next;
    }
    fclose(pFile);
}

/**
 * @brief Charge tous les étudiants depuis un fichier binaire.
 * 
 * Lit les structures student depuis le fichier et les ajoute à la liste.
 * 
 * @param list Pointeur vers la liste d'étudiants (doit être initialisée).
 * @param filename Nom du fichier source.
 */
void load_database(list_student *list, char *filename) {
    // Ouvrir le fichier en mode lecture binaire
    FILE *pFile = fopen(filename, "rb");

    if (pFile == NULL) {
        printf("Impossible d'ouverture a ce fichier %s\n", filename);
        return;
    }

    student temp; // Structure temporaire pour la lecture

    // Lire chaque étudiant du fichier et l'ajouter à la liste
    while (fread(&temp, sizeof(student), 1, pFile) == 1) {
        // Allouer de la mémoire pour le nouvel étudiant
        student *new_student = malloc(sizeof(student));
        *new_student = temp; // Copier les données
        new_student->next = NULL; // Réinitialiser le pointeur next
        add_student(list, new_student); // Ajouter à la liste
    }

    fclose(pFile); // Fermer le fichier
    printf("Donnees chargees avec succes !\n");
}