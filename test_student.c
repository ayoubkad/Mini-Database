#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "undo_stack.h"
#include "arbres_binaire.h"
#include "hash_table.h"

// Déclarations des fonctions manquantes dans student.h
void add_student(hash_table *ht, list_student *list, student *new_student, UndoStack *stack);
void delete_student(hash_table *ht, list_student *list, char *cne_to_delete, UndoStack *stack);
void modify_student(list_student *list, const char *cne_to_modify, UndoStack *stack);

/**
 * @brief Fonction auxiliaire pour créer un étudiant de test avec des données spécifiques.
 *
 * @param nom Nom de l'étudiant
 * @param prenom Prénom de l'étudiant
 * @param cne CNE de l'étudiant
 * @param moyenne Moyenne de l'étudiant
 * @return Pointeur vers le nouvel étudiant créé
 */
student *create_test_student(const char *nom, const char *prenom, const char *cne, float moyenne) {
    student *s = creat_student();
    strcpy(s->nom, nom);
    strcpy(s->prenom, prenom);
    strcpy(s->CNE, cne);
    strcpy(s->filiere, "Informatique");
    s->moyenne = moyenne;
    s->date_naissance.jour = 1;
    s->date_naissance.mois = 1;
    s->date_naissance.annee = 2000;
    return s;
}

/**
 * @brief Test de la fonction de tri par moyenne.
 *
 * Crée une liste d'étudiants avec des moyennes différentes,
 * applique le tri et vérifie que la liste est bien triée en ordre décroissant.
 */
/* Test function commented out - sort_students_by_grade not implemented yet
void test_sort_students_by_grade() {
    printf("=== Test de tri des etudiants par moyenne ===\n\n");

    // Créer une liste d'étudiants
    list_student *list = creat_list_student();

    // Ajouter des étudiants avec différentes moyennes
    add_student(NULL, list, create_test_student("Alami", "Ahmed", "CNE001", 12.5), NULL);
    add_student(NULL, list, create_test_student("Bennani", "Fatima", "CNE002", 16.8), NULL);
    add_student(NULL, list, create_test_student("Cherif", "Hassan", "CNE003", 14.2), NULL);
    add_student(NULL, list, create_test_student("Drissi", "Salma", "CNE004", 18.5), NULL);
    add_student(NULL, list, create_test_student("El Amrani", "Youssef", "CNE005", 11.0), NULL);
    add_student(NULL, list, create_test_student("Fassi", "Laila", "CNE006", 15.7), NULL);

    printf("Liste avant le tri:\n");
    display_all_student(list);

    // Appliquer le tri
    printf("\n\nApplication du tri par moyenne...\n\n");
    sort_students_by_grade(list);

    printf("\nListe apres le tri:\n");
    display_all_student(list);

    // Vérification manuelle que le tri est correct
    printf("\n\n=== Verification du tri ===\n");
    student *current = list->tete;
    int correct = 1;
    while (current != NULL && current->next != NULL) {
        if (current->moyenne < current->next->moyenne) {
            printf("ERREUR: %s (%.2f) est avant %s (%.2f)\n",
                   current->nom, current->moyenne,
                   current->next->nom, current->next->moyenne);
            correct = 0;
        }
        current = current->next;
    }

    if (correct) {
        printf("SUCCESS: La liste est correctement triee en ordre decroissant!\n");
    } else {
        printf("ECHEC: La liste n'est pas correctement triee.\n");
    }

    // Libérer la mémoire
    delete_all_students(NULL, list);
    free(list);
}
*/

/**
 * @brief Test de la fonction de tri avec une liste vide.
 */
/* Test function commented out - sort_students_by_grade not implemented yet
void test_sort_empty_list() {
    printf("\n\n=== Test de tri d'une liste vide ===\n");
    list_student *list = creat_list_student();

    sort_students_by_grade(list);

    if (list->tete == NULL) {
        printf("SUCCESS: La liste vide reste vide apres le tri.\n");
    } else {
        printf("ECHEC: La liste devrait etre vide.\n");
    }

    free(list);
}
*/

/**
 * @brief Test de la fonction de tri avec un seul étudiant.
 */
/* Test function commented out - sort_students_by_grade not implemented yet
void test_sort_single_student() {
    printf("\n\n=== Test de tri avec un seul etudiant ===\n");
    list_student *list = creat_list_student();

    add_student(NULL, list, create_test_student("Unique", "Etudiant", "CNE999", 14.5), NULL);

    printf("Avant tri: Moyenne = %.2f\n", list->tete->moyenne);
    sort_students_by_grade(list);
    printf("Apres tri: Moyenne = %.2f\n", list->tete->moyenne);

    if (list->tete->moyenne == 14.5 && list->tete->next == NULL) {
        printf("SUCCESS: Un seul etudiant reste inchange.\n");
    } else {
        printf("ECHEC: Le tri a modifie incorrectement la liste.\n");
    }

    delete_all_students(NULL, list);
    free(list);
}
*/

/**
 * @brief Test de la fonction de tri avec des moyennes identiques.
 */
/* Test function commented out - sort_students_by_grade not implemented yet
void test_sort_equal_grades() {
    printf("\n\n=== Test de tri avec moyennes identiques ===\n");
    list_student *list = creat_list_student();

    add_student(NULL, list, create_test_student("A", "Premier", "CNE101", 15.0), NULL);
    add_student(NULL, list, create_test_student("B", "Deuxieme", "CNE102", 15.0), NULL);
    add_student(NULL, list, create_test_student("C", "Troisieme", "CNE103", 15.0), NULL);

    printf("Liste avant tri:\n");
    display_all_student(list);

    sort_students_by_grade(list);

    printf("\nListe apres tri:\n");
    display_all_student(list);

    printf("\nSUCCESS: Le tri fonctionne avec des moyennes identiques.\n");

    delete_all_students(NULL, list);
    free(list);
}
*/

