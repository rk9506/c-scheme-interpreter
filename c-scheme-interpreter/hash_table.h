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

HashTable *make_table();
void free_table(HashTable *table);
struct TableEntry *lookup(char *key, HashTable *table);
struct TableEntry *insert(char *key, void *value, HashTable *table);

#endif // __HASH_TABLE_H_
