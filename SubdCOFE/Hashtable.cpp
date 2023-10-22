#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Hashtable.h"
#include "Save_and_Output.h"
#define SIZE 20



// Простая хэш-функция
int hash_function(const char* key) {
    int hash = 0;
    for (int i = 0; i < strlen(key); i++) {
        hash += key[i];
    }
    return hash % SIZE;
}

// Инициализация хэш-таблицы
void initialize_hash(HashTable* hashtable) {
    for (int i = 0; i < SIZE; i++) {
        hashtable->array_hash[i] = NULL;
    }
}

// Добавление элемента в хэш-таблицу
void insert_hash(HashTable* hashtable, const char* key, const char* value) {
    int index = hash_function(key);
    Node_hash* new_node = (Node_hash*)malloc(sizeof(Node_hash));
    new_node->key_hash = _strdup(key);
    new_node->value_hash = _strdup(value);
    new_node->next_hash = NULL;

    if (hashtable->array_hash[index] == NULL) {
        hashtable->array_hash[index] = new_node;
    }
    else {
        Node_hash* current = hashtable->array_hash[index];
        while (current->next_hash != NULL) {
            current = current->next_hash;
        }
        current->next_hash = new_node;
    }
}


// Получение значения по ключу из хэш-таблицы
const char* getbykey_hash(HashTable* hashtable, const char* key) {
    int index = hash_function(key);
    Node_hash* current = hashtable->array_hash[index];
    while (current != NULL) {
        if (strcmp(current->key_hash, key) == 0) {
            return current->value_hash;
        }
        current = current->next_hash;
    }
    return NULL;
}

void printHashTable(HashTable* hashtable) {
    printf("Hash Table Contents:\n");
    for (int i = 0; i < SIZE; i++) {
        if (hashtable->array_hash[i] != NULL) {
            printf("Index %d: Key: %s, Value: %s\n", i, hashtable->array_hash[i]->key_hash, hashtable->array_hash[i]->value_hash);
        }
    }
}

void save_table_to_file(HashTable* myTable, const char* file_name, const char* table_name) {
    remove_table_from_file(file_name, table_name);
    FILE* file = fopen("database.data", "a");
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        return;
    }

    fprintf(file, "Hash Table Data (%s):\n", table_name);
    for (int i = 0; i < SIZE; i++) {
        if (myTable->array_hash[i] != NULL) {
            fprintf(file, "%s %s\n", myTable->array_hash[i]->key_hash, myTable->array_hash[i]->value_hash);
            myTable->array_hash[i] = myTable->array_hash[i]->next_hash;

        }
    }

    fclose(file);
}

void deletebykey_hash(HashTable* hashtable, const char* key) {
    int index = hash_function(key);
    Node_hash* current = hashtable->array_hash[index];
    Node_hash* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key_hash, key) == 0) {
            if (prev == NULL) {
                hashtable->array_hash[index] = current->next_hash;
            }
            else {
                prev->next_hash = current->next_hash;
            }
            free(current);
            break;
        }
        prev = current;
        current = current->next_hash;
    }
}