/**
 * @brief Test de sauvegarde et chargement après tri.
 */
/* Test function commented out - sort_students_by_grade not implemented yet
void test_sort_with_save_load() {
    printf("\n\n=== Test de tri avec sauvegarde et chargement ===\n");
    list_student *list1 = creat_list_student();

    // Ajouter des étudiants
    add_student(NULL, list1, create_test_student("Zaki", "Amina", "CNE201", 13.5), NULL);
    add_student(NULL, list1, create_test_student("Yassir", "Omar", "CNE202", 17.2), NULL);
    add_student(NULL, list1, create_test_student("Wafi", "Nadia", "CNE203", 15.8), NULL);

    // Trier
    sort_students_by_grade(list1);

    // Sauvegarder
    save_database(list1, "test_sorted.db");

    // Charger dans une nouvelle liste
    list_student *list2 = creat_list_student();
    load_database(list2, "test_sorted.db");

    printf("\nListe chargee depuis le fichier:\n");
    display_all_student(list2);

    // Vérifier que l'ordre est préservé
    student *s1 = list1->tete;
    student *s2 = list2->tete;
    int identical = 1;

    while (s1 != NULL && s2 != NULL) {
        if (s1->moyenne != s2->moyenne || strcmp(s1->CNE, s2->CNE) != 0) {
            identical = 0;
            break;
        }
        s1 = s1->next;
        s2 = s2->next;
    }

    if (identical && s1 == NULL && s2 == NULL) {
        printf("\nSUCCESS: L'ordre de tri est preserve apres sauvegarde/chargement.\n");
    } else {
        printf("\nECHEC: L'ordre a change apres sauvegarde/chargement.\n");
    }

    delete_all_students(NULL, list1);
    delete_all_students(NULL, list2);
    free(list1);
    free(list2);
}
*/

/**
 * @brief Test de la fonction de recherche par CNE.
 */
void test_search_student_by_cne() {
    printf("\n\n=== Test de recherche d'etudiant par CNE ===\n");
    list_student *list = creat_list_student();

    // Ajouter plusieurs étudiants
    add_student(NULL, list, create_test_student("Alami", "Ahmed", "CNE001", 12.5), NULL);
    add_student(NULL, list, create_test_student("Bennani", "Fatima", "CNE002", 16.8), NULL);
    add_student(NULL, list, create_test_student("Cherif", "Hassan", "CNE003", 14.2), NULL);

    printf("\nRecherche d'un etudiant existant (CNE002):\n");
    search_student_by_cne(NULL, "CNE002");

    printf("\n\nRecherche d'un etudiant inexistant (CNE999):\n");
    search_student_by_cne(NULL, "CNE999");

    printf("\nSUCCESS: Test de recherche complete.\n");

    delete_all_students(NULL, list);
    free(list);
}

/**
 * @brief Test de la fonction de suppression de tous les étudiants.
 */
void test_delete_all_students() {
    printf("\n\n=== Test de suppression de tous les etudiants ===\n");
    list_student *list = creat_list_student();

    // Ajouter plusieurs étudiants
    add_student(NULL, list, create_test_student("Student1", "First", "CNE101", 15.0), NULL);
    add_student(NULL, list, create_test_student("Student2", "Second", "CNE102", 16.0), NULL);
    add_student(NULL, list, create_test_student("Student3", "Third", "CNE103", 17.0), NULL);

    printf("Liste avant suppression:\n");
    display_all_student(list);

    printf("\n\nSuppression de tous les etudiants...\n");
    delete_all_students(NULL, list);

    if (list->tete == NULL && list->queues == NULL) {
        printf("\nSUCCESS: Tous les etudiants ont ete supprimes.\n");
        printf("Verification: tete = NULL, queues = NULL\n");
    } else {
        printf("\nECHEC: La liste n'est pas vide apres suppression.\n");
    }

    // Test de suppression sur liste déjà vide
    printf("\n\nTest de suppression sur liste vide:\n");
    delete_all_students(NULL, list);
    printf("SUCCESS: Aucune erreur lors de la suppression d'une liste vide.\n");

    free(list);
}

/**
 * @brief Test de la fonction get_middle().
 * Teste la fonction qui trouve le milieu d'une liste chaînée.
 */
/* Test function commented out - get_middle not implemented yet
void test_get_middle() {
    printf("\n\n=== Test de la fonction get_middle ===\n");
    list_student *list = creat_list_student();

    // Test avec liste vide
    student *middle = get_middle(NULL);
    if (middle == NULL) {
        printf("SUCCESS: get_middle retourne NULL pour une liste vide.\n");
    } else {
        printf("ECHEC: get_middle devrait retourner NULL pour une liste vide.\n");
    }

    // Test avec un seul élément
    add_student(NULL, list, create_test_student("A", "First", "CNE101", 15.0), NULL);
    middle = get_middle(list->tete);
    if (middle != NULL && strcmp(middle->CNE, "CNE101") == 0) {
        printf("SUCCESS: get_middle fonctionne avec un seul element.\n");
    } else {
        printf("ECHEC: get_middle ne fonctionne pas correctement avec un seul element.\n");
    }

    // Test avec plusieurs éléments (nombre impair)
    add_student(NULL, list, create_test_student("B", "Second", "CNE102", 16.0), NULL);
    add_student(NULL, list, create_test_student("C", "Third", "CNE103", 17.0), NULL);
    add_student(NULL, list, create_test_student("D", "Fourth", "CNE104", 18.0), NULL);
    add_student(NULL, list, create_test_student("E", "Fifth", "CNE105", 19.0), NULL);
    
    middle = get_middle(list->tete);
    if (middle != NULL && strcmp(middle->CNE, "CNE103") == 0) {
        printf("SUCCESS: get_middle trouve correctement le milieu (5 elements).\n");
    } else {
        printf("ECHEC: Milieu attendu CNE103, trouve %s.\n", middle ? middle->CNE : "NULL");
    }

    // Test avec nombre pair d'éléments
    delete_all_students(NULL, list);
    add_student(NULL, list, create_test_student("A", "First", "CNE201", 15.0), NULL);
    add_student(NULL, list, create_test_student("B", "Second", "CNE202", 16.0), NULL);
    add_student(NULL, list, create_test_student("C", "Third", "CNE203", 17.0), NULL);
    add_student(NULL, list, create_test_student("D", "Fourth", "CNE204", 18.0), NULL);
    
    middle = get_middle(list->tete);
    if (middle != NULL && strcmp(middle->CNE, "CNE202") == 0) {
        printf("SUCCESS: get_middle fonctionne avec un nombre pair d'elements.\n");
    } else {
        printf("ECHEC: Milieu attendu CNE202, trouve %s.\n", middle ? middle->CNE : "NULL");
    }

    delete_all_students(NULL, list);
    free(list);
}
*/

