#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Set.h"
#include "Save_and_Output.h"
// Структура для элемента множества


void initialize_set(Set* set) {
    set->size_set = 0;
}

bool contains_set(Set* set, int element) {
    for (int i = 0; i < set->size_set; i++) {
        if (set->elements_set[i] == element) {
            return true;
        }
    }
    return false;
}

void add_set(Set* set, int element) {
    if (!contains_set(set, element)) {
        set->elements_set[set->size_set++] = element;
    }
}

void remove_element_set(Set* set, int element) {
    
    for (int i = 0; i < set->size_set; i++) {
        if (set->elements_set[i] == element) {
            for (int j = i; j < set->size_set - 1; j++) {
                set->elements_set[j] = set->elements_set[j + 1];
            }
            set->size_set--;
            break;
        }
    }
   
}

void print_set(Set* set) {
    printf("{ ");
    for (int i = 0; i < set->size_set; i++) {
        printf("%d ", set->elements_set[i]);
    }
    printf("}\n");
}


