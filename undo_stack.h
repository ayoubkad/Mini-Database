#ifndef UNDO_STACK_H
#define UNDO_STACK_H

typedef struct student student;
typedef struct ListStudent list_student;
typedef struct hash_table hash_table;

typedef enum {
    ADD_OPERATION,
    DELETE_OPERATION,
    MODIFY_OPERATION
} OperationType;

typedef struct {
    char nom[20];
    char prenom[20];
    Date date_naissance;
    char CNE[15];
    char filiere[30];
    float moyenne;
} student_data;

typedef struct UndoNode {
    OperationType type;
    student_data backup_data;
    struct UndoNode *next;
} UndoNode;

typedef struct {
    UndoNode *top;
} UndoStack;

UndoStack *create_undo_stack();

void push_undo(UndoStack *stack, OperationType type, student *s);

void execute_undo(hash_table *ht, list_student *list, UndoStack *stack);

void free_undo_stack(UndoStack *stack);

void modify_student(list_student *list, const char *cne_to_modify, UndoStack *stack);

void add_student(hash_table *ht, list_student *list, student *new_student, UndoStack *stack);

// Ajoute un étudiant à la fin de la liste.

void delete_student(hash_table *ht, list_student *list, char *cne_to_delete, UndoStack *stack);

// Supprime un étudiant de la liste en utilisant son CNE.

void display_undo_history(UndoStack *stack);
#endif