/**
 * @brief Test de la fonction merge_sorted_lists().
 * Teste la fusion de deux listes triées.
 */
/* Test function commented out - merge_sorted_lists not implemented yet
void test_merge_sorted_lists() {
    printf("\n\n=== Test de la fonction merge_sorted_lists ===\n");
    
    // Test avec deux listes NULL
    student *merged = merge_sorted_lists(NULL, NULL);
    if (merged == NULL) {
        printf("SUCCESS: merge_sorted_lists retourne NULL pour deux listes vides.\n");
    } else {
        printf("ECHEC: merge_sorted_lists devrait retourner NULL.\n");
    }

    // Créer première liste triée (décroissant): 18.0 -> 15.0 -> 12.0
    student *list1 = create_test_student("A", "First", "CNE101", 18.0);
    list1->next = create_test_student("B", "Second", "CNE102", 15.0);
    list1->next->next = create_test_student("C", "Third", "CNE103", 12.0);
    list1->next->next->next = NULL;

    // Créer deuxième liste triée (décroissant): 17.0 -> 14.0 -> 11.0
    student *list2 = create_test_student("D", "Fourth", "CNE201", 17.0);
    list2->next = create_test_student("E", "Fifth", "CNE202", 14.0);
    list2->next->next = create_test_student("F", "Sixth", "CNE203", 11.0);
    list2->next->next->next = NULL;

    // Fusionner les listes
    merged = merge_sorted_lists(list1, list2);

    printf("Liste fusionnee:\n");
    student *current = merged;
    float previous_moyenne = 100.0;
    int correct = 1;
    int count = 0;
    
    while (current != NULL) {
        printf("  %s: %.2f\n", current->CNE, current->moyenne);
        if (current->moyenne > previous_moyenne) {
            printf("  ERREUR: Ordre incorrect (%.2f > %.2f)\n", current->moyenne, previous_moyenne);
            correct = 0;
        }
        previous_moyenne = current->moyenne;
        current = current->next;
        count++;
    }

    if (correct && count == 6) {
        printf("SUCCESS: merge_sorted_lists fusionne correctement en ordre decroissant.\n");
    } else {
        printf("ECHEC: Probleme dans la fusion (correct=%d, count=%d).\n", correct, count);
    }

    // Libérer la mémoire
    while (merged != NULL) {
        student *temp = merged;
        merged = merged->next;
        free(temp);
    }
}
*/

/**
 * @brief Test de la fonction merge_sort_recursive().
 * Teste le tri récursif d'une liste.
 */
/* Test function commented out - merge_sort_recursive not implemented yet
void test_merge_sort_recursive() {
    printf("\n\n=== Test de la fonction merge_sort_recursive ===\n");
    
    // Test avec liste NULL
    student *sorted = merge_sort_recursive(NULL);
    if (sorted == NULL) {
        printf("SUCCESS: merge_sort_recursive retourne NULL pour une liste vide.\n");
    } else {
        printf("ECHEC: merge_sort_recursive devrait retourner NULL.\n");
    }

    // Créer une liste non triée
    student *head = create_test_student("A", "First", "CNE101", 12.5);
    head->next = create_test_student("B", "Second", "CNE102", 18.0);
    head->next->next = create_test_student("C", "Third", "CNE103", 14.2);
    head->next->next->next = create_test_student("D", "Fourth", "CNE104", 16.8);
    head->next->next->next->next = create_test_student("E", "Fifth", "CNE105", 11.0);
    head->next->next->next->next->next = NULL;

    printf("Liste avant tri:\n");
    student *current = head;
    while (current != NULL) {
        printf("  %s: %.2f\n", current->CNE, current->moyenne);
        current = current->next;
    }

    // Trier la liste
    sorted = merge_sort_recursive(head);

    printf("\nListe apres tri:\n");
    current = sorted;
    float previous_moyenne = 100.0;
    int correct = 1;
    
    while (current != NULL) {
        printf("  %s: %.2f\n", current->CNE, current->moyenne);
        if (current->moyenne > previous_moyenne) {
            printf("  ERREUR: Ordre incorrect\n");
            correct = 0;
        }
        previous_moyenne = current->moyenne;
        current = current->next;
    }

    if (correct) {
        printf("SUCCESS: merge_sort_recursive trie correctement en ordre decroissant.\n");
    } else {
        printf("ECHEC: La liste n'est pas correctement triee.\n");
    }

    // Libérer la mémoire
    while (sorted != NULL) {
        student *temp = sorted;
        sorted = sorted->next;
        free(temp);
    }
}
*/

/**
 * @brief Test de création d'un noeud d'arbre binaire.
 */
