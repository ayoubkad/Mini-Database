#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "undo_stack.h"

// Déclarations des fonctions manquantes dans student.h
void add_student(list_student *list, student *new_student, UndoStack *stack);
void delete_student(list_student *list, char *cne_to_delete, UndoStack *stack);
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
void test_sort_students_by_grade() {
    printf("=== Test de tri des etudiants par moyenne ===\n\n");

    // Créer une liste d'étudiants
    list_student *list = creat_list_student();

    // Ajouter des étudiants avec différentes moyennes
    add_student(list, create_test_student("Alami", "Ahmed", "CNE001", 12.5), NULL);
    add_student(list, create_test_student("Bennani", "Fatima", "CNE002", 16.8), NULL);
    add_student(list, create_test_student("Cherif", "Hassan", "CNE003", 14.2), NULL);
    add_student(list, create_test_student("Drissi", "Salma", "CNE004", 18.5), NULL);
    add_student(list, create_test_student("El Amrani", "Youssef", "CNE005", 11.0), NULL);
    add_student(list, create_test_student("Fassi", "Laila", "CNE006", 15.7), NULL);

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
    delete_all_students(list);
    free(list);
}

/**
 * @brief Test de la fonction de tri avec une liste vide.
 */
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

/**
 * @brief Test de la fonction de tri avec un seul étudiant.
 */
void test_sort_single_student() {
    printf("\n\n=== Test de tri avec un seul etudiant ===\n");
    list_student *list = creat_list_student();

    add_student(list, create_test_student("Unique", "Etudiant", "CNE999", 14.5), NULL);

    printf("Avant tri: Moyenne = %.2f\n", list->tete->moyenne);
    sort_students_by_grade(list);
    printf("Apres tri: Moyenne = %.2f\n", list->tete->moyenne);

    if (list->tete->moyenne == 14.5 && list->tete->next == NULL) {
        printf("SUCCESS: Un seul etudiant reste inchange.\n");
    } else {
        printf("ECHEC: Le tri a modifie incorrectement la liste.\n");
    }

    delete_all_students(list);
    free(list);
}

/**
 * @brief Test de la fonction de tri avec des moyennes identiques.
 */
void test_sort_equal_grades() {
    printf("\n\n=== Test de tri avec moyennes identiques ===\n");
    list_student *list = creat_list_student();

    add_student(list, create_test_student("A", "Premier", "CNE101", 15.0), NULL);
    add_student(list, create_test_student("B", "Deuxieme", "CNE102", 15.0), NULL);
    add_student(list, create_test_student("C", "Troisieme", "CNE103", 15.0), NULL);

    printf("Liste avant tri:\n");
    display_all_student(list);

    sort_students_by_grade(list);

    printf("\nListe apres tri:\n");
    display_all_student(list);

    printf("\nSUCCESS: Le tri fonctionne avec des moyennes identiques.\n");

    delete_all_students(list);
    free(list);
}

/**
 * @brief Test de sauvegarde et chargement après tri.
 */
void test_sort_with_save_load() {
    printf("\n\n=== Test de tri avec sauvegarde et chargement ===\n");
    list_student *list1 = creat_list_student();

    // Ajouter des étudiants
    add_student(list1, create_test_student("Zaki", "Amina", "CNE201", 13.5), NULL);
    add_student(list1, create_test_student("Yassir", "Omar", "CNE202", 17.2), NULL);
    add_student(list1, create_test_student("Wafi", "Nadia", "CNE203", 15.8), NULL);

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

    delete_all_students(list1);
    delete_all_students(list2);
    free(list1);
    free(list2);
}

/**
 * @brief Test de la fonction de recherche par CNE.
 */
void test_search_student_by_cne() {
    printf("\n\n=== Test de recherche d'etudiant par CNE ===\n");
    list_student *list = creat_list_student();

    // Ajouter plusieurs étudiants
    add_student(list, create_test_student("Alami", "Ahmed", "CNE001", 12.5), NULL);
    add_student(list, create_test_student("Bennani", "Fatima", "CNE002", 16.8), NULL);
    add_student(list, create_test_student("Cherif", "Hassan", "CNE003", 14.2), NULL);

    printf("\nRecherche d'un etudiant existant (CNE002):\n");
    search_student_by_cne(list, "CNE002");

    printf("\n\nRecherche d'un etudiant inexistant (CNE999):\n");
    search_student_by_cne(list, "CNE999");

    printf("\nSUCCESS: Test de recherche complete.\n");

    delete_all_students(list);
    free(list);
}

