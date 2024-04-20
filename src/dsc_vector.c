/*
 * This file is part of libdsc.
 *
 * libdsc is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * libdsc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * libdsc. If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "../include/dsc_vector.h"
#include "../include/dsc_error.h"

/* Represents a vector. */
struct dsc_vector_t {
    int *values;     /* Array of values stored in the vector. */
    size_t size;     /* The number of elements in the vector. */
    size_t capacity; /* The current capacity of the vector. */
};

static void dsc_vector_resize(dsc_vector_t *vector, size_t new_capacity) {
    /* Check for integer overflow.*/
    if (new_capacity > SIZE_MAX / sizeof(int)) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return;
    }

    int *new_values = malloc(new_capacity * sizeof(int));
    if (new_values == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return;
    }

    if (vector->values != NULL) {
        memcpy(new_values, vector->values, vector->size * sizeof(int));
        free(vector->values);
    }

    vector->values = new_values;
    vector->capacity = new_capacity;
}

dsc_vector_t *dsc_vector_create() {
    dsc_vector_t *new_vector = malloc(sizeof *new_vector);
    if (new_vector == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    new_vector->size = 0;
    new_vector->capacity = DSC_VECTOR_INITIAL_CAPACITY;
    dsc_vector_resize(new_vector, new_vector->capacity);

    if (new_vector->values == NULL) {
        free(new_vector);
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return new_vector;
}

void dsc_vector_free(dsc_vector_t *vector) {
    if (vector == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    free(vector->values);
    free(vector);

    dsc_set_error(DSC_ERROR_NONE);
}

void dsc_vector_push_back(dsc_vector_t *vector, int value) {
    if (vector == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    /* Resize the vector if the size exceeds the capacity. */
    if (vector->size >= vector->capacity) {
        size_t new_capacity = vector->capacity * 1.5;
        dsc_vector_resize(vector, new_capacity);
        if (vector->values == NULL) {
            dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
            return;
        }
    }

    vector->values[vector->size] = value;
    vector->size++;
    dsc_set_error(DSC_ERROR_NONE);
}

void dsc_vector_pop_back(dsc_vector_t *vector) {
    if (vector == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    if (dsc_vector_empty(vector)) {
        dsc_set_error(DSC_ERROR_EMPTY_CONTAINER);
        return;
    }

    vector->size--;
    dsc_set_error(DSC_ERROR_NONE);
}

size_t dsc_vector_insert(struct dsc_vector_t *vector, size_t position, int value) {
    if (vector == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return 0;
    }

    if (position < 0 || position > vector->size) {
        dsc_set_error(DSC_ERROR_OUT_OF_RANGE);
        return 0;
    }

    /* Resize the vector if the size exceeds the capacity. */
    if (vector->size >= vector->capacity) {
        size_t new_capacity = vector->capacity * 1.5;
        dsc_vector_resize(vector, new_capacity);
        if (vector->values == NULL) {
            dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
            return 0;
        }
    }

    /* Shift elements to the right to make room for the new element. */
    for (size_t i = vector->size; i > position; --i) {
        vector->values[i] = vector->values[i - 1];
    }

    vector->values[position] = value;
    vector->size++;

    dsc_set_error(DSC_ERROR_NONE);
    return position;
}

void dsc_vector_erase(struct dsc_vector_t *vector, size_t position) {
    if (vector == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    if (position < 0 || position >= vector->size) {
        dsc_set_error(DSC_ERROR_OUT_OF_RANGE);
        return;
    }

    /* Shift elements to the left to fill the gap. */
    for (size_t i = position; i < vector->size - 1; ++i) {
        vector->values[i] = vector->values[i + 1];
    }

    vector->size--;
    dsc_set_error(DSC_ERROR_NONE);
}

int dsc_vector_at(const dsc_vector_t *vector, size_t index) {
    if (vector == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return 0;
    }

    if (index < 0 || index >= vector->size) {
        dsc_set_error(DSC_ERROR_OUT_OF_RANGE);
        return 0;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return vector->values[index];
}

bool dsc_vector_empty(const dsc_vector_t *vector) {
    if (vector == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return true;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return vector->size == 0;
}

size_t dsc_vector_size(const dsc_vector_t *vector) {
    if (vector == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return 0;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return vector->size;
}

size_t dsc_vector_capacity(const dsc_vector_t *vector) {
    if (vector == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return 0;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return vector->capacity;
}

void dsc_vector_reserve(dsc_vector_t *vector, size_t new_capacity) {
    if (vector == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    if (new_capacity <= vector->capacity) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    dsc_vector_resize(vector, new_capacity);
    if (vector->values == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return;
    }

    dsc_set_error(DSC_ERROR_NONE);
}