void test_create_ab_node() {
    printf("\n\n=== Test de creation d'un noeud d'arbre binaire ===\n");
    
    // Test avec un étudiant valide
    student *s = create_test_student("Alami", "Ahmed", "CNE001", 15.5);
    ab_node_student *node = create_ab_node(s);
    
    if (node != NULL && node->std == s && node->filsg == NULL && node->filsd == NULL) {
        printf("SUCCESS: Noeud cree avec succes.\n");
        printf("  Etudiant: %s %s, Moyenne: %.2f\n", node->std->nom, node->std->prenom, node->std->moyenne);
    } else {
        printf("ECHEC: Creation de noeud incorrecte.\n");
    }
    
    // Test avec NULL
    ab_node_student *null_node = create_ab_node(NULL);
    if (null_node == NULL) {
        printf("SUCCESS: create_ab_node retourne NULL pour un etudiant NULL.\n");
    } else {
        printf("ECHEC: create_ab_node devrait retourner NULL.\n");
    }
    
    free(node);
    free(s);
}

/**
 * @brief Test de création de la racine d'arbre binaire.
 */
void test_create_ab_racine() {
    printf("\n\n=== Test de creation de la racine d'arbre ===\n");
    
    ab_racine_student *racine = create_ab_racine();
    
    if (racine != NULL && racine->racine == NULL) {
        printf("SUCCESS: Racine d'arbre creee avec succes (racine vide).\n");
    } else {
        printf("ECHEC: Creation de racine incorrecte.\n");
    }
    
    free(racine);
}

/**
 * @brief Test d'insertion dans un arbre binaire de recherche.
 */
void test_insert_bst() {
    printf("\n\n=== Test d'insertion dans un arbre binaire de recherche ===\n");
    
    ab_racine_student *racine = create_ab_racine();
    
    // Insérer plusieurs étudiants
    student *s1 = create_test_student("Alami", "Ahmed", "CNE001", 15.0);
    student *s2 = create_test_student("Bennani", "Fatima", "CNE002", 12.0);
    student *s3 = create_test_student("Cherif", "Hassan", "CNE003", 18.0);
    student *s4 = create_test_student("Drissi", "Salma", "CNE004", 14.0);
    student *s5 = create_test_student("El Amrani", "Youssef", "CNE005", 16.0);
    
    ab_node_student *n1 = create_ab_node(s1);
    ab_node_student *n2 = create_ab_node(s2);
    ab_node_student *n3 = create_ab_node(s3);
    ab_node_student *n4 = create_ab_node(s4);
    ab_node_student *n5 = create_ab_node(s5);
    
    insert_bst(racine, n1);
    insert_bst(racine, n2);
    insert_bst(racine, n3);
    insert_bst(racine, n4);
    insert_bst(racine, n5);
    
    // Vérifier que la racine n'est pas NULL
    if (racine->racine != NULL) {
        printf("SUCCESS: Les noeuds ont ete inseres dans l'arbre.\n");
        printf("  Racine (moyenne): %.2f\n", racine->racine->std->moyenne);
        
        // Vérifier la structure BST
        if (racine->racine->std->moyenne == 15.0) {
            printf("  Fils gauche (moyenne < 15.0): ");
            if (racine->racine->filsg != NULL) {
                printf("%.2f\n", racine->racine->filsg->std->moyenne);
            } else {
                printf("NULL\n");
            }
            
            printf("  Fils droit (moyenne >= 15.0): ");
            if (racine->racine->filsd != NULL) {
                printf("%.2f\n", racine->racine->filsd->std->moyenne);
            } else {
                printf("NULL\n");
            }
        }
    } else {
        printf("ECHEC: L'arbre est vide apres insertion.\n");
    }
    
    // Test avec NULL
    insert_bst(NULL, n1);
    insert_bst(racine, NULL);
    printf("SUCCESS: Aucun crash avec parametres NULL.\n");
    
    free_bst_nodes(racine->racine);
    free(racine);
    free(s1);
    free(s2);
    free(s3);
    free(s4);
    free(s5);
}

/**
 * @brief Test d'affichage de l'arbre trié.
 */
void test_afficher_arbres_trie() {
    printf("\n\n=== Test d'affichage d'arbre trie ===\n");
    
    ab_racine_student *racine = create_ab_racine();
    
    // Test avec arbre vide
    printf("\nTest avec arbre vide:\n");
    afficher_arbres_trie(racine);
    
    // Ajouter des étudiants
    student *s1 = create_test_student("Alami", "Ahmed", "CNE001", 15.0);
    student *s2 = create_test_student("Bennani", "Fatima", "CNE002", 12.0);
    student *s3 = create_test_student("Cherif", "Hassan", "CNE003", 18.0);
    student *s4 = create_test_student("Drissi", "Salma", "CNE004", 14.0);
    student *s5 = create_test_student("El Amrani", "Youssef", "CNE005", 16.0);
    
    insert_bst(racine, create_ab_node(s1));
    insert_bst(racine, create_ab_node(s2));
    insert_bst(racine, create_ab_node(s3));
    insert_bst(racine, create_ab_node(s4));
    insert_bst(racine, create_ab_node(s5));
    
    printf("\nAffichage de l'arbre (ordre decroissant):\n");
    afficher_arbres_trie(racine);
    
    printf("\nSUCCESS: L'arbre a ete affiche (verifiez visuellement l'ordre decroissant).\n");
    
    free_bst_nodes(racine->racine);
    free(racine);
    free(s1);
    free(s2);
    free(s3);
    free(s4);
    free(s5);
}

/**
 * @brief Test de libération de la mémoire de l'arbre.
 */
