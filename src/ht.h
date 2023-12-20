#ifndef _HT_H
#define _HT_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef uint64_t hashfunction (const char*, size_t);
typedef void cleanup_t(void *);
typedef struct _ht_t ht_t;

/**
 * @brief Create a new hashtable
 * @param size number of entries in the table
 * @param hf hashfunction pointer
 * @param data char to store
 * @return hashtable pointer
 */
ht_t *ht_create(uint32_t size, hashfunction *hf, cleanup_t *cf);

/**
 * @brief Destroy a hashtable 
 * @param ht hashtable pointer
 * @return void
 */
void ht_destroy(ht_t *ht);

/**
 * @brief Print elements of hashtable 
 * @param ht hashtable pointer
 * @return void
 */
void ht_printf(ht_t *ht);

/**
 * @brief insert a new entry to hashtable
 * @param ht hashtable pointer
 * @param key insert value by string key
 * @param obj void pointer to object
 * @return true if inserted, return false if value is already there
 */
bool ht_insert(ht_t *ht, const char *key, void *obj);

/**
 * @brief search for element in hashtable 
 * @param ht hashtable pointer
 * @param key search for value with string key
 * @return void
 */
void *ht_search(ht_t *ht, const char *key);

/**
 * @brief Delete element of a hashtable
 * @param ht hashtable pointer
 * @param key delete value by provided string key
 * @return void
 */
void *ht_delete(ht_t *ht, const char *key);

#endif