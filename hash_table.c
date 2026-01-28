#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "hash_table.h"

unsigned int hash(const char *key) {
    unsigned int somme = 0;
    for (int i = 0; key[i]; i++) {
        somme = (somme * 31) + (unsigned char) key[i];
    }
    return somme % TABLE_SIZE;
}

hash_table *createTable() {
    hash_table *ht = (hash_table *) calloc(1, sizeof(hash_table));
    if (ht == NULL) {
        printf("Error allocating memory for hash table\n");
        exit(-1);
    }
    return ht;
}

void insert_hash(hash_table *ht, student *s) {
    if (ht == NULL || s == NULL) return;

    const unsigned int index = hash(s->CNE);

    node_hash *new_node = (node_hash *) malloc(sizeof(node_hash));
    if (new_node == NULL) {
        printf("Erreur memoire node_hash\n");
        return;
    }

    new_node->key = strdup(s->CNE);
    if (new_node->key == NULL) {
        free(new_node);
        return;
    }
    new_node->value = s;

    new_node->next = ht->table[index];
    ht->table[index] = new_node;
}

student *search_hash(hash_table *ht, const char *key) {
    if (ht == NULL || key == NULL) {
        return NULL;
    }

    const unsigned int index = hash(key);
    node_hash *temp = ht->table[index];
    while (temp != NULL) {
        if (strcmp(key, temp->key) == 0) {
            return temp->value;
        }
        temp = temp->next;
    }
    return NULL;
}

void delete_student_hash(hash_table *ht, const char *key) {
    if (ht == NULL || key == NULL) return;

    unsigned int index = hash(key);
    node_hash *current = ht->table[index];
    node_hash *previous = NULL;

    while (current != NULL) {
        if (strcmp(key, current->key) == 0) {
            if (previous == NULL) {
                ht->table[index] = current->next;
            } else {
                previous->next = current->next;
            }

            free(current->key);
            free(current);
            return;
        }

        previous = current;
        current = current->next;
    }
}

void print_table(hash_table *ht) {
    if (ht == NULL) return;

    printf("\n--- Contenu de la Table de Hachage ---\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        // On n'affiche que les cases non vides pour ne pas polluer l'écran
        if (ht->table[i] != NULL) {
            printf("Index %d : ", i);
            node_hash *current = ht->table[i];
            while (current != NULL) {
                printf("[%s] -> ", current->value->CNE);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
    printf("--------------------------------------\n");
}

void free_table(hash_table *ht) {
    if (ht == NULL) return;

    for (int i = 0; i < TABLE_SIZE; i++) {
        node_hash *current = ht->table[i];
        while (current != NULL) {
            node_hash *temp = current;
            current = current->next;

            if (temp->key != NULL) {
                free(temp->key);
            }
            free(temp);
        }
    }
    free(ht);
}