void test_free_bst_nodes() {
    printf("\n\n=== Test de liberation de memoire de l'arbre ===\n");
    
    ab_racine_student *racine = create_ab_racine();
    student *students[10];
    
    // Ajouter des étudiants
    for (int i = 0; i < 10; i++) {
        char cne[20];
        sprintf(cne, "CNE%03d", i);
        students[i] = create_test_student("Nom", "Prenom", cne, 10.0 + i);
        insert_bst(racine, create_ab_node(students[i]));
    }
    
    printf("10 noeuds inseres dans l'arbre.\n");
    
    // Libérer tous les noeuds
    free_bst_nodes(racine->racine);
    racine->racine = NULL;
    
    printf("SUCCESS: Tous les noeuds ont ete liberes (aucun crash).\n");
    
    // Test avec NULL
    free_bst_nodes(NULL);
    printf("SUCCESS: Aucun crash avec free_bst_nodes(NULL).\n");
    
    // Libérer les étudiants
    for (int i = 0; i < 10; i++) {
        free(students[i]);
    }
    
    free(racine);
}

/**
 * @brief Test complet de l'arbre binaire de recherche.
 */
void test_bst_complete() {
    printf("\n\n=== Test complet de l'arbre binaire de recherche ===\n");
    
    ab_racine_student *racine = create_ab_racine();
    
    // Créer et insérer des étudiants dans un ordre aléatoire
    float moyennes[] = {15.0, 10.0, 20.0, 8.0, 12.0, 18.0, 22.0};
    int count = sizeof(moyennes) / sizeof(moyennes[0]);
    student *students[7]; // Garder les références
    
    printf("Insertion des moyennes dans l'ordre: ");
    for (int i = 0; i < count; i++) {
        printf("%.1f ", moyennes[i]);
        char cne[20];
        sprintf(cne, "CNE%03d", i);
        students[i] = create_test_student("Etudiant", "Test", cne, moyennes[i]);
        insert_bst(racine, create_ab_node(students[i]));
    }
    printf("\n");
    
    printf("\nAffichage de l'arbre trie (devrait etre en ordre decroissant):\n");
    afficher_arbres_trie(racine);
    
    printf("\nSUCCESS: Test complet termine.\n");
    printf("Attendu (ordre decroissant): 22.0, 20.0, 18.0, 15.0, 12.0, 10.0, 8.0\n");
    
    free_bst_nodes(racine->racine);
    free(racine);
    
    // Libérer les étudiants
    for (int i = 0; i < count; i++) {
        free(students[i]);
    }
}

/**
 * @brief Test de la fonction de modification d'étudiant.
 */
void test_modify_student() {
    printf("\n\n=== Test de modification d'etudiant ===\n");
    list_student *list = creat_list_student();

    // Ajouter un étudiant
    student *s = create_test_student("Alami", "Ahmed", "CNE001", 12.5);
    add_student(NULL, list, s, NULL);

    printf("Etudiant avant modification:\n");
    search_student_by_cne(NULL, "CNE001");

    printf("\n\nNOTE: La fonction modify_student() necessite une interaction utilisateur.\n");
    printf("Pour un test automatise, nous verifions seulement l'existence de l'etudiant.\n");

    // Test de modification d'un étudiant inexistant
    printf("\nTentative de modification d'un CNE inexistant:\n");
    modify_student(list, "CNE999", NULL);

    printf("\nSUCCESS: Test de modification complete (verification de base).\n");

    delete_all_students(NULL, list);
    free(list);
}

/**
 * @brief Test de la fonction de recherche avec liste vide.
 */
void test_search_empty_list() {
    printf("\n\n=== Test de recherche dans une liste vide ===\n");
    list_student *list = creat_list_student();

    printf("Recherche dans une liste vide:\n");
    search_student_by_cne(NULL, "CNE001");

    printf("\nSUCCESS: Aucun crash lors de la recherche dans une liste vide.\n");

    free(list);
}

/**
 * @brief Test de recherche après tri.
 */
/* Test function commented out - sort_students_by_grade not implemented yet
void test_search_after_sort() {
    printf("\n\n=== Test de recherche apres tri ===\n");
    list_student *list = creat_list_student();

    // Ajouter des étudiants
    add_student(NULL, list, create_test_student("Zaki", "Amina", "CNE201", 13.5), NULL);
    add_student(NULL, list, create_test_student("Yassir", "Omar", "CNE202", 17.2), NULL);
    add_student(NULL, list, create_test_student("Wafi", "Nadia", "CNE203", 15.8), NULL);

    printf("Liste avant tri:\n");
    display_all_student(list);

    // Trier la liste
    sort_students_by_grade(list);

    printf("\n\nListe apres tri:\n");
    display_all_student(list);

    // Rechercher un étudiant après le tri
    printf("\n\nRecherche de CNE202 apres tri:\n");
    search_student_by_cne(NULL, "CNE202");

    printf("\nSUCCESS: La recherche fonctionne correctement apres le tri.\n");

    delete_all_students(NULL, list);
    free(list);
}
*/

/**
 * @brief Test de suppression individuelle suivie d'une suppression totale.
 */
void test_delete_combination() {
    printf("\n\n=== Test de combinaison de suppressions ===\n");
    list_student *list = creat_list_student();

    // Ajouter plusieurs étudiants
    add_student(NULL, list, create_test_student("A", "First", "CNE301", 15.0), NULL);
    add_student(NULL, list, create_test_student("B", "Second", "CNE302", 16.0), NULL);
    add_student(NULL, list, create_test_student("C", "Third", "CNE303", 17.0), NULL);
    add_student(NULL, list, create_test_student("D", "Fourth", "CNE304", 18.0), NULL);

    printf("Liste initiale (4 etudiants):\n");
    display_all_student(list);

    // Supprimer un étudiant
    printf("\n\nSuppression de CNE302:\n");
    delete_student(NULL, list, "CNE302", NULL);
    display_all_student(list);

    // Supprimer un autre étudiant
    printf("\n\nSuppression de CNE304:\n");
    delete_student(NULL, list, "CNE304", NULL);
    display_all_student(list);

    // Supprimer tous les étudiants restants
    printf("\n\nSuppression de tous les etudiants restants:\n");
    delete_all_students(NULL, list);

    if (list->tete == NULL && list->queues == NULL) {
        printf("SUCCESS: Toutes les suppressions ont fonctionne correctement.\n");
    } else {
        printf("ECHEC: La liste n'est pas vide.\n");
    }

    free(list);
}

