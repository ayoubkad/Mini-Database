#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "student.h"

void test_creat_list_student() {
    list_student *list = creat_list_student();
    assert(list != NULL);
    assert(list->tete == NULL);
    assert(list->queues == NULL);
    printf("Test creat_list_student: PASSED\n");
}

void test_creat_student() {
    student *s = creat_student();
    assert(s != NULL);
    assert(s->next == NULL);
    printf("Test creat_student: PASSED\n");
}

void test_add_student() {
    list_student *list = creat_list_student();
    student *s1 = creat_student();
    strcpy(s1->nom, "Dupont");
    strcpy(s1->prenom, "Jean");
    strcpy(s1->CNE, "CNE001");
    
    add_student(list, s1);
    assert(list->tete == s1);
    assert(list->queues == s1);
    
    student *s2 = creat_student();
    strcpy(s2->nom, "Martin");
    strcpy(s2->prenom, "Marie");
    strcpy(s2->CNE, "CNE002");
    
    add_student(list, s2);
    assert(list->tete == s1);
    assert(list->queues == s2);
    assert(s1->next == s2);
    
    printf("Test add_student: PASSED\n");
}

int main() {
    printf("=== Execution des tests ===\n");
    test_creat_list_student();
    test_creat_student();
    test_add_student();
    printf("=== Tous les tests sont passes ===\n");
    return 0;
}
