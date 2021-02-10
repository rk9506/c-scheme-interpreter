#include "hash_table.h"

/* A generic hash-table largely cribbed from K&R */

HashTable *make_hash_table()
{
    HashTable *table = malloc(sizeof(HashTable*));
    *table = calloc(HASH_SIZE, sizeof(struct TableEntry));

    return table;
}

void free_table_entry(struct TableEntry *entry)
{
    if (entry != NULL)
    {
        free_table_entry(entry->next);
        free(entry);
    }
}

void free_hash_table(HashTable *table)
{
    int i;
    for (i = 0; i < HASH_SIZE; i++)
    {
        if (table[i] != NULL)
        {
            free_table_entry(table[i]);
        }
    }

    free(table);
}

void print_hash_table(HashTable *table)
{
    int i;
    for (i = 0; i < HASH_SIZE; i++)
    {
        if (table[i] != NULL)
        {
            if (table[i]->key != NULL) printf("table entry var %s\n", table[i]->key);
        }
    }
}

unsigned hash(char *key)
{
    unsigned hashval;

    for (hashval = 0; *key != '\0'; key++)
    {
        hashval = *key + 31 * hashval;
    }

    return hashval % HASH_SIZE;
}

struct TableEntry *hash_lookup(char *key, HashTable *table)
{
    struct TableEntry *e;

    for (e = table[hash(key)]; e != NULL; e = e->next)
    {
        if (strcmp(key, e->key) == 0)
        {
            return e; /* Found */
        }
    }

    return NULL; /* Not found */
}

struct TableEntry *hash_insert(char *key, void *value, HashTable *table)
{
    struct TableEntry *e;
    unsigned hashval;

    if ((e = hash_lookup(key, table)) == NULL) { /* not found */
        e = (struct TableEntry*) malloc(sizeof(*e));

        if (e == NULL || (e->key = strdup(key)) == NULL)
            return NULL;

        hashval = hash(key);
        e->next = table[hashval];
        table[hashval] = e;
    } else /* already there */
    {
        free(e->value); /*free previous defn */
    }

    if ((e->value = value) == NULL)
        return NULL;

    return e;
}