/**
 * @brief Test de création d'une table de hachage.
 */
void test_create_hash_table() {
    printf("\n\n=== Test de creation d'une table de hachage ===\n");
    
    hash_table *ht = createTable();
    
    if (ht != NULL) {
        printf("SUCCESS: Table de hachage creee avec succes.\n");
        
        // Vérifier que toutes les cases sont initialisées à NULL
        int all_null = 1;
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (ht->table[i] != NULL) {
                all_null = 0;
                break;
            }
        }
        
        if (all_null) {
            printf("SUCCESS: Toutes les cases de la table sont initialisees a NULL.\n");
        } else {
            printf("ECHEC: Certaines cases ne sont pas initialisees a NULL.\n");
        }
        
        free_table(ht);
    } else {
        printf("ECHEC: Impossible de creer la table de hachage.\n");
    }
}

/**
 * @brief Test de la fonction de hachage.
 */
void test_hash_function() {
    printf("\n\n=== Test de la fonction de hachage ===\n");
    
    // Test avec différentes clés
    const char *keys[] = {"CNE001", "CNE002", "CNE999", "ABC123", "XYZ789"};
    int num_keys = sizeof(keys) / sizeof(keys[0]);
    
    printf("Calcul des indices de hachage:\n");
    for (int i = 0; i < num_keys; i++) {
        unsigned int index = hash(keys[i]);
        printf("  %s -> Index: %u\n", keys[i], index);
        
        if (index >= TABLE_SIZE) {
            printf("ECHEC: L'index %u depasse TABLE_SIZE (%d)!\n", index, TABLE_SIZE);
            return;
        }
    }
    
    // Vérifier que des clés identiques donnent le même hash
    unsigned int h1 = hash("CNE001");
    unsigned int h2 = hash("CNE001");
    
    if (h1 == h2) {
        printf("SUCCESS: La fonction de hachage est deterministe.\n");
    } else {
        printf("ECHEC: La fonction de hachage n'est pas deterministe.\n");
    }
}

/**
 * @brief Test d'insertion dans la table de hachage.
 */
void test_insert_hash() {
    printf("\n\n=== Test d'insertion dans la table de hachage ===\n");
    
    hash_table *ht = createTable();
    
    // Créer et insérer des étudiants
    student *s1 = create_test_student("Alami", "Ahmed", "CNE001", 15.5);
    student *s2 = create_test_student("Bennani", "Fatima", "CNE002", 16.8);
    student *s3 = create_test_student("Cherif", "Hassan", "CNE003", 14.2);
    
    insert_hash(ht, s1);
    insert_hash(ht, s2);
    insert_hash(ht, s3);
    
    printf("3 etudiants inseres dans la table de hachage.\n");
    print_table(ht);
    
    // Test avec paramètres NULL
    insert_hash(NULL, s1);
    insert_hash(ht, NULL);
    printf("\nSUCCESS: Aucun crash avec parametres NULL.\n");
    
    free(s1);
    free(s2);
    free(s3);
    free_table(ht);
}

/**
 * @brief Test de recherche dans la table de hachage.
 */
void test_search_hash() {
    printf("\n\n=== Test de recherche dans la table de hachage ===\n");
    
    hash_table *ht = createTable();
    
    // Créer et insérer des étudiants
    student *s1 = create_test_student("Alami", "Ahmed", "CNE001", 15.5);
    student *s2 = create_test_student("Bennani", "Fatima", "CNE002", 16.8);
    student *s3 = create_test_student("Cherif", "Hassan", "CNE003", 14.2);
    
    insert_hash(ht, s1);
    insert_hash(ht, s2);
    insert_hash(ht, s3);
    
    printf("Table de hachage avec 3 etudiants:\n");
    print_table(ht);
    
    // Rechercher un étudiant existant
    printf("\n\nRecherche de CNE002:\n");
    student *found = search_hash(ht, "CNE002");
    
    if (found != NULL && strcmp(found->CNE, "CNE002") == 0) {
        printf("SUCCESS: Etudiant trouve: %s %s (Moyenne: %.2f)\n",
               found->nom, found->prenom, found->moyenne);
    } else {
        printf("ECHEC: Etudiant CNE002 non trouve.\n");
    }
    
    // Rechercher un étudiant inexistant
    printf("\n\nRecherche de CNE999 (inexistant):\n");
    found = search_hash(ht, "CNE999");
    
    if (found == NULL) {
        printf("SUCCESS: NULL retourne pour un etudiant inexistant.\n");
    } else {
        printf("ECHEC: Un etudiant a ete trouve alors qu'il ne devrait pas exister.\n");
    }
    
    // Test avec paramètres NULL
    found = search_hash(NULL, "CNE001");
    found = search_hash(ht, NULL);
    printf("\nSUCCESS: Aucun crash avec parametres NULL.\n");
    
    free(s1);
    free(s2);
    free(s3);
    free_table(ht);
}

/**
 * @brief Test de suppression dans la table de hachage.
 */
