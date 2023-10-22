#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Set.h"
#include "Save_and_Output.h"


int main() {
    setlocale(LC_ALL, "Russian");
    char quer[100];
    fgets(quer, sizeof(quer), stdin); // считывание строки с клавиатуры
    const char* query = quer;

    if (strstr(query, "SADD") != NULL) {
        int element;
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'SADD %s %d'", filename, table_name, &element);
        const char* c_filename = filename;
        const char* c_table_name = table_name;
        Set Set = read_set_from_file(filename, table_name);
        add_set(&Set, element);
        save_set_to_file(&Set, filename, table_name);
    }
    else if (strstr(query, "SREM") != NULL) {
        int element;
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'SREM %s %d'", filename, table_name, &element);
        Set Set = read_set_from_file(filename, table_name);
        remove_element_set(&Set, element);
        save_set_to_file(&Set, filename, table_name);
    }
    else if (strstr(query, "SISMEMBER") != NULL) {
        int element;
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'SISMEMBER %s %d'", filename, table_name, &element);
        Set Set = read_set_from_file(filename, table_name);
        if (contains_set(&Set, element)) printf("-> %s", "True");
        else printf("-> %s", "False");
    }

    else if (strstr(query, "SISSHOW") != NULL) {
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'SISSHOW %[^\']'", filename, table_name);
        Set mySet = read_set_from_file(filename, table_name);
        print_set(&mySet);
    }

    else if (strstr(query, "SPUSH") != NULL) {
        int element;
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'SPUSH %s %d'", filename, table_name, &element);
        Stack Stack = read_stack_from_file(filename, table_name);
        push_stack(&Stack, element);
        save_stack_to_file(&Stack, filename, table_name);
    }

    else if (strstr(query, "SPOP") != NULL) {
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'SPOP %s'", filename, table_name);
        Stack Stack = read_stack_from_file(filename, table_name);
        printf("-> %d", top_stack(&Stack));
        pop_stack(&Stack, filename, table_name);
    }

    else if (strstr(query, "STACKSHOW") != NULL) {
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'STACKSHOW %[^\']'", filename, table_name);
        Stack Stack = read_stack_from_file(filename, table_name);
        print_stack(&Stack);
    }


    else if (strstr(query, "QPUSH") != NULL) {
        int element;
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'QPUSH %s %d'", filename, table_name, &element);
        Queue Queue = read_queue_from_file(filename, table_name);
        enqueue(&Queue, element);
        save_queue_to_file(&Queue, filename, table_name);
    }

    else if (strstr(query, "QPOP") != NULL) {
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'QPOP %s'", filename, table_name);
        Queue Queue = read_queue_from_file(filename, table_name);
        printf("-> %d", top_queue(&Queue));
        dequeue(&Queue);
        save_queue_to_file(&Queue, filename, table_name);

    }
    
    else if (strstr(query, "QSHOW") != NULL) {
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'QSHOW %[^\']'", filename, table_name);
        Queue Queue = read_queue_from_file(filename, table_name);
        print_queue(&Queue);
    }

    else if (strstr(query, "HSET") != NULL) {
        char element[20], key[20], filename[20], table_name[20];
        sscanf(query, "--file %s --query 'HSET %s %s %[^\']'", filename, table_name, key, &element);
        const char* c_filename = filename;
        const char* c_table_name = table_name;
        const char* c_key = key;
        const char* c_element = element;
        HashTable HS;
        HS = read_table_from_file(filename, table_name);
        insert_hash(&HS, c_key, c_element);
        save_table_to_file(&HS, filename, table_name);
    }

    else if (strstr(query, "HDEL") != NULL) {
        char key[20], filename[20], table_name[20];
        sscanf(query, "--file %s --query 'HDEL %s %[^\']'", filename, table_name, key);
        const char* c_filename = filename;
        const char* c_table_name = table_name;
        const char* c_key = key;
        HashTable HS;
        HS = read_table_from_file(filename, table_name);
        deletebykey_hash(&HS, c_key);
        save_table_to_file(&HS, filename, table_name);
    }


    else if (strstr(query, "HGET") != NULL) {
        char key[20], filename[20], table_name[20];
        sscanf(query, "--file %s --query 'HGET %s %[^\']'", filename, table_name, key);
        HashTable HS = read_table_from_file(filename, table_name);
        const char* value = getbykey_hash(&HS, key);
        if (value != NULL) {
            printf("-> %s", value);
        }
    }


    else if (strstr(query, "HSHOW") != NULL) {
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'HSHOW %[^\']'", filename, table_name);
        HashTable HS = read_table_from_file(filename, table_name);
        printHashTable(&HS);
    }


    return 0;
}




