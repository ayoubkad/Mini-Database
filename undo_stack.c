#include "undo_stack.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

UndoStack *create_undo_stack() {
    UndoStack *stack = (UndoStack *) malloc(sizeof(UndoStack));
    if (stack == NULL) {
        return NULL;
    }
    stack->top = NULL;
    return stack;
}

void push_undo(UndoStack *stack, OperationType type, student *s) {
    if (stack == NULL) return;
    UndoNode *new_node = (UndoNode *) malloc(sizeof(UndoNode));
    if (new_node == NULL) {
        printf("Erreur d'allocation memoire pour UndoStack\n");
        return;
    }
    new_node->type = type;
    if (s != NULL) {
        strcpy(new_node->backup_data.nom, s->nom);
        strcpy(new_node->backup_data.prenom, s->prenom);
        strcpy(new_node->backup_data.CNE, s->CNE);
        strcpy(new_node->backup_data.filiere, s->filiere);
        new_node->backup_data.moyenne = s->moyenne;

        new_node->backup_data.date_naissance = s->date_naissance;
    }
    new_node->next = stack->top;
    stack->top = new_node;
}

void execute_undo(list_student *list, UndoStack *stack) {
    if (stack == NULL || stack->top == NULL) {
        printf("Aucun changement a annuler.\n");
        return;
    }
    UndoNode *node = stack->top;
    stack->top = node->next;
    switch (node->type) {
        case ADD_OPERATION: delete_student(list, node->backup_data.CNE, NULL);
            break;
        case DELETE_OPERATION: {
            student *s = (student *) malloc(sizeof(student));
            strcpy(s->CNE, node->backup_data.CNE);
            strcpy(s->filiere, node->backup_data.filiere);
            s->moyenne = node->backup_data.moyenne;
            strcpy(s->nom, node->backup_data.nom);
            strcpy(s->prenom, node->backup_data.prenom);
            s->moyenne = node->backup_data.moyenne;
            s->date_naissance = node->backup_data.date_naissance;
            s->next = NULL;
            add_student(list, s, NULL);
        }
        break;
        case MODIFY_OPERATION: {
            student *courant = list->tete;
            while (courant != NULL && strcmp(courant->CNE, node->backup_data.CNE) != 0) {
                courant = courant->next;
            }
            if (courant == NULL) {
                printf("Erreur: Impossible d'annuler, etudiant introuvable.\n");
            } else {
                strcpy(courant->CNE, node->backup_data.CNE);
                strcpy(courant->filiere, node->backup_data.filiere);
                courant->moyenne = node->backup_data.moyenne;
                strcpy(courant->nom, node->backup_data.nom);
                strcpy(courant->prenom, node->backup_data.prenom);
                courant->moyenne = node->backup_data.moyenne;
                courant->date_naissance = node->backup_data.date_naissance;
            }
        }
        break;
    }
    free(node);
}
void free_undo_stack(UndoStack *stack) {
    if (stack == NULL) {
        return;
    }
    UndoNode *node = stack->top;
    while (node != NULL) {
        UndoNode *node_current = node;
        node = node->next;
        free(node_current);
    }
    free(stack);
}

void display_undo_history(UndoStack *stack) {
    if (stack == NULL || stack->top == NULL) {
        printf("\n--- Historique Vide ---\n");
        return;
    }

    printf("\n--- Historique des actions (Recents en premier) ---\n");
    UndoNode *current = stack->top;
    int i = 1;
    while (current != NULL) {
        printf("%d. ", i);
        switch(current->type) {
            case ADD_OPERATION:
                printf("[AJOUT] Etudiant: %s (CNE: %s)\n",
                       current->backup_data.nom, current->backup_data.CNE);
                break;
            case DELETE_OPERATION:
                printf("[SUPPRESSION] Etudiant: %s (CNE: %s)\n",
                       current->backup_data.nom, current->backup_data.CNE);
                break;
            case MODIFY_OPERATION:
                printf("[MODIFICATION] Etudiant: %s (CNE: %s)\n",
                       current->backup_data.nom, current->backup_data.CNE);
                break;
        }
        current = current->next;
        i++;
    }
    printf("-----------------------------------------------\n");
}