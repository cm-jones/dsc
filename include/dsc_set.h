/*
 * This file is part of the Data Structures for C (DSC) library.
 *
 * The Data Structures for C (DSC) library is free software: you can
 * redistribute it and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * The Data Structures for C (DSC) library is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * the Data Structures for C (DSC) library. If not, see
 * <https://www.gnu.org/licenses/>.
 */

#ifndef __DSC_SET_H__
#define __DSC_SET_H__

#include <stdbool.h>
#include "dsc_error.h"

/**
 * @def DSC_SET_INITIAL_CAPACITY
 * @brief The initial capacity of the hash set.
 */
#define DSC_SET_INITIAL_CAPACITY 16

/**
 * @def DSC_SET_LOAD_FACTOR
 * @brief The load factor threshold for resizing the hash set.
 */
#define DSC_SET_LOAD_FACTOR 0.75

/**
 * @struct dsc_set_entry_t
 * @brief Represents an entry in the hash set.
 *
 * @param key The key of the entry.
 * @param next Pointer to the next entry in case of collisions.
 */
struct dsc_set_entry_t {
    int key;
    struct dsc_set_entry_t *next;
};

/**
 * @struct dsc_set_t
 * @brief Represents a hash set.
 *
 * @param buckets Array of pointers to entries.
 * @param capacity The current capacity of the hash set.
 * @param size The number of elements in the hash set.
 * @param error The error status of the hash set.
 */
struct dsc_set_t {
    struct dsc_set_entry **buckets;
    int capacity;
    int size;
    enum dsc_error_t error;
};

/**
 * @brief Creates a new hash set.
 *
 * @return A pointer to the newly created hash set, or NULL if memory allocation fails.
 */
struct dsc_set_t *dsc_set_create();

/**
 * @brief Creates a new hash set with an error status.
 *
 * @param error The error status to set for the hash set.
 * @return A pointer to the newly created hash set, or NULL if memory allocation fails.
 */
struct dsc_set_t *dsc_set_create_with_error(enum dsc_error_t error);

/**
 * @brief Destroys the hash set and frees its memory.
 *
 * @param set The hash set to destroy.
 * @return NULL.
 */
struct dsc_set_t *dsc_set_destroy(struct dsc_set_t *set);

/**
 * @brief Adds an element to the hash set.
 *
 * @param set The hash set to add the element to.
 * @param value The value to add.
 * @return The updated hash set.
 */
struct dsc_set_t *dsc_set_add(struct dsc_set_t *set, int value);

/**
 * @brief Removes an element from the hash set.
 *
 * @param set The hash set to remove the element from.
 * @param value The value to remove.
 * @return The updated hash set.
 */
struct dsc_set_t *dsc_set_remove(struct dsc_set_t *set, int value);

/**
 * @brief Checks if an element exists in the hash set.
 *
 * @param set The hash set to check.
 * @param value The value to check for.
 * @return true if the element exists, false otherwise.
 */
bool dsc_set_contains(struct dsc_set_t *set, int value);

/**
 * @brief Gets the size of the hash set.
 *
 * @param set The hash set to get the size of.
 * @return The size of the hash set.
 */
int dsc_set_size(struct dsc_set_t *set);

/**
 * @brief Checks if the hash set is empty.
 *
 * @param set The hash set to check.
 * @return true if the hash set is empty, false otherwise.
 */
bool dsc_set_is_empty(struct dsc_set_t *set);

/**
 * @brief Clears all elements from the hash set.
 *
 * @param set The hash set to clear.
 * @return The updated hash set.
 */
struct dsc_set_t *dsc_set_clear(struct dsc_set_t *set);

#endif // __DSC_SET_H__