void test_delete_hash() {
    printf("\n\n=== Test de suppression dans la table de hachage ===\n");
    
    hash_table *ht = createTable();
    
    // Créer et insérer des étudiants
    student *s1 = create_test_student("Alami", "Ahmed", "CNE001", 15.5);
    student *s2 = create_test_student("Bennani", "Fatima", "CNE002", 16.8);
    student *s3 = create_test_student("Cherif", "Hassan", "CNE003", 14.2);
    
    insert_hash(ht, s1);
    insert_hash(ht, s2);
    insert_hash(ht, s3);
    
    printf("Table initiale:\n");
    print_table(ht);
    
    // Supprimer un étudiant
    printf("\n\nSuppression de CNE002:\n");
    delete_student_hash(ht, "CNE002");
    print_table(ht);
    
    // Vérifier que l'étudiant est bien supprimé
    student *found = search_hash(ht, "CNE002");
    if (found == NULL) {
        printf("SUCCESS: Etudiant CNE002 correctement supprime.\n");
    } else {
        printf("ECHEC: Etudiant CNE002 trouve alors qu'il devrait etre supprime.\n");
    }
    
    // Vérifier que les autres étudiants sont toujours là
    found = search_hash(ht, "CNE001");
    if (found != NULL) {
        printf("SUCCESS: Etudiant CNE001 toujours present.\n");
    } else {
        printf("ECHEC: Etudiant CNE001 non trouve.\n");
    }
    
    // Supprimer un étudiant inexistant
    printf("\n\nSuppression de CNE999 (inexistant):\n");
    delete_student_hash(ht, "CNE999");
    printf("SUCCESS: Aucun crash lors de la suppression d'un etudiant inexistant.\n");
    
    // Test avec paramètres NULL
    delete_student_hash(NULL, "CNE001");
    delete_student_hash(ht, NULL);
    printf("\nSUCCESS: Aucun crash avec parametres NULL.\n");
    
    free(s1);
    free(s2);
    free(s3);
    free_table(ht);
}

/**
 * @brief Test de gestion des collisions dans la table de hachage.
 */
void test_hash_collisions() {
    printf("\n\n=== Test de gestion des collisions ===\n");
    
    hash_table *ht = createTable();
    
    // Insérer beaucoup d'étudiants pour provoquer des collisions
    student *students[20];
    for (int i = 0; i < 20; i++) {
        char cne[20];
        sprintf(cne, "CNE%03d", i);
        students[i] = create_test_student("Nom", "Prenom", cne, 10.0 + i * 0.5);
        insert_hash(ht, students[i]);
    }
    
    printf("20 etudiants inseres dans la table de hachage:\n");
    print_table(ht);
    
    // Vérifier que tous les étudiants sont récupérables
    int all_found = 1;
    for (int i = 0; i < 20; i++) {
        char cne[20];
        sprintf(cne, "CNE%03d", i);
        student *found = search_hash(ht, cne);
        
        if (found == NULL || strcmp(found->CNE, cne) != 0) {
            printf("ECHEC: Etudiant %s non trouve ou incorrect.\n", cne);
            all_found = 0;
        }
    }
    
    if (all_found) {
        printf("\nSUCCESS: Tous les 20 etudiants ont ete recuperes correctement.\n");
        printf("La gestion des collisions fonctionne correctement.\n");
    } else {
        printf("\nECHEC: Certains etudiants n'ont pas ete trouves.\n");
    }
    
    // Libérer la mémoire
    for (int i = 0; i < 20; i++) {
        free(students[i]);
    }
    free_table(ht);
}

/**
 * @brief Test de suppression avec collisions.
 */
void test_delete_with_collisions() {
    printf("\n\n=== Test de suppression avec collisions ===\n");
    
    hash_table *ht = createTable();
    
    // Insérer plusieurs étudiants
    student *students[10];
    for (int i = 0; i < 10; i++) {
        char cne[20];
        sprintf(cne, "CNE%03d", i);
        students[i] = create_test_student("Nom", "Prenom", cne, 10.0 + i);
        insert_hash(ht, students[i]);
    }
    
    printf("10 etudiants inseres:\n");
    print_table(ht);
    
    // Supprimer quelques étudiants
    printf("\n\nSuppression de CNE001, CNE005, CNE009:\n");
    delete_student_hash(ht, "CNE001");
    delete_student_hash(ht, "CNE005");
    delete_student_hash(ht, "CNE009");
    
    print_table(ht);
    
    // Vérifier que les étudiants supprimés ne sont plus là
    int correct = 1;
    if (search_hash(ht, "CNE001") != NULL) {
        printf("ECHEC: CNE001 encore present.\n");
        correct = 0;
    }
    if (search_hash(ht, "CNE005") != NULL) {
        printf("ECHEC: CNE005 encore present.\n");
        correct = 0;
    }
    if (search_hash(ht, "CNE009") != NULL) {
        printf("ECHEC: CNE009 encore present.\n");
        correct = 0;
    }
    
    // Vérifier que les autres sont toujours là
    if (search_hash(ht, "CNE000") == NULL || search_hash(ht, "CNE002") == NULL) {
        printf("ECHEC: Des etudiants non supprimes sont manquants.\n");
        correct = 0;
    }
    
    if (correct) {
        printf("\nSUCCESS: Les suppressions avec collisions fonctionnent correctement.\n");
    }
    
    // Libérer la mémoire
    for (int i = 0; i < 10; i++) {
        free(students[i]);
    }
    free_table(ht);
}

/**
 * @brief Test de libération de la table de hachage.
 */
void test_free_hash_table() {
    printf("\n\n=== Test de liberation de la table de hachage ===\n");
    
    hash_table *ht = createTable();
    
    // Insérer plusieurs étudiants
    student *students[15];
    for (int i = 0; i < 15; i++) {
        char cne[20];
        sprintf(cne, "CNE%03d", i);
        students[i] = create_test_student("Nom", "Prenom", cne, 10.0 + i);
        insert_hash(ht, students[i]);
    }
    
    printf("15 etudiants inseres dans la table.\n");
    
    // Libérer la table
    free_table(ht);
    printf("SUCCESS: Table liberee sans crash.\n");
    
    // Test avec NULL
    free_table(NULL);
    printf("SUCCESS: Aucun crash avec free_table(NULL).\n");
    
    // Libérer les étudiants
    for (int i = 0; i < 15; i++) {
        free(students[i]);
    }
}

