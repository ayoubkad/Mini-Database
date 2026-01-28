#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "student.h"
#include "arbres_binaire.h"

ab_node_student *create_ab_node(student *student) {
    if (student == NULL) return NULL;

    ab_node_student *node = (ab_node_student *) malloc(sizeof(ab_node_student));
    if (node == NULL) {
        printf("Erreur d'allocation memoire!\n");
        return NULL;
    }

    node->std = student;

    node->filsd = NULL;
    node->filsg = NULL;

    return node;
}

ab_racine_student *create_ab_racine() {
    ab_racine_student *racine = (ab_racine_student *) malloc(sizeof(ab_racine_student));
    if (racine == NULL) {
        printf("Erreur d'allocation memoire!\n");
        return NULL;
    }
    racine->racine = NULL;
    return racine;
}

ab_node_student *insert_recursive_worker(ab_node_student *currant, ab_node_student *new_node) {
    if (currant == NULL) return new_node;

    if (new_node->std->moyenne < currant->std->moyenne) {
        currant->filsg = insert_recursive_worker(currant->filsg, new_node);
    } else {
        currant->filsd = insert_recursive_worker(currant->filsd, new_node);
    }
    return currant;
}

void insert_bst(ab_racine_student *racine, ab_node_student *node) {
    if (racine == NULL || node == NULL) return;

    racine->racine = insert_recursive_worker(racine->racine, node);
}

void free_bst_nodes(ab_node_student *node) {
    if (node == NULL) return;

    free_bst_nodes(node->filsg);
    free_bst_nodes(node->filsd);

    free(node);
}
