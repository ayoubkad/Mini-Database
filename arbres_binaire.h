#ifndef MINI_DATABASE_ARBRES_BINAIRE_H
#define MINI_DATABASE_ARBRES_BINAIRE_H
#include "undo_stack.h"

// structure de node d'arbre
typedef struct ab_node_student {
    student *std;
    struct ab_node_student *filsg;
    struct ab_node_student *filsd;
} ab_node_student;

// structure de racine d'arbre
typedef struct ab_racine_student {
    ab_node_student *racine;
} ab_racine_student;

ab_node_student *create_ab_node(student *student);
void insert_bst(ab_racine_student *racine, ab_node_student *node);

ab_racine_student *create_ab_racine();

void afficher_arbres_trie(ab_racine_student *racine);

void free_bst_nodes(ab_node_student *node);
#endif //MINI_DATABASE_ARBRES_BINAIRE_H