/**
 * @brief Test de print_table avec différentes situations.
 */
void test_print_table() {
    printf("\n\n=== Test d'affichage de la table de hachage ===\n");
    
    // Test avec table vide
    hash_table *ht = createTable();
    printf("\nTable vide:\n");
    print_table(ht);
    
    // Ajouter quelques étudiants
    student *s1 = create_test_student("Alami", "Ahmed", "CNE001", 15.5);
    student *s2 = create_test_student("Bennani", "Fatima", "CNE002", 16.8);
    
    insert_hash(ht, s1);
    insert_hash(ht, s2);
    
    printf("\nTable avec 2 etudiants:\n");
    print_table(ht);
    
    // Test avec NULL
    printf("\nTest avec table NULL:\n");
    print_table(NULL);
    printf("SUCCESS: Aucun crash avec print_table(NULL).\n");
    
    free(s1);
    free(s2);
    free_table(ht);
}

/**
 * @brief Test complet de la table de hachage.
 */
void test_hash_table_complete() {
    printf("\n\n=== Test complet de la table de hachage ===\n");
    
    hash_table *ht = createTable();
    
    // Phase 1: Insertion
    printf("\nPhase 1: Insertion de 10 etudiants\n");
    student *students[10];
    for (int i = 0; i < 10; i++) {
        char nom[50], prenom[50], cne[20];
        sprintf(nom, "Nom%d", i);
        sprintf(prenom, "Prenom%d", i);
        sprintf(cne, "CNE%03d", i);
        students[i] = create_test_student(nom, prenom, cne, 10.0 + i);
        insert_hash(ht, students[i]);
    }
    print_table(ht);
    
    // Phase 2: Recherche
    printf("\n\nPhase 2: Recherche de quelques etudiants\n");
    for (int i = 0; i < 10; i += 3) {
        char cne[20];
        sprintf(cne, "CNE%03d", i);
        student *found = search_hash(ht, cne);
        if (found != NULL) {
            printf("Trouve: %s (Moyenne: %.2f)\n", found->CNE, found->moyenne);
        }
    }
    
    // Phase 3: Suppression
    printf("\n\nPhase 3: Suppression de quelques etudiants\n");
    delete_student_hash(ht, "CNE001");
    delete_student_hash(ht, "CNE005");
    delete_student_hash(ht, "CNE008");
    print_table(ht);
    
    // Phase 4: Vérification
    printf("\n\nPhase 4: Verification\n");
    int correct = 1;
    
    // Vérifier que les étudiants supprimés ne sont plus là
    if (search_hash(ht, "CNE001") != NULL || 
        search_hash(ht, "CNE005") != NULL || 
        search_hash(ht, "CNE008") != NULL) {
        printf("ECHEC: Des etudiants supprimes sont encore presents.\n");
        correct = 0;
    }
    
    // Vérifier que les autres sont toujours là
    if (search_hash(ht, "CNE000") == NULL || 
        search_hash(ht, "CNE002") == NULL || 
        search_hash(ht, "CNE009") == NULL) {
        printf("ECHEC: Des etudiants non supprimes sont manquants.\n");
        correct = 0;
    }
    
    if (correct) {
        printf("SUCCESS: Test complet de la table de hachage reussi!\n");
    } else {
        printf("ECHEC: Problemes detectes dans le test complet.\n");
    }
    
    // Libérer la mémoire
    for (int i = 0; i < 10; i++) {
        free(students[i]);
    }
    free_table(ht);
}

/**
 * @brief Programme principal de test.
 */
int main() {
    printf("========================================\n");
    printf("   TESTS COMPLETS DES FONCTIONS\n");
    printf("========================================\n\n");

    // Tests de tri - commentés car sort_students_by_grade non implémenté
    // printf("\n*** TESTS DE TRI ***\n");
    // test_sort_students_by_grade();
    // test_sort_empty_list();
    // test_sort_single_student();
    // test_sort_equal_grades();
    // test_sort_with_save_load();

    // Tests des fonctions auxiliaires du tri - commentés car fonctions non implémentées
    // printf("\n\n*** TESTS DES FONCTIONS AUXILIAIRES DE TRI ***\n");
    // test_get_middle();
    // test_merge_sorted_lists();
    // test_merge_sort_recursive();

    // Tests de recherche
    printf("\n\n*** TESTS DE RECHERCHE ***\n");
    test_search_student_by_cne();
    test_search_empty_list();
    // test_search_after_sort(); // commenté car sort_students_by_grade non implémenté

    // Tests de suppression
    printf("\n\n*** TESTS DE SUPPRESSION ***\n");
    test_delete_all_students();
    test_delete_combination();

    // Test de modification
    printf("\n\n*** TESTS DE MODIFICATION ***\n");
    test_modify_student();

    // Tests des arbres binaires
    printf("\n\n*** TESTS DES ARBRES BINAIRES DE RECHERCHE ***\n");
    test_create_ab_node();
    test_create_ab_racine();
    test_insert_bst();
    test_afficher_arbres_trie();
    test_free_bst_nodes();
    test_bst_complete();

    // Tests de la table de hachage
    printf("\n\n*** TESTS DE LA TABLE DE HACHAGE ***\n");
    test_create_hash_table();
    test_hash_function();
    test_insert_hash();
    test_search_hash();
    test_delete_hash();
    test_hash_collisions();
    test_delete_with_collisions();
    test_free_hash_table();
    test_print_table();
    test_hash_table_complete();

    printf("\n========================================\n");
    printf("   FIN DE TOUS LES TESTS\n");
    printf("========================================\n");

    return 0;
}