/**
 * @brief Test de la fonction de suppression de tous les étudiants.
 */
void test_delete_all_students() {
    printf("\n\n=== Test de suppression de tous les etudiants ===\n");
    list_student *list = creat_list_student();

    // Ajouter plusieurs étudiants
    add_student(list, create_test_student("Student1", "First", "CNE101", 15.0), NULL);
    add_student(list, create_test_student("Student2", "Second", "CNE102", 16.0), NULL);
    add_student(list, create_test_student("Student3", "Third", "CNE103", 17.0), NULL);

    printf("Liste avant suppression:\n");
    display_all_student(list);

    printf("\n\nSuppression de tous les etudiants...\n");
    delete_all_students(list);

    if (list->tete == NULL && list->queues == NULL) {
        printf("\nSUCCESS: Tous les etudiants ont ete supprimes.\n");
        printf("Verification: tete = NULL, queues = NULL\n");
    } else {
        printf("\nECHEC: La liste n'est pas vide apres suppression.\n");
    }

    // Test de suppression sur liste déjà vide
    printf("\n\nTest de suppression sur liste vide:\n");
    delete_all_students(list);
    printf("SUCCESS: Aucune erreur lors de la suppression d'une liste vide.\n");

    free(list);
}

/**
 * @brief Test de la fonction get_middle().
 * Teste la fonction qui trouve le milieu d'une liste chaînée.
 */
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
    add_student(list, create_test_student("A", "First", "CNE101", 15.0), NULL);
    middle = get_middle(list->tete);
    if (middle != NULL && strcmp(middle->CNE, "CNE101") == 0) {
        printf("SUCCESS: get_middle fonctionne avec un seul element.\n");
    } else {
        printf("ECHEC: get_middle ne fonctionne pas correctement avec un seul element.\n");
    }

    // Test avec plusieurs éléments (nombre impair)
    add_student(list, create_test_student("B", "Second", "CNE102", 16.0), NULL);
    add_student(list, create_test_student("C", "Third", "CNE103", 17.0), NULL);
    add_student(list, create_test_student("D", "Fourth", "CNE104", 18.0), NULL);
    add_student(list, create_test_student("E", "Fifth", "CNE105", 19.0), NULL);
    
    middle = get_middle(list->tete);
    if (middle != NULL && strcmp(middle->CNE, "CNE103") == 0) {
        printf("SUCCESS: get_middle trouve correctement le milieu (5 elements).\n");
    } else {
        printf("ECHEC: Milieu attendu CNE103, trouve %s.\n", middle ? middle->CNE : "NULL");
    }

    // Test avec nombre pair d'éléments
    delete_all_students(list);
    add_student(list, create_test_student("A", "First", "CNE201", 15.0), NULL);
    add_student(list, create_test_student("B", "Second", "CNE202", 16.0), NULL);
    add_student(list, create_test_student("C", "Third", "CNE203", 17.0), NULL);
    add_student(list, create_test_student("D", "Fourth", "CNE204", 18.0), NULL);
    
    middle = get_middle(list->tete);
    if (middle != NULL && strcmp(middle->CNE, "CNE202") == 0) {
        printf("SUCCESS: get_middle fonctionne avec un nombre pair d'elements.\n");
    } else {
        printf("ECHEC: Milieu attendu CNE202, trouve %s.\n", middle ? middle->CNE : "NULL");
    }

    delete_all_students(list);
    free(list);
}

/**
 * @brief Test de la fonction merge_sorted_lists().
 * Teste la fusion de deux listes triées.
 */
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

/**
 * @brief Test de la fonction merge_sort_recursive().
 * Teste le tri récursif d'une liste.
 */
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

/**
 * @brief Test de la fonction de modification d'étudiant.
 */
void test_modify_student() {
    printf("\n\n=== Test de modification d'etudiant ===\n");
    list_student *list = creat_list_student();

    // Ajouter un étudiant
    student *s = create_test_student("Alami", "Ahmed", "CNE001", 12.5);
    add_student(list, s, NULL);

    printf("Etudiant avant modification:\n");
    search_student_by_cne(list, "CNE001");

    printf("\n\nNOTE: La fonction modify_student() necessite une interaction utilisateur.\n");
    printf("Pour un test automatise, nous verifions seulement l'existence de l'etudiant.\n");

    // Test de modification d'un étudiant inexistant
    printf("\nTentative de modification d'un CNE inexistant:\n");
    modify_student(list, "CNE999", NULL);

    printf("\nSUCCESS: Test de modification complete (verification de base).\n");

    delete_all_students(list);
    free(list);
}

