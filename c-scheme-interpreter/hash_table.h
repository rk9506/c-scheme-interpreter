#ifndef __HASH_TABLE_H_
#define __HASH_TABLE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define HASH_SIZE 8096

struct TableEntry;

struct TableEntry
{
    struct TableEntry *next;
    char *key;
    void *value;
};

typedef struct TableEntry* HashTable;

HashTable *make_hash_table();
void free_hash_table(HashTable *table);
struct TableEntry *hash_lookup(char *key, HashTable *table);
struct TableEntry *has_insert(char *key, void *value, HashTable *table);
void print_hash_table(HashTable *table);

#endif // __HASH_TABLE_H_
