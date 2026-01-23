#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "arbres_binaire.h"
#include "undo_stack.h"
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
    s->date_naissance.jour = 0;
    s->date_naissance.mois = 0;
    s->date_naissance.annee = 0;
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
void add_student(list_student *list, student *new_student, UndoStack *stack) {
    if (list->tete == NULL) {
        list->tete = new_student;
        list->queues = new_student;
    } else {
        list->queues->next = new_student;
        list->queues = new_student;
    }
    if (stack != NULL) {
        push_undo(stack, ADD_OPERATION, new_student);
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
    if (list_student == NULL || list_student->tete == NULL) {
        printf("la Base de donnee et vide!!!\n");
    }
    int compte = 1;
    student *courent = list_student->tete;
    while (courent != NULL) {
        printf("\n");
        printf("+--------------------------------------------+\n");
        printf("|             INFORMATION ETUDIANT %-2d       |\n", compte); // J'ai ajouté %-2d pour l'alignement
        printf("+--------------------------------------------+\n");
        printf("| CNE            : %-25.25s |\n", courent->CNE);
        printf("| Nom            : %-25.25s |\n", courent->nom);
        printf("| Prenom         : %-25.25s |\n", courent->prenom);
        printf("| Date Naissance : %02d/%02d/%-19d |\n", courent->date_naissance.jour,
               courent->date_naissance.mois, courent->date_naissance.annee);
        printf("| Filiere        : %-25.25s |\n", courent->filiere);
        printf("| Moyenne        : %-25.2f |\n", courent->moyenne);
        printf("+--------------------------------------------+\n");
        compte++;
        courent = courent->next;
    }
}

void display_student(list_student *list_student, char *cne) {
    if (list_student == NULL || list_student->tete == NULL) {
        printf("la Base de donnee et vide!!!\n");
    }
    int trouver = 0;
    student *courent = list_student->tete;
    while (courent != NULL && strcmp(courent->CNE, cne) != 0) {
        trouver = 1;
        printf("\n");
        printf("+--------------------------------------------+\n");
        printf("|             INFORMATION ETUDIANT       |\n"); // J'ai ajouté %-2d pour l'alignement
        printf("+--------------------------------------------+\n");
        printf("| CNE            : %-25.25s |\n", courent->CNE);
        printf("| Nom            : %-25.25s |\n", courent->nom);
        printf("| Prenom         : %-25.25s |\n", courent->prenom);
        printf("| Date Naissance : %02d/%02d/%-19d |\n", courent->date_naissance.jour,
               courent->date_naissance.mois, courent->date_naissance.annee);
        printf("| Filiere        : %-25.25s |\n", courent->filiere);
        printf("| Moyenne        : %-25.2f |\n", courent->moyenne);
        printf("+--------------------------------------------+\n");
        courent = courent->next;
    }
    if (trouver == 0) {
        printf("etudiant n'est pas trouver!!!\n");
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
void delete_student(list_student *list, char *cne_to_delete, UndoStack *stack) {
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

        if (stack == NULL) {
            push_undo(stack, DELETE_OPERATION, temp);
        }

        free(temp);
        printf("Etudiant supprime avec succes.\n");
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

    if (stack = NULL) {
        push_undo(stack, DELETE_OPERATION, current);
    }

    free(current);
    printf("Etudiant supprime avec succes.\n");
}

/**
 * @brief Sauvegarde la liste des étudiants dans un fichier binaire.
 * 
 * MÉTHODE DE SÉRIALISATION :
 * Cette fonction utilise la sérialisation binaire pour persister les données.
 * Elle convertit les structures student de la mémoire en un flux d'octets
 * qui peut être stocké sur le disque et rechargé ultérieurement.
 *
 * PROCESSUS :
 * 1. Ouverture du fichier en mode écriture binaire ("wb")
 * 2. Pour chaque étudiant de la liste chaînée :
 *    - Copie des données dans une structure buffer (student_data)
 *    - Exclusion du pointeur 'next' pour éviter la corruption de données
 *    - Écriture de la structure complète en un seul bloc binaire
 * 3. Fermeture du fichier après l'écriture de tous les étudiants
 *
 * AVANTAGES :
 * - Rapidité d'écriture/lecture (pas de conversion texte)
 * - Taille de fichier réduite
 * - Préservation exacte des types de données (float, int, etc.)
 *
 * INCONVÉNIENTS :
 * - Non portable entre différentes architectures
 * - Non lisible par un éditeur de texte
 *
 * @param list Pointeur vers la liste d'étudiants à sauvegarder.
 * @param filename Nom du fichier de destination.
 */
void save_database(list_student *list, char *filename) {
    // Ouvrir le fichier en mode écriture binaire ("wb" = write binary)
    FILE *pFile = fopen(filename, "wb");
    student *cursor = list->tete;

    if (pFile == NULL) {
        printf("Impossible d'ouverture a ce fichier %s\n", filename);
        exit(1);
    }

    // Buffer temporaire de type student_data (sans le pointeur 'next')
    // Cela évite d'écrire les adresses mémoire qui ne seraient pas valides après rechargement
    student_data buffer;

    // Parcourir toute la liste chaînée
    while (cursor != NULL) {
        // Copier les données de l'étudiant actuel dans le buffer
        strcpy(buffer.nom, cursor->nom);
        strcpy(buffer.prenom, cursor->prenom);
        strcpy(buffer.CNE, cursor->CNE);
        strcpy(buffer.filiere, cursor->filiere);
        buffer.moyenne = cursor->moyenne;
        buffer.date_naissance.jour = cursor->date_naissance.jour;
        buffer.date_naissance.mois = cursor->date_naissance.mois;
        buffer.date_naissance.annee = cursor->date_naissance.annee;

        // Écrire la structure complète dans le fichier en un seul bloc
        fwrite(&buffer, sizeof(student_data), 1, pFile);

        // Passer à l'étudiant suivant dans la liste
        cursor = cursor->next;
    }

    fclose(pFile);
    printf("Base de donnees sauvegardee avec succes.\n");
}

/**
 * @brief Charge tous les étudiants depuis un fichier binaire.
 * 
 * MÉTHODE DE DÉSÉRIALISATION :
 * Cette fonction effectue l'opération inverse de save_database.
 * Elle lit le flux d'octets depuis le fichier et reconstruit les structures
 * student en mémoire, recréant ainsi la liste chaînée originale.
 *
 * PROCESSUS :
 * 1. Ouverture du fichier en mode lecture binaire ("rb")
 * 2. Lecture séquentielle des structures student stockées :
 *    - fread() lit sizeof(student) octets à chaque itération
 *    - Chaque lecture crée un nouvel étudiant en mémoire
 *    - Reconstruction de la liste chaînée avec add_student()
 * 3. Arrêt automatique quand fread() retourne 0 (fin de fichier)
 * 4. Fermeture du fichier
 *
 * IMPORTANT :
 * - La liste doit être initialisée avant l'appel (via creat_list_student())
 * - Les pointeurs 'next' sont reconstruits lors de l'ajout à la liste
 * - L'ordre des étudiants est préservé (même ordre qu'à la sauvegarde)
 *
 * GESTION DES ERREURS :
 * - Vérifie l'existence du fichier avant de lire
 * - Retourne sans crash si le fichier n'existe pas
 *
 * @param list Pointeur vers la liste d'étudiants (doit être initialisée).
 * @param filename Nom du fichier source.
 */
void load_database(list_student *list, char *filename) {
    // Ouvrir le fichier en mode lecture binaire ("rb" = read binary)
    FILE *pFile = fopen(filename, "rb");

    if (pFile == NULL) {
        printf("Aucune base de donnees trouvee. Creation d'une nouvelle base...\n");
        return;
    }

    // Structure temporaire pour lire chaque étudiant depuis le fichier
    student_data temp;

    // Lire chaque étudiant du fichier jusqu'à la fin (EOF)
    // fread retourne 1 si la lecture réussit, 0 si on atteint la fin du fichier
    while (fread(&temp, sizeof(student_data), 1, pFile) == 1) {
        // Allouer dynamiquement de la mémoire pour le nouvel étudiant
        // Ceci crée un nouveau nœud dans la liste chaînée
        student *new_student = malloc(sizeof(student));

        // Copier toutes les données lues depuis le fichier vers le nouvel étudiant
        strcpy(new_student->nom, temp.nom);
        strcpy(new_student->prenom, temp.prenom);
        strcpy(new_student->CNE, temp.CNE);
        strcpy(new_student->filiere, temp.filiere);
        new_student->moyenne = temp.moyenne;
        new_student->date_naissance.jour = temp.date_naissance.jour;
        new_student->date_naissance.mois = temp.date_naissance.mois;
        new_student->date_naissance.annee = temp.date_naissance.annee;

        // Réinitialiser le pointeur next (il sera défini correctement par add_student)
        // Important : le pointeur 'next' du fichier ne serait pas valide ici
        new_student->next = NULL;

        // Ajouter l'étudiant à la fin de la liste chaînée
        // Cela reconstruit la structure de liste originale
        add_student(list, new_student, NULL);
    }

    fclose(pFile); // Fermer le fichier après la lecture complète
    printf("Donnees chargees avec succes !\n");
}

/**
 * @brief Modifie les informations d'un étudiant identifié par son CNE.
 *
 * Recherche un étudiant dans la liste en utilisant son CNE et permet
 * de modifier l'un de ses attributs (nom, prénom, date de naiéssance,
 * filière ou moyenne) selon le choix de l'utilisateur.
 *
 * @param list Pointeur vers la liste d'étudiants.
 * @param cne_to_modify CNE de l'étudiant à modifier.
 */
void modify_student(list_student *list, const char *cne_to_modify, UndoStack *stack) {
    // Initialiser le curseur au début de la liste
    student *cursor = list->tete;
    // Parcourir la liste pour trouver l'étudiant avec le CNE correspondant
    while (cursor != NULL) {
        if (strcmp(cursor->CNE, cne_to_modify) == 0) {
            int choice;

            push_undo(stack, MODIFY_OPERATION, cursor);

            // Afficher le menu des options de modification
            printf("Que voulez-vous changer?\n");
            printf("1. Nom\n");
            printf("2. Prenom\n");
            printf("3. Date\n");
            printf("4. Filiere\n");
            printf("5. Moyenne\n");
            printf("Votre choix: ");
            scanf("%d", &choice);
            while (getchar() != '\n') {
            }
            // Traiter le choix de l'utilisateur
            switch (choice) {
                case 1: {
                    // Modifier le nom
                    char new_nom[20];
                    printf("entrer nouvelle Nom : ");
                    fgets(new_nom, 20, stdin); // Note: fgets() serait plus sûr pour les noms composés comme "EL Amrani"
                    new_nom[strcspn(new_nom, "\n")] = 0; // strcspn()  qui return combien de caractere a '\n'
                    strcpy(cursor->nom, new_nom);
                    break;
                }
                case 2: {
                    // Modifier le prénom
                    char new_prenom[20];
                    printf("entrer nouvelle Prenom : ");
                    fgets(new_prenom, 20, stdin);
                    new_prenom[strcspn(new_prenom, "\n")] = 0;
                    strcpy(cursor->prenom, new_prenom);
                    break;
                }
                case 3: {
                    // Modifier la date de naissance
                    Date new_date;
                    printf("entrer nouvelle Date comme (1 6 2005) : ");
                    scanf("%d%d%d", &new_date.jour, &new_date.mois, &new_date.annee);
                    while (getchar() != '\n') {
                    }
                    cursor->date_naissance.jour = new_date.jour;
                    cursor->date_naissance.mois = new_date.mois;
                    cursor->date_naissance.annee = new_date.annee;
                    break;
                }
                case 4: {
                    // Modifier la filière
                    char new_filiere[30];
                    printf("entrer nouvelle Filiere : ");
                    fgets(new_filiere, 30, stdin);
                    new_filiere[strcspn(new_filiere, "\n")] = 0;
                    strcpy(cursor->filiere, new_filiere);
                    break;
                }
                case 5: {
                    // Modifier la moyenne
                    float new_moyenne;
                    printf("Entrer nouvelle Moyenne : ");
                    scanf("%f", &new_moyenne);
                    while (getchar() != '\n');
                    cursor->moyenne = new_moyenne;
                    break;
                }
                default:
                    printf("Choix invalide!\n");
            }
            printf("Modification reussie!\n");
            return;
        }
        // Passer à l'étudiant suivant
        cursor = cursor->next;
    }

    // Si l'étudiant n'a pas été trouvé
    printf("Erreur: Aucun etudiant trouve avec le CNE %s\n", cne_to_modify);
}

void search_student_by_cne(list_student *list, char *cne) {
    student *courent = list->tete;
    while (courent != NULL) {
        if (strcmp(courent->CNE, cne) == 0) {
            printf("+--------------------------------------------+\n");
            printf("|             INFORMATION ETUDIANT           |\n"); // J'ai ajouté %-2d pour l'alignement
            printf("+--------------------------------------------+\n");
            printf("| CNE            : %-25.25s |\n", courent->CNE);
            printf("| Nom            : %-25.25s |\n", courent->nom);
            printf("| Prenom         : %-25.25s |\n", courent->prenom);
            printf("| Date Naissance : %02d/%02d/%-19d |\n", courent->date_naissance.jour,
                   courent->date_naissance.mois, courent->date_naissance.annee);
            printf("| Filiere        : %-25.25s |\n", courent->filiere);
            printf("| Moyenne        : %-25.2f |\n", courent->moyenne);
            printf("+--------------------------------------------+\n");
            return;
        }
        courent = courent->next;
    }
    printf("n'est existe aucun etudiant de CNE : %s dans la base de donnees", cne);
}

void delete_all_students(list_student *list) {
    if (list == NULL || list->tete == NULL) {
        printf("la base de donnee est vide!!!");
        return;
    }
    student *courent = list->tete;
    while (courent != NULL) {
        student *temp = courent;
        courent = courent->next;
        free(temp);
    }
    list->tete = NULL;
    list->queues = NULL;

    printf("la base de donnee vide avec success");
}

/**
 * @brief Trouve le milieu d'une liste chaînée en utilisant la technique du pointeur rapide/lent.
 *
 * @param head Pointeur vers le premier nœud de la liste.
 * @return Pointeur vers le nœud du milieu.
 */
student *get_middle(student *head) {
    if (head == NULL) {
        return NULL;
    }

    student *slow = head;
    student *fast = head->next;

    // Le pointeur rapide avance deux fois plus vite que le lent
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

/**
 * @brief Fusionne deux listes chaînées triées en ordre décroissant par moyenne.
 *
 * @param left Pointeur vers le premier nœud de la première liste.
 * @param right Pointeur vers le premier nœud de la deuxième liste.
 * @return Pointeur vers le premier nœud de la liste fusionnée.
 */
student *merge_sorted_lists(student *left, student *right) {
    // Si une des listes est vide, retourner l'autre
    if (left == NULL) return right;
    if (right == NULL) return left;

    student *result = NULL;

    // Trier par ordre décroissant (meilleures moyennes en premier)
    if (left->moyenne >= right->moyenne) {
        result = left;
        result->next = merge_sorted_lists(left->next, right);
    } else {
        result = right;
        result->next = merge_sorted_lists(left, right->next);
    }
    return result;
}

/**
 * @brief Trie récursivement une liste chaînée par merge sort.
 *
 * @param head Pointeur vers le premier nœud de la liste à trier.
 * @return Pointeur vers le premier nœud de la liste triée.
 */
student *merge_sort_recursive(student *head) {
    // Cas de base : liste vide ou un seul élément
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // Trouver le milieu de la liste
    student *middle = get_middle(head);
    student *next_of_middle = middle->next;

    // Couper la liste en deux parties
    middle->next = NULL;

    // Trier récursivement les deux moitiés
    student *left = merge_sort_recursive(head);
    student *right = merge_sort_recursive(next_of_middle);

    // Fusionner les deux listes triées
    student *sorted = merge_sorted_lists(left, right);

    return sorted;
}

/**
 * @brief Trie les étudiants par moyenne (ordre décroissant).
 *
 * Utilise l'algorithme de tri fusion (merge sort) pour trier la liste
 * des étudiants en fonction de leur moyenne, du plus élevé au plus faible.
 *
 * @param list Pointeur vers la liste d'étudiants à trier.
 */
void sort_students_by_grade(list_student *list) {
    if (list == NULL || list->tete == NULL) {
        printf("La liste est vide, impossible de trier.\n");
        return;
    }

    // Appliquer le tri fusion
    list->tete = merge_sort_recursive(list->tete);

    // Mettre à jour le pointeur de queue
    student *current = list->tete;
    while (current != NULL && current->next != NULL) {
        current = current->next;
    }
    list->queues = current;

    printf("Liste triee par moyenne avec succes.\n");
}

static void display_student_arbre(student *student) {
    printf("+--------------------------------------------+\n");
    printf("|             INFORMATION ETUDIANT       |\n"); // J'ai ajouté %-2d pour l'alignement
    printf("+--------------------------------------------+\n");
    printf("| CNE            : %-25.25s |\n", student->CNE);
    printf("| Nom            : %-25.25s |\n", student->nom);
    printf("| Prenom         : %-25.25s |\n", student->prenom);
    printf("| Date Naissance : %02d/%02d/%-19d |\n", student->date_naissance.jour,
           student->date_naissance.mois, student->date_naissance.annee);
    printf("| Filiere        : %-25.25s |\n", student->filiere);
    printf("| Moyenne        : %-25.2f |\n", student->moyenne);
    printf("+--------------------------------------------+\n");
}

static void sort_by_arbre_recursive(ab_node_student *node) {
    if (node != NULL) {
        sort_by_arbre_recursive(node->filsd);
        display_student_arbre(node->std);
        sort_by_arbre_recursive(node->filsg);
    }
}

void afficher_arbres_trie(ab_racine_student *racine) {
    if (racine == NULL || racine->racine == NULL) {
        printf("L'arbre est vide.\n");
        return;
    }
    printf("\n=== Liste des etudiants triee par moyenne (Decroissant) ===\n");
    sort_by_arbre_recursive(racine->racine);
    printf("===========================================================\n");
}