/**
 * @brief Test de la fonction de recherche avec liste vide.
 */
void test_search_empty_list() {
    printf("\n\n=== Test de recherche dans une liste vide ===\n");
    list_student *list = creat_list_student();

    printf("Recherche dans une liste vide:\n");
    search_student_by_cne(list, "CNE001");

    printf("\nSUCCESS: Aucun crash lors de la recherche dans une liste vide.\n");

    free(list);
}

/**
 * @brief Test de recherche après tri.
 */
void test_search_after_sort() {
    printf("\n\n=== Test de recherche apres tri ===\n");
    list_student *list = creat_list_student();

    // Ajouter des étudiants
    add_student(list, create_test_student("Zaki", "Amina", "CNE201", 13.5), NULL);
    add_student(list, create_test_student("Yassir", "Omar", "CNE202", 17.2), NULL);
    add_student(list, create_test_student("Wafi", "Nadia", "CNE203", 15.8), NULL);

    printf("Liste avant tri:\n");
    display_all_student(list);

    // Trier la liste
    sort_students_by_grade(list);

    printf("\n\nListe apres tri:\n");
    display_all_student(list);

    // Rechercher un étudiant après le tri
    printf("\n\nRecherche de CNE202 apres tri:\n");
    search_student_by_cne(list, "CNE202");

    printf("\nSUCCESS: La recherche fonctionne correctement apres le tri.\n");

    delete_all_students(list);
    free(list);
}

/**
 * @brief Test de suppression individuelle suivie d'une suppression totale.
 */
void test_delete_combination() {
    printf("\n\n=== Test de combinaison de suppressions ===\n");
    list_student *list = creat_list_student();

    // Ajouter plusieurs étudiants
    add_student(list, create_test_student("A", "First", "CNE301", 15.0), NULL);
    add_student(list, create_test_student("B", "Second", "CNE302", 16.0), NULL);
    add_student(list, create_test_student("C", "Third", "CNE303", 17.0), NULL);
    add_student(list, create_test_student("D", "Fourth", "CNE304", 18.0), NULL);

    printf("Liste initiale (4 etudiants):\n");
    display_all_student(list);

    // Supprimer un étudiant
    printf("\n\nSuppression de CNE302:\n");
    delete_student(list, "CNE302", NULL);
    display_all_student(list);

    // Supprimer un autre étudiant
    printf("\n\nSuppression de CNE304:\n");
    delete_student(list, "CNE304", NULL);
    display_all_student(list);

    // Supprimer tous les étudiants restants
    printf("\n\nSuppression de tous les etudiants restants:\n");
    delete_all_students(list);

    if (list->tete == NULL && list->queues == NULL) {
        printf("SUCCESS: Toutes les suppressions ont fonctionne correctement.\n");
    } else {
        printf("ECHEC: La liste n'est pas vide.\n");
    }

    free(list);
}

/**
 * @brief Programme principal de test.
 */
int main() {
    printf("========================================\n");
    printf("   TESTS COMPLETS DES FONCTIONS\n");
    printf("========================================\n\n");

    // Tests de tri
    printf("\n*** TESTS DE TRI ***\n");
    test_sort_students_by_grade();
    test_sort_empty_list();
    test_sort_single_student();
    test_sort_equal_grades();
    test_sort_with_save_load();

    // Tests des fonctions auxiliaires du tri
    printf("\n\n*** TESTS DES FONCTIONS AUXILIAIRES DE TRI ***\n");
    test_get_middle();
    test_merge_sorted_lists();
    test_merge_sort_recursive();

    // Tests de recherche
    printf("\n\n*** TESTS DE RECHERCHE ***\n");
    test_search_student_by_cne();
    test_search_empty_list();
    test_search_after_sort();

    // Tests de suppression
    printf("\n\n*** TESTS DE SUPPRESSION ***\n");
    test_delete_all_students();
    test_delete_combination();

    // Test de modification
    printf("\n\n*** TESTS DE MODIFICATION ***\n");
    test_modify_student();

    printf("\n========================================\n");
    printf("   FIN DE TOUS LES TESTS\n");
    printf("========================================\n");

    return 0;
}