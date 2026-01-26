#ifndef MINI_DATABASE_HASH_TABLE_H
#define MINI_DATABASE_HASH_TABLE_H

#define TABLE_SIZE 131
#include "student.h"

typedef struct node_hash {;
    char *key;
    student *value;
    struct node_hash *next;
} node_hash;

typedef struct hash_table {
    node_hash *table[TABLE_SIZE];
} hash_table;

unsigned int hash(const char *cne);

hash_table *createTable();

void insert_hash(hash_table *ht, student *s);

student *search(hash_table *ht, const char *key);

void delete_student_hash(hash_table *ht, const char *key);

void print_table(hash_table *ht);

void free_table(hash_table *ht);
#endif //MINI_DATABASE_HASH_TABLE_H
